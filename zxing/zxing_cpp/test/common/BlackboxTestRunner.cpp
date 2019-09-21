/*
* Copyright 2016 Nu-book Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "BlackboxTestRunner.h"
#include "TextDecoder.h"
#include "TextUtfEncoding.h"
#include "DecodeHints.h"
#include "Result.h"
#include "ImageLoader.h"
#include "TestReader.h"
#include "Pdf417MultipleCodeReader.h"
#include "QRCodeStructuredAppendReader.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <functional>

namespace ZXing { namespace Test {

static std::wstring buildPath(const std::wstring& dir, const std::wstring& name)
{
	if (dir.empty())
		return name;
	if (name.empty())
		return dir;
	if (dir.back() == '/' || name.front() == '/')
		return dir + name;
	return dir + L"/" + name;
}

template <typename StrT>
static StrT getBaseName(const StrT& path)
{
	for (int i = (int)path.size(); i >= 0; --i) {
		if (path[i] == '\\' || path[i] == '/')
			return path.substr(i + 1);
	}
	return path;
}

static std::wstring replaceExtension(const std::wstring& filePath, const std::wstring& newExt)
{
	for (int i = (int)filePath.size(); i >= 0; --i) {
		if (filePath[i] == '.')
			return filePath.substr(0, !newExt.empty() && newExt[0] != '.' ? i + 1 : i) + newExt;
		if (filePath[i] == '\\' || filePath[i] == '/')
			break;
	}
	if (filePath.empty() || newExt.empty())
		return filePath;
	return filePath + (newExt[0] != '.' ? L"." : L"") + newExt;
}

static std::string toUtf8(const std::wstring& s)
{
	return TextUtfEncoding::ToUtf8(s);
}

#ifdef _WIN32
    #define asNativePath(x) x
#else
	static std::string asNativePath(const std::wstring& path) { return toUtf8(path); }
#endif


namespace {

	struct TestCase
	{
		struct TC
		{
			const char* name;
			int mustPassCount; // The number of images which must decode for the test to pass.
			int maxMisreads;   // Maximum number of images which can fail due to successfully reading the wrong contents
			std::set<std::wstring> notDetectedFiles;
			std::map<std::wstring, std::string> misReadFiles;
		};

		TC tc[2];
		int rotation; // The rotation in degrees clockwise to use for this test.

		TestCase(int mpc, int thc, int mm, int mt, int r) : tc{ {"fast", mpc, mm, {}, {}}, {"slow", thc, mt, {}, {}} }, rotation(r) {}
		TestCase(int mpc, int thc, int r) : TestCase(mpc, thc, 0, 0, r) {}
	};

	struct FalsePositiveTestCase
	{
		int maxAllowed; // Maximum number of images which can fail due to successfully reading the wrong contents
		int rotation;   // The rotation in degrees clockwise to use for this test.
	};
}

static std::string checkResult(const std::wstring& pathPrefix, std::wstring imgPath, const std::string& expectedFormat, const TestReader::ReadResult& result)
{
	if (expectedFormat != result.format)
		return "Format mismatch: expected " + expectedFormat + " but got " + result.format;

	std::ifstream metaStream(asNativePath(buildPath(pathPrefix, replaceExtension(imgPath, L".metadata.txt"))),
							 std::ios::binary);
	if (metaStream) {
		std::string expected((std::istreambuf_iterator<char>(metaStream)), std::istreambuf_iterator<char>());
		auto utf8Metatata = toUtf8(result.metadata);
		if (utf8Metatata != expected)
			return "Metadata mismatch: expected '" + expected + "' but got '" + utf8Metatata + "'";
	}

	imgPath = replaceExtension(imgPath, L".txt");
	std::ifstream utf8Stream(asNativePath(buildPath(pathPrefix, imgPath)), std::ios::binary);
	if (utf8Stream) {
		std::string expected((std::istreambuf_iterator<char>(utf8Stream)), std::istreambuf_iterator<char>());
		auto utf8Result = toUtf8(result.text);
		return utf8Result != expected ? "Content mismatch: expected '" + expected + "' but got '" + utf8Result + "'" : "";
	}

	imgPath = replaceExtension(imgPath, L".bin");
	std::ifstream latin1Stream(asNativePath(buildPath(pathPrefix, imgPath)), std::ios::binary);
	if (latin1Stream) {
		std::string expected((std::istreambuf_iterator<char>(latin1Stream)), std::istreambuf_iterator<char>());
		std::string latin1Result;
		for (wchar_t c : result.text) {
			latin1Result.push_back(static_cast<char>(c));
		}
		return latin1Result != expected ? "Content mismatch: expected '" + expected + "' but got '" + latin1Result + "'" : "";
	}

	return "Error reading file";
}

static const char* BAD = "!!!!!! FAILED !!!!!!";


static void printPositiveTestStats(int imageCount, const TestCase::TC& tc)
{
	int passCount = imageCount - (int)tc.misReadFiles.size() - (int)tc.notDetectedFiles.size();

	printf(", %s: %3d of %3d, misread: %d of %d", tc.name, (int)passCount, tc.mustPassCount,
		(int)tc.misReadFiles.size(), tc.maxMisreads);

	if (passCount < tc.mustPassCount && !tc.notDetectedFiles.empty()) {
		std::cout << "\nFAILED: Not detected (" << tc.name << "):";
		for (const auto& f : tc.notDetectedFiles)
			std::cout << ' ' << toUtf8(f);
		std::cout << "\n";
	}

	if ((int)tc.misReadFiles.size() > tc.maxMisreads) {
		std::cout << "FAILED: Read error (" << tc.name << "):";
		for (const auto& f : tc.misReadFiles)
			std::cout << "      " << toUtf8(f.first) << ": " << f.second << "\n";
		std::cout << "\n";
	}
}

static void doRunTests(BlackboxTestRunner& runner, const std::vector<TestReader>& readers,
	const std::string& directory, const char* format, int imageCount, const std::vector<TestCase>& tests)
{
	TestReader::clearCache();

	auto images = runner.getImagesInDirectory(std::wstring(directory.begin(), directory.end()));
	auto folderName = getBaseName(directory);
	
	if (images.size() != (size_t)imageCount)
		std::cout << "TEST " << folderName << " => Expected number of tests: " << imageCount
		     << ", got: " << images.size() << " => " << BAD << std::endl;

	for (auto& test : tests) {
		auto startTime = std::chrono::steady_clock::now();
		printf("%-20s @ %3d, total: %3d", folderName.c_str(), test.rotation, (int)images.size());
		for (size_t i = 0; i < readers.size(); ++i) {
			auto tc = test.tc[i];

			for (const auto& imagePath : images) {
				auto result = readers[i].read(buildPath(runner.pathPrefix(), imagePath), test.rotation);
				if (!result.format.empty()) {
					auto error = checkResult(runner.pathPrefix(), imagePath, format, result);
					if (!error.empty())
						tc.misReadFiles[imagePath] = error;
				} else {
					tc.notDetectedFiles.insert(imagePath);
				}
			}

			printPositiveTestStats((int)images.size(), tc);
		}

		auto duration = std::chrono::steady_clock::now() - startTime;
		printf(", time: %4d ms", (int)std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
		std::cout << std::endl;
	}
}

static std::pair<std::wstring, std::wstring> splitFileName(const std::wstring& filePath, wchar_t c)
{
	for (int i = (int)filePath.length() - 1; i >= 0; --i) {
		if (filePath[i] == c)
			return std::make_pair(filePath.substr(0, i), filePath.substr(i + 1));
		if (filePath[i] == '/' || filePath[i] == '\\')
			break;
	}
	return std::make_pair(filePath, std::wstring());
}

template <typename ReaderT>
static void doRunStructuredAppendTest(BlackboxTestRunner& runner, const std::vector<ReaderT>& readers,
	const std::string& directory, const char* format, int totalTests, const std::vector<TestCase>& tests)
{
	auto images = runner.getImagesInDirectory(std::wstring(directory.begin(), directory.end()));
	auto folderName = getBaseName(directory);

	std::map<std::wstring, std::vector<std::wstring>> imageGroups;
	for (const auto& path : images) {
		imageGroups[splitFileName(path, '-').first].push_back(buildPath(runner.pathPrefix(), path));
	}

	if (imageGroups.size() != (size_t)totalTests) {
		std::cout << "TEST " << folderName << " => Expected number of tests: " << totalTests
			<< ", got: " << imageGroups.size() << " => " << BAD << std::endl;
	}

	for (auto& test : tests) {
		printf("%-20s @ %3d, total: %3d", folderName.c_str(), test.rotation, (int)images.size());
		for (size_t i = 0; i < readers.size(); ++i) {
			auto tc = test.tc[i];

			for (const auto& imageGroup : imageGroups) {
				auto imagePath = imageGroup.first;
				auto result = readers[i].readMultiple(imageGroup.second, test.rotation);
				if (!result.format.empty()) {
					auto error = checkResult(runner.pathPrefix(), imageGroup.first, format, result);
					if (!error.empty())
						tc.misReadFiles[imagePath] = error;
				}
				else {
					tc.notDetectedFiles.insert(imagePath);
				}
			}

			printPositiveTestStats((int)imageGroups.size(), tc);
		}

		std::cout << std::endl;
	}
}


static DecodeHints createNewHints(DecodeHints hints, bool tryHarder, bool tryRotate)
{
	hints.setShouldTryHarder(tryHarder);
	hints.setShouldTryRotate(tryRotate);
	return hints;
}

static DecodeHints createHintsForFormat(const std::string& format)
{
	DecodeHints hints;
	auto f = BarcodeFormatFromString(format);
	if (f != BarcodeFormat::FORMAT_COUNT)
		hints.setPossibleFormats({ f });
	else
		std::cout << "\"" + format + "\" is unrecognized as barcode format" << std::endl;
	return hints;
}

static DecodeHints apply(DecodeHints hints, std::function<void (DecodeHints&)> f)
{
	f(hints);
	return hints;
}

BlackboxTestRunner::BlackboxTestRunner(const std::wstring& pathPrefix, const std::shared_ptr<ImageLoader>& imageLoader)
: _pathPrefix(pathPrefix), _imageLoader(imageLoader)
{
}

BlackboxTestRunner::~BlackboxTestRunner()
{
}

TestReader
BlackboxTestRunner::createReader(bool tryHarder, bool tryRotate, const std::string& format)
{
	return TestReader(_imageLoader, createNewHints(!format.empty() ? createHintsForFormat(format) : DecodeHints(), tryHarder, tryRotate));
}

void
BlackboxTestRunner::run(const std::set<std::string>& includedTests)
{
	auto hasTest = [&includedTests](const std::string& dir) {
		auto stem = getBaseName(dir);
		return includedTests.empty() || includedTests.find(stem) != includedTests.end() ||
		       includedTests.find(stem.substr(0, stem.size() - 2)) != includedTests.end();
	};

	auto runTests = [&](const std::string& directory, const char* format, int total,
					    const std::vector<TestCase>& tests, const DecodeHints& hints = DecodeHints()) {
		if (hasTest(directory)) {
			std::vector<TestReader> readers {
				TestReader(_imageLoader, createNewHints(hints, false, false)),
				TestReader(_imageLoader, createNewHints(hints, true, true))
			};
			doRunTests(*this, readers, directory, format, total, tests);
		}
	};

	auto runPdf417StructuredAppendTest = [&](const std::string& directory, const char* format, int total, const std::vector<TestCase>& tests) {
		if (hasTest(directory)) {
			Pdf417MultipleCodeReader reader(_imageLoader);
			doRunStructuredAppendTest<Pdf417MultipleCodeReader>(*this, { reader }, directory, format, total, tests);
		}
	};

	auto runQRCodeStructuredAppendTest = [&](const std::string& directory, const char* format, int total, const std::vector<TestCase>& tests) {
		if (hasTest(directory)) {
			QRCodeStructuredAppendReader reader(_imageLoader);
			doRunStructuredAppendTest<QRCodeStructuredAppendReader>(*this, { reader }, directory, format, total, tests);
		}
	};

	try
	{
		auto startTime = std::chrono::steady_clock::now();

		// clang-format off
		runTests("blackbox/aztec-1", "AZTEC", 13, {
			{ 13, 13, 0   },
			{ 13, 13, 90  },
			{ 13, 13, 180 },
			{ 13, 13, 270 },
		});

		runTests("blackbox/aztec-2", "AZTEC", 22, {
			{ 5, 5, 0   },
			{ 4, 4, 90  },
			{ 6, 6, 180 },
			{ 3, 3, 270 },
		});

		runTests("blackbox/datamatrix-1", "DATA_MATRIX", 21, {
			{ 21, 21, 0   },
			{  0, 21, 90  },
			{  0, 21, 180 },
			{  0, 21, 270 },
		});

		runTests("blackbox/datamatrix-2", "DATA_MATRIX", 18, {
			{ 18, 18, 0   },
			{  0, 18, 90  },
			{  0, 18, 180 },
			{  0, 18, 270 },
		});

		runTests("blackbox/codabar-1", "CODABAR", 11, {
			{ 11, 11, 0   },
			{ 11, 11, 180 },
		});

		runTests("blackbox/code39-1", "CODE_39", 4, {
			{ 4, 4, 0   },
			{ 4, 4, 180 },
		});

		runTests("blackbox/code39-2", "CODE_39", 2, {
			{ 2, 2, 0   },
			{ 2, 2, 180 },
		},
		apply(createHintsForFormat("CODE_39"), [](DecodeHints& h) { h.setShouldTryCode39ExtendedMode(true); }));

		runTests("blackbox/code39-3", "CODE_39", 17, {
			{ 17, 17, 0   },
			{ 17, 17, 180 },
		});

		runTests("blackbox/code93-1", "CODE_93", 3, {
			{ 3, 3, 0   },
			{ 3, 3, 180 },
		});

		runTests("blackbox/code128-1", "CODE_128", 6, {
			{ 6, 6, 0   },
			{ 6, 6, 180 },
		});

		runTests("blackbox/code128-2", "CODE_128", 40, {
			{ 36, 39, 0   },
			{ 36, 39, 180 },
		});

		runTests("blackbox/code128-3", "CODE_128", 2, {
			{ 2, 2, 0   },
			{ 2, 2, 180 },
		});

		runTests("blackbox/ean8-1", "EAN_8", 8, {
			{ 3, 3, 0   },
			{ 3, 3, 180 },
		});

		runTests("blackbox/ean13-1", "EAN_13", 31, {
			{ 27, 29, 0   },
			{ 24, 29, 180 },
		});

		runTests("blackbox/ean13-2", "EAN_13", 28, {
			{ 12, 17, 0   },
			{ 11, 17, 180 },
		});

		runTests("blackbox/ean13-3", "EAN_13", 55, {
			{ 53, 55, 0   },
			{ 55, 55, 180 },
		});

		runTests("blackbox/ean13-4", "EAN_13", 22, {
			{ 7, 14, 0   },
			{ 8, 14, 180 },
		});

		runTests("blackbox/ean13-5", "EAN_13", 18, {
			{ 0, 0, 0   },
			{ 0, 0, 180 },
		});

		runTests("blackbox/ean13-extension-1", "EAN_13", 5, {
			{ 5, 5, 0, 0, 0 },
			{ 5, 5, 1, 0, 180 },
		});

		runTests("blackbox/itf-1", "ITF", 14, {
			{ 14, 14, 0   },
			{ 14, 14, 180 },
		});

		runTests("blackbox/itf-2", "ITF", 13, {
			{ 13, 13, 0   },
			{ 13, 13, 180 },
		});

		runTests("blackbox/upca-1", "UPC_A", 15, {
			{ 10, 12, 0, 1, 0   },
			{ 12, 12, 0, 1, 180 },
		});

		runTests("blackbox/upca-2", "UPC_A", 52, {
			{ 28, 36, 0   },
			{ 29, 36, 180 },
		});

		runTests("blackbox/upca-3", "UPC_A", 21, {
			{ 7, 10, 0, 1, 0   },
			{ 8, 10, 0, 1, 180 },
		});

		runTests("blackbox/upca-4", "UPC_A", 19, {
			{ 9, 11, 0, 1, 0   },
			{ 9, 11, 0, 1, 180 },
		});

		runTests("blackbox/upca-5", "UPC_A", 35, {
			{ 20, 23, 0, 0, 0   },
			{ 22, 23, 0, 0, 180 },
		});
		
		runTests("blackbox/upca-6", "UPC_A", 19, {
			{ 0, 0, 0   },
			{ 0, 0, 180 },
		});

		runTests("blackbox/upca-extension-1", "UPC_A", 6, {
			{ 2, 4, 2, 2, 0 },
			{ 2, 4, 2, 2, 180 },
		});

		runTests("blackbox/upce-1", "UPC_E", 3, {
			{ 3, 3, 0   },
			{ 3, 3, 180 },
		});

		runTests("blackbox/upce-2", "UPC_E", 41, {
			{ 31, 35, 0, 1, 0   },
			{ 31, 35, 1, 1, 180 },
		});

		runTests("blackbox/upce-3", "UPC_E", 11, {
			{ 6, 8, 0   },
			{ 6, 8, 180 },
		});

		runTests("blackbox/rss14-1", "RSS_14", 6, {
			{ 6, 6, 0   },
			{ 6, 6, 180 },
		});

		runTests("blackbox/rss14-2", "RSS_14", 20, {
			{ 7, 10, 1, 1, 0   },
			{ 8, 10, 0, 1, 180 },
		});

		runTests("blackbox/rssexpanded-1", "RSS_EXPANDED", 32, {
			{ 32, 32, 0   },
			{ 32, 32, 180 },
		});

		runTests("blackbox/rssexpanded-2", "RSS_EXPANDED", 23, {
			{ 21, 23, 0   },
			{ 21, 23, 180 },
		});

		runTests("blackbox/rssexpanded-3", "RSS_EXPANDED", 117, {
			{ 117, 117, 0   },
			{ 117, 117, 180 },
		});

		runTests("blackbox/rssexpandedstacked-1", "RSS_EXPANDED", 64, {
			{ 59, 64, 0   },
			{ 59, 64, 180 },
		});

		runTests("blackbox/rssexpandedstacked-2", "RSS_EXPANDED", 7, {
			{ 2, 7, 0   },
			{ 2, 7, 180 },
		});

		runTests("blackbox/qrcode-1", "QR_CODE", 20, {
			{ 17, 17, 0   },
			{ 14, 14, 90  },
			{ 17, 17, 180 },
			{ 14, 14, 270 },
		});

		runTests("blackbox/qrcode-2", "QR_CODE", 34, {
			{ 31, 31, 0   },
			{ 30, 30, 90  },
			{ 30, 30, 180 },
			{ 30, 30, 270 },
		});

		runTests("blackbox/qrcode-3", "QR_CODE", 42, {
			{ 38, 38, 0   },
			{ 39, 39, 90  },
			{ 36, 36, 180 },
			{ 39, 39, 270 },
		});

		runTests("blackbox/qrcode-4", "QR_CODE", 48, {
			{ 36, 36, 0   },
			{ 35, 35, 90  },
			{ 35, 35, 180 },
			{ 35, 35, 270 },
		});

		runTests("blackbox/qrcode-5", "QR_CODE", 19, {
			{ 19, 19, 0   },
			{ 19, 19, 90  },
			{ 19, 19, 180 },
			{ 19, 19, 270 },
		});

		runTests("blackbox/qrcode-6", "QR_CODE", 15, {
			{ 15, 15, 0   },
			{ 14, 14, 90  },
			{ 13, 13, 180 },
			{ 14, 14, 270 },
		});

		runQRCodeStructuredAppendTest("blackbox/qrcode-7", "QR_CODE", 1, {
			{ 1, 1, 0   },
		});

		runTests("blackbox/pdf417-1", "PDF_417", 10, {
			{ 10, 10, 0   },
			{ 10, 10, 180 },
		});

		runTests("blackbox/pdf417-2", "PDF_417", 25, {
			{ 25, 25, 0   },
			{ 25, 25, 180 },
		});

		runTests("blackbox/pdf417-3", "PDF_417", 19, {
			{ 19, 19, 0   },
			{ 19, 19, 180 },
		});

		runPdf417StructuredAppendTest("blackbox/pdf417-4", "PDF_417", 3, {
			{ 3, 3, 0   },
		});

		runTests("blackbox/falsepositives-1", "NONE", 24, {
			{ 0, 0, 0, 0, 0   },
			{ 0, 0, 0, 0, 90  },
			{ 0, 0, 0, 0, 180 },
			{ 0, 0, 0, 0, 270 },
		});

		runTests("blackbox/falsepositives-2", "NONE", 25, {
			{ 0, 0, 0, 2, 0   },
			{ 0, 0, 0, 2, 90  },
			{ 0, 0, 0, 2, 180 },
			{ 0, 0, 0, 2, 270 },
		});
		// clang-format on

		auto duration = std::chrono::steady_clock::now() - startTime;
		std::cout << "Total time: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " ms." << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Internal error" << std::endl;
	}
}

}} // ZXing::Test
