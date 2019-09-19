---
layout: post  
title: 关于 NSInvocation 和 Hook Objc Block
date: 2018-07-06
categories: tech     
---  



## 怎样取得一个nsblock的返回类型，参数? 函数签名



## 怎样动态替换这个nsblock指向的函数?


使用　未公开的接口　l2tp ，在ios9,10里面可以成功。在ios8里面不能成功，
ios8里，程序把生成的配置文件，序列化之后发给相应的xpc服务，被xpc service拒绝。
但是在preferences又可以生成相应的配置，成功保存。

可能的原因: 1. entitlements权限不够？
2. 再就要具体分析发送的数据了　。
  要把os_xpc_object打印出来,  

  https://developer.apple.com/documentation/xpc/xpc_services_xpc.h?language=objc

  

```
_xpc_copy_description

 xpc_dictionary_set_data

 xpc_dictionary_set_int64(r0, "config-operation", 0x3);

nskeyedarchiver  initforwritingwithmutabledata

[r0 setrequiressecurecoding:0x1];

 r4 = [[nsstring stringwithutf8string:"config-object"] retain];

 [r0 encodeobject:*(r11 + 0x18) forkey:r4];

                            

                            

 [r0 finishencoding];

r0 = xpc_dictionary_create(0x0, 0x0, 0x0);

```


   不是权限问题，数据也是一样的，在自己的app里不行，在preferences可以保存。

看样子，要分析一下xpc servcier 实现才行。

## 问题: 怎么找到对应的xpc service呢　             

xpc的数据最终是由nehelper发出去的。从nehelper分析起

nehelper里有一个单例

```
-[nehelper connection]()

stack[2024] = xpc_connection_create_mach_service("com.apple.nehelper", *(stack[2025] + *0x2fe2feac), 0x2); 

```



从这个可看到远端服务的名字叫　`com.apple.nehelper` 

``
the  name of the remote service with which to connect. the service name must  exist in a mach bootstrap that is accessible to the process and be  advertised in a launchd.plist.
在/library/launchdaemons发现一个文件`com.apple.nehelper.plist`

文件里果然有machservices一项，值为com.apple.nehelper

program一项的值为 /usr/libexec/nehelper

用ldid 看它的权限

```
<?xml version="1.0" encoding="utf-8"?>

<!doctype plist public "-//apple//dtd plist 1.0//en" "http://www.apple.com/dtds/propertylist-1.0.dtd">

<plist version="1.0">

<dict>

    <key>com.apple.systemconfiguration.scpreferences-write-access</key>

    <array>

        <string>vpn-com.apple.neplugin.ikev2.plist</string>

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



果然有写vpn配置的权限。用hopper打开分析分析看它接受信息的部分.

应该就是nehelperserver 这个类了

先用knhook 来hook一个这个类，打印它的信息看看

sub_d118 

sub_d118 



-[nehelperconfigurationmanager saveconfigurationtoprofile:] 这个方法失败了

```
void * -[nehelperconfigurationmanager saveconfigurationtoprofile:](void * self, void * _cmd, void * arg2) {
    r7 = (sp - 0x14) + 0xc;
    sp = sp - 0x3c;
    r10 = self;
    r6 = [arg2 retain];
    r5 = [[arg2 payloadinfo] retain];
    r7 = r7;
    r8 = [[r5 profileuuid] retain];
    [r5 release];
    r4 = [arg2 copyprofiledictionary];
    [r6 release];
    if (r4 != 0x0) {
            stack[2037] = r10;
            r7 = r7;
            r11 = [[nspropertylistserialization datawithpropertylist:r4 format:0xc8 options:0x0 error:sp + 0x18, stack[2035]] retain];
            r0 = 0x0;
            if (r11 != 0x0) {
                    stack[2035] = r4;
                    stack[2036] = r8;
                    r8 = [r0 retain];
                    r10 = [[mcprofileconnection sharedconnection] retain];
                    r4 = [[stack[2037] bundleid] retain];
                    stack[2038] = r8;
                    r1 = @selector(queuefiledataforacceptance:originalfilename:forbundleid:outerror:);
                    r0 = r10;
                    asm { strd       r4, r5, [sp, #0x34 + var_34] };
                    r6 = [objc_msgsend(r0, r1) retain];
                    r5 = [stack[2038] retain];
                    [r8 release];
                    [r4 release];
                    [r10 release];
                    if (r5 == 0x0) {
                            r8 = stack[2036];
                            r4 = stack[2035];
                            if (r6 != 0x0) {
                                    if (r8 != 0x0) {
                                            [nehelperconfigurationmanager addpendingingestionprofileuuid:r8];
                                            [nehelperconfigurationmanager addpendingingestionprofileuuid:r8];
                                    }
                                    [nehelperconfigurationmanager addpendingingestionprofileuuid:r6];
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
                    r5 = [[stack[2037] clientname] retain];
                    nelogobjc();
                    [r11 release];
                    [r5 release];
                    r5 = [[nserror errorwithdomain:@"neconfigurationerrordomain" code:0x8 userinfo:r6] retain];
                    r11 = 0x0;
            }
    }
    else {
            r4 = [[r10 clientname] retain];
            nelogobjc();
            [r4 release];
            r4 = 0x0;
            r5 = [[nserror errorwithdomain:@"neconfigurationerrordomain" code:0x8 userinfo:r4] retain];
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



根据之前的报错 not saved: error domain=neconfigurationerrordomain code=8 "invalid configuration operation request" userinfo=0x17a9d480 {nslocalizeddescription=invalid configuration operation request} 

定位是在这个方法里哪条路径上报出的.


