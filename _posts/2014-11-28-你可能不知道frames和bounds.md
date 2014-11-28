---
layout: post  
title:  你可能不知道frames和bounds  
date:   2014-11-28-2:32  
categories: tech  
---  

View有两个属性:frame和bound.  

frame表示的view坐标位置及大小是基于父坐标系的。  

bound表示的view坐标位置及大小是基于这个view自己的坐标系的。  

如果使用frame属性，那必须小心，这些值是表示子视图在父视图中的位置，包括旋转和缩放。  

这意味着使用self.view.bounds.size可以相对可靠的获得一个视图控制器的视图尺寸。  

![](/resource/img/你可能不知道frames和bounds/a.png)

如果你在上面的绿色的视图控制器里，然后尝试添加一个子视图到绿色的视图里，如果你使用frame来获取绿色视图的坐标位置，你会得到怪异的结果。  

	hotNewSubview.frame = self.view.frame;  //HORRIBLY, HORRIBLY WRONG
	hotNewSubview.frame = self.view.bounds; //Better, but still not good

`bounds`的`origins`通常情况下都是0。都不一定全都是0。  
坐标变换可以影响它自己的`origin`。比如在一个滚动视图里，向上滚动10个单位，那它的`bounds origin`就成为了(0,-10)。  

Objective-c开发者经常使用self.view.frame或self.view.bounds来创建一个新的子视图,用来占据整个父视图可见空间。这是错误的,我们来看看:  

	hotNewSubview.frame = self.view.frame;  //HORRIBLY, HORRIBLY WRONG
	hotNewSubview.frame = self.view.bounds; //Better, but still not perfect
	hotNewSubview.frame = CGRectMake(0, 0, 
	    CGRectGetWidth(self.view.bounds), 
	    CGRectGetHeight(self.view.bounds)); //Best  


所以结论是，你应该理解自己所做的事。View hierarchies占了构建app的一大部分内容。确保你完全理解视图及其坐标系统。　　

***
[You Probably Don't Understand frames and bounds](http://ashfurrow.com/blog/you-probably-dont-understand-frames-and-bounds)