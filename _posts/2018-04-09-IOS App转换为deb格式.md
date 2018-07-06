---
layout: post 
title: IOS App转换为deb格式及获取ROOT权限
date: 2018-04-09  
categories: tech     
---  

## debian 文件组织格式为

    
    /Applications/SimpleTunnel.app/
    /DEBIAN/control
    /DEBIAN/postinst		


## 使用手机里的dpkg-deb 命令打包 (手机设备本来环境与目标安装环境一致)

先修改几个程序文件的属性

    chmod 755 DEBIAN/*
    chmod 755 Applications/SimpleTunnel.app/PlugIns/PacketTunnel.appex/PacketTunnel
    chmod 755 Applications/SimpleTunnel.app/SimpleTunnel


生成deb

    dpkg-deb -b deb/ com.abuyun.ios.deb

## 修改app的运行权限为ROOT[^ios-run-application-with-root-privileges]

1. 修改Info.plist里面的Executable file键值指向脚本fake文件

    fake脚本指向原来的主程序执行文件

        #!/bin/bash
        root=$(dirname "$0")
        exec "${root}"/SimpleTunnel


2. 在postinst中 
 
         chmod 0775 fake 
         chown root:wheel SimpleTunnel 
         chmod 6775 SimpleTunnel  
 
3. main() function add setuid(0)
	
        if (setuid(0) == 0 && setgid(0) == 0)
        {
            NSLog(@"提权成功.");
        }
        else{
            NSLog(@"提权失败");
        }





[^ios-run-application-with-root-privileges]:  http://blog.ib-soft.net/2013/01/ios-run-application-with-root-privileges.html