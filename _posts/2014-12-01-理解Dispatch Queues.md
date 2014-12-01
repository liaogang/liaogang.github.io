---
layout: post  
title:  理解Dispatch Queues  
date:   2014-12-01  
categories: tech  
---  

Grand Central Dispatch (GCD) dispatch queues 是一个处理任务的强大的工具。 Dispatch queues 让你处理任务的一块代码异步或同步地。与对应的线程代码相比，更加易用;执行任务时，效率更高。  

##关于Dispatch Queues
你可以定制相应的代码，使用function或block object，来把一个任务加入dispatch queue.　　

A dispatch queue is an object-like structure that manages the tasks you submit to it. All dispatch queues are first-in, first-out data structures.所以任务总是按你添加的顺序先后执行。GCD提供一些dispatch queues,但你也可以自己创建，来完成特殊的任务。  

|类型        |描述                                          |
|:----------|:---------------------------------------------|
|Serial,串行                |Serial 又称private dispatch queues，每个时刻只执行一个任务。Serial queue通常用于同步访问特定的资源。当你创建多个Serial queue时，虽然它们各自是同步执行的，但Serial queue与Serial queue之间是并发执行的。|
|Concurrent,并行| Concurrent 又称global dispatch queue，可以并发地执行多个任务。你只能使用系统提供的4种global dispatch queue，不能自己创建。（iOS 5.0之前是3种）。|
|Main dispatch| Main dispatch queue 它是全局可用的serial queue，它是在应用程序主线程上执行任务的。|

When it comes to adding concurrency to an application, dispatch queues provide several advantages over threads. The most direct advantage is the simplicity of the work-queue programming model. With threads, you have to write code both for the work you want to perform and for the creation and management of the threads themselves. Dispatch queues let you focus on the work you actually want to perform without having to worry about the thread creation and management. Instead, the system handles all of the thread creation and management for you. The advantage is that the system is able to manage threads much more efficiently than any single application ever could. The system can scale the number of threads dynamically based on the available resources and current system conditions. In addition, the system is usually able to start running your task more quickly than you could if you created the thread yourself.　　

Although you might think rewriting your code for dispatch queues would be difficult, it is often easier to write code for dispatch queues than it is to write code for threads. The key to writing your code is to design tasks that are self-contained and able to run asynchronously. (This is actually true for both threads and dispatch queues.) However, where dispatch queues have an advantage is in predictability. If you have two tasks that access the same shared resource but run on different threads, either thread could modify the resource first and you would need to use a lock to ensure that both tasks did not modify that resource at the same time. With dispatch queues, you could add both tasks to a serial dispatch queue to ensure that only one task modified the resource at any given time. This type of queue-based synchronization is more efficient than locks because locks always require an expensive kernel trap in both the contested and uncontested cases, whereas a dispatch queue works primarily in your application’s process space and only calls down to the kernel when absolutely necessary.　　

尽管你会指出，两个运行在一个serial queue中的任务不是并发的,　但你要记得，如果两个线程需要访问同一个锁，那并发就没有意义了。更重要的是，线程模型要求创建两个线程，它占用了内核和用户空间资源。Dispatch queues则不需要，并且它所使用的线程可以保持工作而不堵塞。  

需要记住的一些重要的关于dispatch queues事项包括如下:  
* 不同的Dispatch queues之间可以并发地执行任务。 序列化执行是对同一个dispatch queue里的任务而言。
* 系统会决定同一时间并发的最大数额。因此，一个包含100个queues里的100个任务的应用，可能不会全部都是并发执行的（除非系统有100以上的有效芯）。  
* 系统选择一个新任务去开始执行时，它会考虑该任务列队的优先级。
* Tasks in a queue must be ready to execute at the time they are added to the queue. (If you have used Cocoa operation objects before, notice that this behavior differs from the model operations use.) 
* Private dispatch queues 是一个基于计数的对象。要注意dispatch sources也可以被绑定到一个queue，使其引用计数加一。Thus, you must make sure that all dispatch sources are canceled and all retain calls are balanced with an appropriate release call. For more information about retaining and releasing queues, see Memory Management for Dispatch Queues. For more information about dispatch sources, see About Dispatch Sources. 

For more information about interfaces you use to manipulate dispatch queues, see Grand Central Dispatch (GCD) Reference.

##Queue-Related Technologies

##Implementing Tasks Using Blocks

##Creating and Managing Dispatch Queues

###Getting the Global Concurrent Dispatch Queues

Although dispatch queues are reference-counted objects, you do not need to retain and release the global concurrent queues. Because they are global to your application, retain and release calls for these queues are ignored. Therefore, you do not need to store references to these queues. You can just call the dispatch_get_global_queue function whenever you need a reference to one of them.

##Creating Serial Dispatch Queues

###Getting Common Queues at Runtime

##Memory Management for Dispatch Queues

Note: You do not need to retain or release any of the global dispatch queues, including the concurrent dispatch queues or the main dispatch queue. Any attempts to retain or release the queues are ignored.

##Storing Custom Context Information with a Queue

##Providing a Clean Up Function For a Queue

---

[IOS Developer LIbrary --> Concurrency Programming Guide
](https://developer.apple.com/library/ios/documentation/General/Conceptual/ConcurrencyProgrammingGuide/OperationQueues/OperationQueues.html)
