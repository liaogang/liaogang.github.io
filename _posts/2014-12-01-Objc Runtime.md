---
layout: post
title:  Objc Runtime
date:   2014-12-01-11:45  
categories: tech
---
## Messaging  

本章介绍了message expressions转换成objc_msgSend函数调用的。你怎么来参考方法的名字。然后解释了你可以如何利用objc_msgSend,如何规避动态绑定。  

### The objc_msgSend Function  

在Objective-C里，消息是在运行的时候才绑定到具体实现的。  

当你写出一句发送消息的Objective-C代码:  

`[receiver message]`  

编译器就会生成一个objc_msgSend的函数调用:  

`objc_msgSend(receiver,selector);`  
`objc_msgSend(receiver, selector, arg1, arg2, ...)`  

这个消息函数做了用来动态绑定的一切事情:

* 首先它找到selector到对应的具体方法实现。由于有相同名字方法可能在不同的类里对应不同的实现。它能准确的找到receiver的类所对应的实现。
* 然后调用例程，传入对象receiver还有任何指定的参数。
* 最后，它传回例程的返回值。

发送消息的关键依赖于编译器为每一个类和对象的所打造的特殊结构。每一个类的结构包含两个重要的元素:  

* 一个指向父类的指针
* 一个dispatch table.这个表记录了每一个类方法的地址。

当一个新的对象被创建时，对应的内存被分配，成员变量被初始化。对象的最开始的变量是一个指向类结构的指针。这个指针就叫isa,它给出了来访问其类结构路径，通过这个类结构来访问父类的路径:  

![](/resource/img/Objc Runtime/messaging1.gif)

When a message is sent to an object, the messaging function follows the object’s isa pointer to the class structure where it looks up the method selector in the dispatch table. If it can’t find the selector there, objc_msgSend follows the pointer to the superclass and tries to find the selector in its dispatch table. Successive failures cause objc_msgSend to climb the class hierarchy until it reaches the NSObject class. Once it locates the selector, the function calls the method entered in the table and passes it the receiving object’s data structure.

This is the way that method implementations are chosen at runtime—or, in the jargon of object-oriented programming, that methods are dynamically bound to messages.

To speed the messaging process, the runtime system caches the selectors and addresses of methods as they are used. There’s a separate cache for each class, and it can contain selectors for inherited methods as well as for methods defined in the class. Before searching the dispatch tables, the messaging routine first checks the cache of the receiving object’s class (on the theory that a method that was used once may likely be used again). If the method selector is in the cache, messaging is only slightly slower than a function call. Once a program has been running long enough to “warm up” its caches, almost all the messages it sends find a cached method. Caches grow dynamically to accommodate new messages as the program runs.

## Dynamic Method Resolution  

这一章描述了如何动态为一个方法提供一个具体实现  
 
### Dynamic Method Resolution  

在一些情况下，你可能想要动态的改变一个方法的具体实现。比如，一个用`@dynamic`修饰的成员属性:  

`@dynamic propertyName;`  

这会告诉编译器这个属性的对应方法，给被动态的绑定。  

You can implement the methods `resolveInstanceMethod:` and `resolveClassMethod:` to dynamically provide an implementation for a given selector for an instance and class method respectively.  

一个Objctive-C方法其实简单的等于一个C 函数。它需要至少两个参数:`self`和`_cmd`。　你可以用函数`class_addMethod`来为一个类添加一个方法:  

	void dynamicMethodIMP(id self, SEL _cmd) 
	{
	    // implementation ....
	}  
	



## Refrence  

[Objective-C Runtime Reference](https://developer.apple.com/library/mac/documentation/Cocoa/Reference/ObjCRuntimeRef/index.html)  
[Objective-C Runtime Programming Guide](https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtHowMessagingWorks.html)  
[Let's Build objc_msgSend](https://mikeash.com/pyblog/friday-qa-2012-11-16-lets-build-objc_msgsend.html)  
[stack overflow](http://stackoverflow.com/questions/15309497/understanding-objective-c-runtime)  

以下定义取自 <objc/objc.h>:  

	/// An opaque type that represents an Objective-C class.
	typedef struct objc_class *Class;

	/// Represents an instance of a class.
	struct objc_object {
	    Class isa;
	};
	
	/// A pointer to an instance of a class.
	typedef struct objc_object *id;
	#endif

	/// An opaque type that represents a method selector.
	typedef struct objc_selector *SEL;

	/// A pointer to the function of a method implementation. 
	#if !OBJC_OLD_DISPATCH_PROTOTYPES
	typedef void (*IMP)(void /* id, SEL, ... */ ); 
	#else
	typedef id (*IMP)(id, SEL, ...); 
	#endif


