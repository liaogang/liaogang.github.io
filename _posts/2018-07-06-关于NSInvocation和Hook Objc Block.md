---
layout: post  
title: 关于 NSInvocation 和 Hook Objc Block
date: 2018-07-06
categories: tech     
---  



## 怎样取得一个NSBlock的返回类型，参数? 函数签名



## 怎样动态替换这个NSBlock指向的函数?


使用　未公开的接口　L2TP ，在iOS9,10里面可以成功。在iOS8里面不能成功，
iOS8里，程序把生成的配置文件，序列化之后发给相应的XPC服务，被XPC Service拒绝。
但是在Preferences又可以生成相应的配置，成功保存。

可能的原因: 1. entitlements权限不够？
2. 再就要具体分析发送的数据了　。
  要把OS_xpc_object打印出来,  

  https://developer.apple.com/documentation/xpc/xpc_services_xpc.h?language=objc

  

```
_xpc_copy_description

 xpc_dictionary_set_data

 xpc_dictionary_set_int64(r0, "config-operation", 0x3);

NSKeyedArchiver  initForWritingWithMutableData

[r0 setRequiresSecureCoding:0x1];

 r4 = [[NSString stringWithUTF8String:"config-object"] retain];

 [r0 encodeObject:*(r11 + 0x18) forKey:r4];

                            

                            

 [r0 finishEncoding];

r0 = xpc_dictionary_create(0x0, 0x0, 0x0);

```


   不是权限问题，数据也是一样的，在自己的app里不行，在Preferences可以保存。

看样子，要分析一下XPC Servcier 实现才行。

## 问题: 怎么找到对应的XPC Service呢　             

XPC的数据最终是由NEHelper发出去的。从NEHelper分析起

NEHelper里有一个单例

```
-[NEHelper connection]()

stack[2024] = xpc_connection_create_mach_service("com.apple.nehelper", *(stack[2025] + *0x2fe2feac), 0x2); 

```



从这个可看到远端服务的名字叫　`com.apple.nehelper` 

``

The  name of the remote service with which to connect. The service name must  exist in a Mach bootstrap that is accessible to the process and be  advertised in a launchd.plist.

在/Library/LaunchDaemons发现一个文件`com.apple.nehelper.plist`

文件里果然有MachServices一项，值为com.apple.nehelper

Program一项的值为 /usr/libexec/nehelper

用ldid 看它的权限

```
<?xml version="1.0" encoding="UTF-8"?>

<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">

<plist version="1.0">

<dict>

	<key>com.apple.SystemConfiguration.SCPreferences-write-access</key>

	<array>

		<string>VPN-com.apple.neplugin.IKEv2.plist</string>

	</array>

	<key>com.apple.managedconfiguration.vpn-profile-access</key>

	<true/>

	<key>com.apple.private.neconfiguration-write-access</key>

	<true/>

	<key>com.apple.private.necp.match</key>

	<true/>

	<key>com.apple.private.necp.policies</key>

	<true/>

	<key>com.apple.private.nehelper.privileged</key>

	<true/>

	<key>keychain-access-groups</key>

	<array>

		<string>apple</string>

		<string>com.apple.identities</string>

		<string>com.apple.certificates</string>

	</array>

</dict>

</plist>

```



果然有写VPN配置的权限。用hopper打开分析分析看它接受信息的部分.

应该就是NEHelperServer 这个类了

先用KNHook 来hook一个这个类，打印它的信息看看

sub_d118 

sub_d118 



-[NEHelperConfigurationManager saveConfigurationToProfile:] 这个方法失败了

```
void * -[NEHelperConfigurationManager saveConfigurationToProfile:](void * self, void * _cmd, void * arg2) {
    r7 = (sp - 0x14) + 0xc;
    sp = sp - 0x3c;
    r10 = self;
    r6 = [arg2 retain];
    r5 = [[arg2 payloadInfo] retain];
    r7 = r7;
    r8 = [[r5 profileUUID] retain];
    [r5 release];
    r4 = [arg2 copyProfileDictionary];
    [r6 release];
    if (r4 != 0x0) {
            stack[2037] = r10;
            r7 = r7;
            r11 = [[NSPropertyListSerialization dataWithPropertyList:r4 format:0xc8 options:0x0 error:sp + 0x18, stack[2035]] retain];
            r0 = 0x0;
            if (r11 != 0x0) {
                    stack[2035] = r4;
                    stack[2036] = r8;
                    r8 = [r0 retain];
                    r10 = [[MCProfileConnection sharedConnection] retain];
                    r4 = [[stack[2037] bundleID] retain];
                    stack[2038] = r8;
                    r1 = @selector(queueFileDataForAcceptance:originalFileName:forBundleID:outError:);
                    r0 = r10;
                    asm { strd       r4, r5, [sp, #0x34 + var_34] };
                    r6 = [objc_msgSend(r0, r1) retain];
                    r5 = [stack[2038] retain];
                    [r8 release];
                    [r4 release];
                    [r10 release];
                    if (r5 == 0x0) {
                            r8 = stack[2036];
                            r4 = stack[2035];
                            if (r6 != 0x0) {
                                    if (r8 != 0x0) {
                                            [NEHelperConfigurationManager addPendingIngestionProfileUUID:r8];
                                            [NEHelperConfigurationManager addPendingIngestionProfileUUID:r8];
                                    }
                                    [NEHelperConfigurationManager addPendingIngestionProfileUUID:r6];
                                    r5 = 0x0;
                            }
                    }
                    else {
                            r8 = stack[2036];
                            r4 = stack[2035];
                    }
            }
            else {
                    r6 = 0x0;
                    r11 = [r0 retain];
                    r5 = [[stack[2037] clientName] retain];
                    NELogObjC();
                    [r11 release];
                    [r5 release];
                    r5 = [[NSError errorWithDomain:@"NEConfigurationErrorDomain" code:0x8 userInfo:r6] retain];
                    r11 = 0x0;
            }
    }
    else {
            r4 = [[r10 clientName] retain];
            NELogObjC();
            [r4 release];
            r4 = 0x0;
            r5 = [[NSError errorWithDomain:@"NEConfigurationErrorDomain" code:0x8 userInfo:r4] retain];
            r6 = 0x0;
            r11 = 0x0;
    }
    [r8 release];
    [r6 release];
    [r4 release];
    [r11 release];
    r0 = r5;
    r0 = [r0 autorelease];
    return r0;
}
```



根据之前的报错 not saved: Error Domain=NEConfigurationErrorDomain Code=8 "invalid configuration operation request" UserInfo=0x17a9d480 {NSLocalizedDescription=invalid configuration operation request} 

定位是在这个方法里哪条路径上报出的.







