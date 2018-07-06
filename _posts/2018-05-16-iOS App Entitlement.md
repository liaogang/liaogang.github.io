---
layout: post  
title: iOS App Entitlement
date: 2018-05-16 
categories: tech     
---  


## 授权钥匙指南

(Apple 参考文档)[https://developer.apple.com/library/content/documentation/Miscellaneous/Reference/EntitlementKeyReference/Chapters/AboutEntitlements.html]

(iOS Code Signing 学习笔记)[http://foggry.com/blog/2014/10/16/ios-code-signing-xue-xi-bi-ji/]



授权颁发决定了iOS或macOS　app 有哪些权力来执行特定iOS功能或安全许可　

通常这个一个xml文件。　比如你在Xcode中的Capabilities中开启了Network Extensions的功能时，它会帮你在项目中自动生成一个xxx.entitlements文件

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>com.apple.developer.networking.networkextension</key>
  <array>
    <string>app-proxy-provider</string>
    <string>content-filter-provider</string>
    <string>packet-tunnel-provider</string>
  </array>
</dict>
</plist>








在 iOS 上你的应用能做什么依然是沙盒限制的，这些限制大多情况下都由授权文件（entitlements）来决定。授权机制决定了哪些系统资源在什么情况下允许被一个应用使用，简单的说它就是一个沙盒的配置列表。

运行如下命令1：


```
 codesign -d --entitlements - Example.app
``` 



在 Xcode 的 Capabilities 选项卡下选择一些选项之后，Xcode 就会生成这样一段 XML。 Xcode 会自动生成一个 .entitlements 文件，然后在需要的时候往里面添加条目。当构建整个应用时，这个文件也会提交给 codesign 作为应用所需要拥有哪些授权的参考。这些授权信息必须都在开发者中心的 App ID 中启用，并且包含在后文介绍的描述文件中。在构建应用时需要使用的授权文件可以在 Xcode build setting 中的 code signing entitlements中设置。





#import "dlfcn.h" 
typedefint (*MobileInstallationInstall)(NSString *path, NSDictionary *dict, void *na, NSString *path2_equal_path_maybe_no_use);

m文件
- (int)IPAInstall:(NSString *)path 
{ 
    void *lib = dlopen("/System/Library/PrivateFrameworks/MobileInstallation.framework/MobileInstallation", RTLD_LAZY); 
    if (lib) 
    { 
        MobileInstallationInstall pMobileInstallationInstall = (MobileInstallationInstall)dlsym(lib, "MobileInstallationInstall"); 
        if (pMobileInstallationInstall){ 
            int ret = pMobileInstallationInstall(path, [NSDictionarydictionaryWithObject:@"User"forKey:@"ApplicationType"], nil, path); 
            dlclose(lib); 
            return ret; 
        } 
    } 
    return -1; 
}



##Xcode 跳过代码签名
```
/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.1.sdk/SDKSettings.plist   
CODE_SIGNING_REQUIRED
```


## [codesign-frameworks.sh](https://gist.github.com/mralexgray/5563383)

```
#!/bin/sh

# WARNING: You may have to run Clean in Xcode after changing CODE_SIGN_IDENTITY! 

# Verify that $CODE_SIGN_IDENTITY is set
if [ -z "$CODE_SIGN_IDENTITY" ] ; then
    echo "CODE_SIGN_IDENTITY needs to be non-empty for codesigning frameworks!"

    if [ "$CONFIGURATION" = "Release" ] ; then
        exit 1
    else
        # Codesigning is optional for non-release builds.
        exit 0
    fi
fi

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")

FRAMEWORK_DIR="${TARGET_BUILD_DIR}/${FRAMEWORKS_FOLDER_PATH}"

# Loop through all frameworks
FRAMEWORKS=`find "${FRAMEWORK_DIR}" -type d -name "*.framework" | sed -e "s/\(.*\)/\1\/Versions\/A\//"`
RESULT=$?
if [[ $RESULT != 0 ]] ; then
    exit 1
fi

echo "Found:"
echo "${FRAMEWORKS}"

for FRAMEWORK in $FRAMEWORKS;
do
    echo "Signing '${FRAMEWORK}'"
    `codesign -f -v -s "${CODE_SIGN_IDENTITY}" "${FRAMEWORK}"`
    RESULT=$?
    if [[ $RESULT != 0 ]] ; then
        exit 1
    fi
done

# restore $IFS
IFS=$SAVEIFS

#Save it to a file in your project.
#Mine is called codesign-frameworks.sh.
#Add a “Run Script” build phase right after your “Copy Embedded Frameworks” build phase.
#You can call it “Codesign Embedded Frameworks”.
#Paste ./codesign-frameworks.sh (or whatever you called your script above) into the script editor text field.
#Build your app. All bundled frameworks will be codesigned.
#Updated 2012-11-14: Adding support for frameworks with special characters in their name (this does not include single quotes) to “codesign-frameworks.sh”.
#Updated 2013-01-30: Adding support for special characters in all paths (this should include single quotes) to “codesign-frameworks.sh”.
#Improvements welcome!
# from http://stackoverflow.com/questions/7697508/how-do-you-codesign-framework-bundles-for-the-mac-app-store
```