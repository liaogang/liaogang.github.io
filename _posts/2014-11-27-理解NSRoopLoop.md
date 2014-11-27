---
layout: post  
title:  理解RoopLoop  
date:   2014-11-27  
categories: tech  
---  
`Run Loop`是一个抽象的概念，它提供了一种机制来处理系统的输入源（sockets,端口，文件，键盘，鼠标，定时器，等等）.如同windows消息机制里面的消息源一样。  
每一个`NSThread`都有它自己的`Run Loop`,可以通过`currentRunLoop`方法来访问。  　
通常你无需直接访问`Run Loop`，虽然有一些（网络）组件，可以允许您指定用来I/O处理的`Run Loop`。  

##Run Loop 解剖  
Run Loop其实非常像它字面上的意思。就是一个循环你的线程进入然后处理各种消息。  
Run loop接收来源于两种源的事件:*Input sources*和*Timer sources*。Input sources派发异步的事件，可能来自另一个线程或应用程序。Timer sources派发同步消息， occurring at a scheduled time or repeating interval.

![](/resource/img/理解RoopLoop/理解RoopLoop.png)

##Run Loop 模式
Table 3-1  Predefined run loop modes　　

| Mode  | Name | Description |  
|:----------------------|:--------------|:------------|
|Default                |NSDefaultRunLoopMode (Cocoa)  kCFRunLoopDefaultMode (Core Foundation)|几乎包括所有输入源 |
|Connection|NSConnectionReplyMode (Cocoa)|处理NSConnection事件，属于系统内部，用户基本不用|
|Modal|NSModalPanelRunLoopMode (Cocoa)|处理modal panels|
|Event tracking|NSEventTrackingRunLoopMode (Cocoa)|如组件拖动输入源 |
|Common modes|NSRunLoopCommonModes (Cocoa)  kCFRunLoopCommonModes (Core Foundation)|NSRunLoopCommonModes 这是一组可配置的通用模式。将input sources与该模式关联则同时也将input sources与该组中的其它模式进行了关联。|


##参考
[Threading Programming Guide](https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html)  
[
自己调研的一些关于NSRunLoop与NSTimer的知识 ](http://blog.csdn.net/ioswyl88219/article/details/16996531)
