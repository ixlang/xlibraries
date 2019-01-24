##包 ： Runtime

## 运行时 进程处理

## 依赖包: XPlatform ; FileStream ; FileSystem 

## 说明

用于运行时进程的处理

## 用法示例


	List<Runtime.OSProcess> lists =  Runtime.OSProcess.listProcesses();

	List.Iterator<Runtime.OSProcess> iter = lists.iterator();
    
    while (iter.hasNext()){
		Runtime.OSProcess p = iter.next();
        _system_.consoleWrite(p.getName() + "[" + p.getId() +"] " + p.getPath());
    }


## github地址 https://github.com/ixlang/xlibrarys
