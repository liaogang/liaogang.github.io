#!/bin/bash

if [ -a "get_html_title" ]; then
	echo ""
else
	gcc get_html_title.cpp -o get_html_title
fi


echo "---" > readme.md
echo "layout: post_center " >> readme.md
echo "title:  ONE问题 " >> readme.md
echo "tag: private  " >> readme.md
echo "permalink: /one/" >> readme.md
echo "---" >> readme.md
echo " " >> readme.md



for ((i=8; i<1700; ++i))  
do  

	if [ -a "$i" ]; then
		echo "finded $i"
	else
		echo "curl $i"
		curl -O http://wufazhuce.com/question/$i
	fi

	title=`./get_html_title $i`
	echo $title
	echo "1. [$title](http://wufazhuce.com/question/$i)  ">>readme.md

done  

cp readme.md ../one.md

