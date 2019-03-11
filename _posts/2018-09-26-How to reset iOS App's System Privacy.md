---  
layout: post  
title: 清除iOS app的系统隐私记录  
date: 2018-09-26  
categories: tech
---



How to reset iOS App's System Privacy



### 环境

iOS9.2

### 动机

 怀疑抖音对小号的机器审核算法里有包含这个权限的探针。需要重置抖音app的权限，相册，相机，microphone, wifi , celluar等

### 临床表现

 未安装过抖音的第一次找开app时，iOS会出现一个弹框向用户提示是否受权，　而已安装过抖音的，则会提示用户此权限已完毕，需要用户手动去Preferences里去打开开关。　　



### 分析步骤

开始分析界面, 在Reveal里打开Preferences抖音的权限设置页面，里看到PSAppListController里有一个属性，相册的一项对应为PSSystemPolicyForApp。　再看它的一个属性\t_properties (NSMutableDictionary*): <__NSDictionaryM: 0x14f489800>　打印这个字典，显示为

```
@{"iconImage":#"<UIImage: 0x14f0c4b30>, {29, 29}","enabled":true,"value":true,"service":"kTCCServicePhotos"}
```

kTCCServicePhotos这个应该是关键，用ldid看Prefercences的授权字段，发现二个有点关系的字段

```
	<key>com.apple.private.tcc.allow</key>
	<array>
		<string>kTCCServiceAddressBook</string>
		<string>kTCCServicePhotos</string>
		<string>kTCCServiceCalendar</string>
		<string>kTCCServiceReminders</string>
		<string>kTCCServiceCamera</string>
		<string>kTCCServiceWillow</string>
		<string>kTCCServiceMicrophone</string>
	</array>
	<key>com.apple.private.tcc.manager</key>
	<true/>
```

这个tcc应该就是管理app授权的库了。基数据应该是跟keychain一样用sqlite的方式储存在系统的哪个地方。



把事先准备好的iOS92版本的dyld_shared_cache拖到hopper里,果然找到kTCCServicePhotos了这个字段。



在TCC.framework里没找到什么线索，用find命令搜到了他的sqlite文件.

```
iPhone-15:/ root# find . -name 'TCC'
./private/var/mobile/Library/TCC
```

用scp拷到电脑上来，用SQL Pro打开发现里面access表里就有我们想要找的字段。



| service           | client                  | client_type | allowed | prompt_count |
| ----------------- | ----------------------- | ----------- | ------- | ------------ |
| kTCCServicePhotos | com.ss.iphone.ugc.Aweme | 0           | 0       | 0            |
| kTCCServiceCamera | com.ss.iphone.ugc.Aweme | 0           | 0       | 1            |

那只要删掉对应的字段就算是清空了记录了.

```
delete from access where client = 'com.ss.iphone.ugc.Aweme'
```

保存下再拷回去试试.　备份，把原TCC.db改成TCC.db_backup,　再就是注意文件的权限是mobile:mobile

```
chown mobile:mobile TCC.db
```

找到相应的服务重启一下

```
iPhone-15:/ root# ps -e|grep TCC
 9205 ??         0:07.34 /System/Library/PrivateFrameworks/TCC.framework/tccd
20145 ttys000    0:00.00 grep TCC
```

找到 lanchd 对应的加载项重启

```
iPhone-15:/private/var/mobile/Library/TCC root# cd /System/Library/LaunchDaemons/
iPhone-15:/System/Library/LaunchDaemons root# ls -l|grep tcc
-rw-r--r-- 1 root wheel   562 May  4  2016 com.apple.tccd.plistl
iPhone-15:/System/Library/LaunchDaemons root# launchctl unload -w com.apple.tccd.plist
iPhone-15:/System/Library/LaunchDaemons root# launchctl load -w com.apple.tccd.plist
```


### 测试

重新打开Preferences发现，相应的项果然不见了，重新打开抖音，点击保存至相册，也弹出了第一次使用相册一样的提示。说明整个修改是正确的。

### 使用优化

接下来就做成服务以供客户程序调用就可以了. 

