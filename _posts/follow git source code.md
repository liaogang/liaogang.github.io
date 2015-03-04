---
layout: post
title:  Using Last.fm API  
date:   2015-03-03-09:41  
categories: tech
---

##bref
git 最开始是由几个简洁的程序粘合而成的。

init-db
commit-tree
read-tree
write-tree
read-cache
update-cache
show-diff

##init-db
init-db 在当前目录建立一个数据库
即.dircache/objects/







获取sha1对应的文件名，在SHA1_FILE_DIRECTORY环境变量里，或默认的.dircache/objects里
char *sha1_file_name(unsigned char *sha1)  

把buf写入到sha1z对应的文件中
int write_sha1_buffer(unsigned char *sha1, void *buf, unsigned int size)  

压缩buf，存入到对应的sha1 cache里去。
int write_sha1_file(char *buf, unsigned len)

add 'path' to database
static int add_file_to_cache(char *path)

