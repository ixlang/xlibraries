##包 ： XCImg

## 提供动态验证码生成


## 说明

提供动态验证码生成


## github地址 https://github.com/ixlang/xlibrarys

使用方法

XCImg.VCodeGen gen  = new XCImg.VCodeGen("ABCD", 160, 40);
byte[] data = gen.getData();

获得bmp图像数据