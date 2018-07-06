---
layout: post  
title: ios的app组织成deb包安装到用户空间
date: 2018-04-14 
categories: tech     
---  

ios　app制作成debian安装包有二种方法:
第一种，参考[iOS App转换为deb格式]，这种方法有几个缺点 

* 即安装目录在`/Applications`下面，占用系统分区的空间 
* 各种dylib找不到frameworks的问题
* 再就是appex和app不能通过app group来共享数据

第二种，把app制作成ipa,通过[IPA installer cmd](http://moreinfo.thebigboss.org/moreinfo/depiction.php?file=ipainstallerconsoleDp) 来安装。
	
* IPAInstaller是通过系统的安装入口来安装app的
	 
>>>app制作成ipa的步骤: 
>>> 新建Payload文件夹,放入demo.app,压缩Payload成zip包。改名Payload.zip成demo.ipa
    
    	 ipainstaller /var/mobile/Media/SimpleTunnel.ipa
    	 ipainstaller -u com.abuyun.http.tunnel 

* 添加依赖，通过[appsync](https://github.com/angelXwind/AppSync) 来无视iOS的签名校验

    	Depends:  mobilesubstrate, com.autopear.installipa,net.angelxwind.appsyncunified 

	
		
		


