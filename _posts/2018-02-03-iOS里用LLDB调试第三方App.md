---
layout: post  
title: iOS里用LLDB调试第三方App
date: 2018-02-03  
categories: tech     
---  


usbmuxd虽然目前最新的版本是1.1.0，但是1.1.0版本和1.0.9版本仅支持Linux系统，也就是说我们的Mac还是得下载v1.0.8的版本，下载地址（[usbmuxd-v1.0.8](https://cgit.sukimashita.com/usbmuxd.git/snapshot/usbmuxd-1.0.8.tar.gz)）。下载完后，将下载的文件进行解压


首先我们得找到iOS设备中debugserver，并将其拷贝到Mac上进行处理，下方就是位于/Developer/usr/bin目录下的debugserver。此debugserver只支持调试我们自己的App, 如果需要调试其他人的App的话，需要对此debugserver进行处理，处理过程见下文。


<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
        <key>com.apple.springboard.debugapplications</key>
        <true/>
        <key>get-task-allow</key>
        <true/>
        <key>task_for_pid-allow</key>
        <true/>
        <key>run-unsigned-code</key>
        <true/>
</dict>
</plist>

在给debugserver符权限时，我们需要使用到ldid命令，如果你的Mac上没有安装ldid命令，那么请用brew进行install。执行下方的命令行就可以给我们的debugserver赋上task_for_pid权限。需要注意的是-S与ent.xml文件名中是没有空格的

ldid -Sent.xml debugserver

最后一步就是将处理好的debugserver拷贝到我们的越狱设备中，并且给debugserver赋上可执行的权限。因为/Developer/usr/bin目录下的debugserver是只读的，所以你不能将处理好的debugserver拷贝到上述文件，你要将处理好的debugserver拷贝到/usr/bin/目录下

chmod +x debugserver

