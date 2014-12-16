---
layout: post    
title:  ARC Retain Cycles in Blocks  
date:   2014-12-09-11:00  
categories: tech  
---  
##block对象
所谓[block对象](https://developer.apple.com/library/mac/documentation/General/Conceptual/DevPedia-CocoaCore/Block.html)


##Use __block Variables to Share Storage
如果你想能够改变一个block内部捕捉到的变量的值，你可以使用_block修饰符来改变原始变量的声明。这意味着这个变量生存期延长到了blocks内部。


所谓Retain cycle是一种循环，当一个对象A保留了对象B的一个引用，同时B也保留A的一个引用。这种情况下，两个对象都不能被释放。从面向对象的角度来看，这也是一个不合逻辑的现象。A包含了B,B不可能同时也包含了A。  

这样一来，这两个对象占用的内存都得不到释放，直到程序终止。  

这本来跟blocks没有什么关系。　　

	[myArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop){　　
	   [self doSomethingWithObject:obj];　　
	}];　　

这个Block保留了self的引用,但是self没有保留block的引用。当其中一个被释放时，没有循环生成，一切都会正常的被释放。  

在非自动计数模式下，_block id x;并没有使x引用计数加一. 在ARC模式下，_block id x;默认使x的引用计数加一。若要在ARC模式下获得非自动计数的行为，你应该使用_unsafe_unretained _block id x;就像它的修饰名字_unsafe_unretained一样，它可能造成野指针的危险行为。所以两个更好的解决方案是使用_weak，或设置_block值为nil来打破Retain Cycle。　　
