##类:ZXing

## 提供二维码生成与识别


## 说明

ZXing是一个开放源码的，用Java实现的多种格式的1D/2D条码图像处理库，它包含了联系到其他语言的端口。Zxing可以实现使用手机的内置的摄像头完成条形码的扫描及解码。

生成二维码:

if (ZXing.load()){ // 需要判断是否加载成功

	byte [] data  = ZXing.generateQRCodeToARGB8888Bitmap("1566", 100, true); 
	//返回BMP图像数据
	long hf = _system_.openFile("ll.bmp","w");
	_system_.writeFile(hf,data,0,data.length);
	_system_.closeFile(hf);
	//写入bmp图像文件
}


识别二维码:

String data  = ZXing.readQRCodeFromARGB8888Buffer(/** 32位ARGB8888图像数据 */, 0, /*图像宽*/,  /* 图像高 */);



## github地址 https://github.com/ixlang/xlibrarys
