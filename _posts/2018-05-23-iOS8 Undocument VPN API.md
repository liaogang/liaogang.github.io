---
layout: post  
title: iOS8 Undocument VPN API
date: 2018-05-23 
categories: tech     
---  



IPA里的neagentdataprovider.vpnplugin,在iOS安装app时会被拷到　一个另外的目录里面去。


neagent 会加载并执行此mach o dylib

installd 会打印出一条消息显示到相应目录.
 0x3d81000 -[MIContainer makeContainerLiveReplacingContainer:withError:]: Made container live for com.cisco.anyconnect.applevpn.plugin at /private/var/mobile/Containers/Data/VPNPlugin/BD579B95-919D-42D5-B135-916C6BB2522F

 0x3d81000 -[MIContainer makeContainerLiveReplacingContainer:withError:]: Made container live for com.cisco.anyconnect.applevpn.plugin at /private/var/mobile/Containers/Bundle/VPNPlugin/1BB13068-41D9-4FE2-BE70-B071492F5732


/private/var/mobile/Containers/Bundle/VPNPlugin/1BB13068-41D9-4FE2-BE70-B071492F5732



iOS Tun 网卡数据的流动

https://blog.csdn.net/naipeng/article/details/54972404


_Unwind_SjLj_Register
I believe it is exception handling. The problems mostly come up when people try to link to a C++ library built in a different compiler.



objc_sync_enter
objc_sync_exit
@synchronized

 dyld: lazy symbol binding failed: Symbol not found: _NEVirtualInterfaceSetReadMultipleIPPacketsHandler
      Referenced from: /var/mobile/Containers/Bundle/VPNPlugin/1BB13068-41D9-4FE2-BE70-B071492F5732/AnyConnectDataAgent.vpnplugin/AnyConnectDataAgent
      Expected in: /System/Library/Frameworks/NetworkExtension.framework/NetworkExtension
