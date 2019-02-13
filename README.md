# AppServer

## 1. 设计理念
    为了减少多线程带来的痛苦,  AppServer根据单线程的方法来设计分布式的服务器。
    根据众多模块功能组件自己的服务器。
    其中，模块相对独立。这样可以把具体某个功能放到一个模块内。每个模块以共享库(*.so)的形式存在。 
    并且，模块通过暴露接口(Interface)的形式实现模块间的通信。

## 2. 目录结构
    3rd, 存放第三方库安装包
    Bin, 生成目录
    IGLibProject, 插件工程目录
    IGMainProject, 加载插件工程目录
    IGTest, 网络代码测试目录   
   
## 3. 模块功能
    功能模块存放在"插件工程目录", 分别有如下功能插件:
    - 网络模块 (doing ...)
    - 数据库模块 (to do ...)
    - 日志模块 (to do ...)
    
## 4. 运行环境
    gcc version 4.8 (C++11)
    macOS, CenterOS
    libevent 2.1.8
    rapidxml 1.13
    
    
