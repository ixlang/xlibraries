##包 ： FileStream

## 文件输出流 FileOutputStream 

## 文件输入流 FileInputStream 

## 依赖包:XPlatform

## 说明

用于文件读写, 支持在Windows的UTF8<->GB1080转换

## 用法示例

using { 
	FileStream;
};


try{
	FileOutputStream fos = new FileOutputStream("/home/user/a.file");
	...
	fos.close();
}catch(Exception e){
	

}

## 注意：如不主动调用close， 则close方法会在对象被GC时调用，但GC时间可能无法确定, 则会导致在GC之前文件被占用的情况.

## github地址 https://github.com/ixlang/xlibrarys
