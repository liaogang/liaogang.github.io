---
layout: post
title:  "New in cplusplus"
date:   2014-08-07  
categories: mine
---

#关于 C++ 里的 New
1.  new expression : new 表达式  
2.  operator new : 操作符函数,用来分配内存.  
3.  placement new :定位表达式,用来初始化已分配的内存.  
 
#例 
第一种用法 : `type a = new type; `   
第二种用法: `void *a = ::operator new(int size);`   
第三种用法:
`new (place address) type [initialiser list]  `   

    //如:  
	void * a = malloc (xxx);)  
	new (a) a_type ; 

