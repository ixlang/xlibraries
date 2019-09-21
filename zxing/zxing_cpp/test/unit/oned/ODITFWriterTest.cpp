/*
* Copyright 2017 Huy Cuong Nguyen
* Copyright 2016 ZXing authors
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
#include "gtest/gtest.h"
#include "BitMatrix.h"
#include "BitMatrixUtility.h"
#include "oned/ODITFWriter.h"

using namespace ZXing;
using namespace ZXing::OneD;

namespace {
	std::string Encode(const std::wstring& input)
	{
		auto result = Utility::ToString(ITFWriter().encode(input, 0, 0), '1', '0', false);
		return result.substr(0, result.size() - 1);	// remove the \n at the end
	}
}

TEST(ODITFWriterTest, Encode)
{
    EXPECT_EQ(Encode(L"00123456789012"),
              "0000010101010111000111000101110100010101110001110111010001010001110100011"
              "100010101000101011100011101011101000111000101110100010101110001110100000");
}

TEST(ODITFWriterTest, EncodeIllegalCharacters)
{
	EXPECT_THROW({ Encode(L"00123456789abc"); }, std::invalid_argument);
}
