---
layout: post
title:  shortcut key in 'player'  
date:   2014-12-16-03:16  
categories: tech
---

below:

* shortcut keys
* function command (string format)
* functions (function pointer)

map<#1,#2> in json format , will load from or save to a file.  
map<#2,#3> is init as the program startup.  


由于快捷键分为全局和非全局二种:
所以我把json格式设计为如下:

	{
		"local":
		{
			"super+shift+n":"new_window",
			"ctrl+a":"new_window",
			"f3":"show_search_window",
			"ctrl+f":"show_search_window"
		}
		,
		"global":
		{

		}
	}


