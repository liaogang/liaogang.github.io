---
layout: post
title:  learning lisp  
date:   2015-03-18
categories: learning
---

##环境配置

在mac里brew里安装clisp.  
在安装目录下面有个bin/clisp.  
可以直接进入交互前端,或指定要输入的文件.  
具体用法: [clisp](file:///Users/liaogang/homebrew/Cellar/clisp/2.49/share/doc/clisp/clisp.html)  


教程: [ANSI Common Lisp 中文版](http://acl.readthedocs.org/en/latest/zhCN/index.html)  

简明lisp参考手册: [Simplified Common Lisp reference](http://jtra.cz/stuff/lisp/sclr/allprint.html)  

##怎样注释

在scheme里注释一行可以使用分号: `;`  

##常用函数  

###null  

###not  

###car  

###cons  

###cdr  

###format:  

	语法:
	format 目录 控制字符串 参数 (0个或几个) ==> string or nil
	参数描述:
	destination: t,nil,stream or string with fill-pointer
	
	
###do 宏  

(variable initial update)

