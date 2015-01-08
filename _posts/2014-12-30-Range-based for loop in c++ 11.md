---
layout: post
title:  Range-based for loop in c++ 11  
date:   2014-12-30-02:54  
categories: tech
---

from [cppreference.com](http://en.cppreference.com/w/)  

[C++11 range-based for loops](http://www.cprogramming.com/c++11/c++11-ranged-for-loop.html)  

执行在一个区域上的遍历。  

##Range-based for loops 的基本语法  

	vector<int> vec;
	vec.push_back( 10 );
	vec.push_back( 20 );
	 
	for (int i : vec )
	{
	    cout << i;
	}
		
也可以使用 `auto` 关键字  

	map<string, string> address_book;
	for ( auto address_entry : address_book )
	{
	            cout  << address_entry.first << " < " << address_entry.second << ">" << endl;
	}

##修改Vector的内容  

	vector<int> vec;
	vec.push_back( 1 );
	vec.push_back( 2 );
	 
	for (int& i : vec )
	{
	    i++; // increments the value in the vector
	}
	for (int i : vec )
	{
	    // show that the values are updated
	    cout << i << endl;
	}
		
##What does it mean to have a range?  
`Strings`,`arrays`, 和所有的`STL`容器。