---
layout: post  
title: Network Extension相关
date: 2018-04-01  
categories: tech     
---  



AppEx attach to debug


        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)( 10 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
      
        
        
        NEPacketTunnelProviderEx* weakself = self;

        weakself.inner = [PacketTunnelProvider new];
        [weakself.inner startTunnelWithOptions:options completionHandler:completionHandler];
            
        });


{
    "lo0/ipv4" = "127.0.0.1";
    "lo0/ipv6" = "fe80::1";
    "pdp_ip0/ipv4" = "10.132.76.168";
    "utun0/ipv6" = "fe80::72c3:e25e:da85:b730";
}



{
    ""awdl0/ipv6"" = ""fe80::c018:9fff:feb2:988"";
    ""en0/ipv6"" = ""fe80::181a:2e43:f91b:db2b"";
    ""lo0/ipv4"" = ""127.0.0.1"";
    ""lo0/ipv6"" = ""fe80::1"";
    ""pdp_ip0/ipv4"" = ""10.48.10.210"";
    ""utun0/ipv4"" = ""192.168.99.2"";
}

{
    "lo0/ipv4" = "127.0.0.1";
    "lo0/ipv6" = "fe80::1";
    "pdp_ip0/ipv4" = "10.49.187.23";
    "utun0/ipv6" = "fe80::5748:5b5d:2bf0:658d";
    "utun1/ipv4" = "192.168.99.2"; //the real one
}

Not all utun interfaces are for VPN. There are other OS features that use utun interfaces.


#define IOS_CELLULAR    @"pdp_ip0"
#define IOS_WIFI        @"en0"
//#define IOS_VPN       @"utun0"
#define IP_ADDR_IPv4    @"ipv4"
#define IP_ADDR_IPv6    @"ipv6"

lo 回环接口(loop back) 或者 本地主机(localhost)
gif 通用 IP-in-IP隧道(RFC2893)
stf 6to4连接(RFC3056)
en 以太网或802.11接口
fw IP over FireWire(IEEE-1394), macOS特有
p2p Point-to-Point 协议
awdl airdrop peer to peer(一种mesh network), apple airdrop设备特有
bridge 第2层桥接
vlan 虚拟局域网络
pdp_ip 蜂窝数据连接
utn0 vpn

在VPN连上之后可以看到地址为192.168.2.2



    "awdl0/ipv6" = "fe80::e0fd:3fff:feb0:a707";
    "en0/ipv4" = "192.168.3.4";
    "en0/ipv6" = "fe80::1cc3:2d4d:cbbb:ab46";
    "en2/ipv4" = "169.254.210.227";
    "en2/ipv6" = "fe80::84a:88fa:c305:94ea";
    "lo0/ipv4" = "127.0.0.1";
    "lo0/ipv6" = "fe80::1";
    "pdp_ip0/ipv4" = "10.119.118.86";
    "utun0/ipv6" = "fe80::9c52:3706:6eda:ac27";
    "utun1/ipv4" = "192.168.2.2";

nw_network_agent_add_to_interface_internal Successfully added agent to "utun1"


ps -aux 

debug root 运行　进程 attach process


simpleserver 绑定的接口　utun　发出的dns没有得到回应　
https://forums.developer.apple.com/thread/69962

mac os 端口　转发　


    NEProxySettings *proxy = [NEProxySettings new];
    proxy.autoProxyConfigurationEnabled = YES;
    proxy.proxyAutoConfigurationJavaScript = [dymain pacSource];
    proxy.excludeSimpleHostnames = true;
    proxy.matchDomains = @[@""];
    networkSettings.proxySettings = proxy;

        networkSettings.IPv4Settings = [[NEIPv4Settings alloc] initWithAddresses:@[@"192.169.89.1"]  subnetMasks:@[@"255.255.255.0"]];

   "utun0/ipv6" = "fe80::9c52:3706:6eda:ac27"; //对应ipv6settings
    "utun1/ipv4" = "192.168.2.2"; //对应ipv4settings的地址

includedRoutes 匹配到这个数组的routes 将会routed through VPN 对应的虚拟接口，这里为utun1

excludedRoutes, 将会送到设备当前的主物理接口,wifi和cellar

NEIPv4Route.default() 为　0.0.0.0 




AppEx 里所依赖的库最好是以lib.a的形式，要不就添加到App的　Embeddeb binaries里。


使用charles 的socks代理时，最好把  http over socks关了


使用ProjectName-Swift.h
Project Defines modual 设置为YES,XCODE自动为swift生成x-Swift.h头文件。

targetManager.connection as? NETunnelProviderSession 来传消息sendProviderMessage 到provider

一个沙箱账号只能用在一台机器上　

xcode9 的　attach process 可以调试appex


/private/etc/apt/sources.list.d/wl.list

