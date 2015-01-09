---
layout: post
title:  cplusplus lambda functions
date:   2015-01-08-16:49  
categories: tech
---

所谓lambda，在c++中就是一个闭包函数:能够捕获域内变量的未命令的函数对象。

##语法  
    

|#|语法|  
|:--:|:--|  
|1|[ capture-list ] ( params ) mutable(optional) exception attribute -> ret { body }|
|2|[ capture-list ] ( params ) -> ret { body } |
|3| capture-list ] ( params ) { body } |
|4|[ capture-list ] { body } |

1. 完整声明。  

2.	lambda常量的声明:以复制的方式捕获对象，对象不可修改。  

3.	省略了尾部的返回类型:闭包的operator()的返回类型根据以下规则确定:  
			 c++14之前:  
      * if the body consists of nothing but a single `return` statement with an expression, the return type is the type of the returned expression (after rvalue-to-lvalue, array-to-pointer, or function-to-pointer implicit conversion) .  
      * 否则，返回类型为`void`。  
c++14或之后:  
			 The return type is deduced from return statements as if for a function whose return type is declared auto. 

4.	Omitted parameter list: function takes no arguments, as if the parameter list was () .


---
refrence from [cppreference](http://en.cppreference.com/w/cpp/language/lambda)  