---
layout: post  
title: iOS里用LLDB调试第三方App
date: 2018-02-03  
categories: tech     
---  



LLDB是Low Level Debugger的简称，在iOS开发的调试中LLDB是经常使用的，LLDB是Xcode内置的动态调试工具。使用LLDB可以动态的调试你的应用程序，如果你不做其他的额外处理，因为debugserver缺少task_for_pid权限，所以你只能使用LLDB来调试你自己的App。那么本篇博客中就要使用LLDB来调试从AppStore下载安装的App，并且结合着Hopper来分析第三方App内部的结构。LLDB与Hopper的结合，会让你看到不一样的东西，本篇博客就会和你一起领略LLDB与Hopper的魅力。



###  

## 一、SSH的USB连接--usbmuxd

之前我们ssh连接iOS设备是通过局域网也就是WiFi来连接的，当网络环境不好的时候输入个命令行都卡，所以我们需要一种更快的访问iOS设备的方式，那就是使用USB连接了。本篇博客中无论是SSH连接iOS设备还是LLDB连接iOS设备，我们都使用USB的方式进行设备的访问，这样速度就快的不行不行的了。本篇博客的第一部分就是介绍如何使用USB进行设备的SSH连接，这部分也是本篇博客的基础，不过内容还算是简单。



### 1、获取usbmuxd

usbmuxd虽然目前最新的版本是1.1.0，但是1.1.0版本和1.0.9版本仅支持Linux系统，也就是说我们的Mac还是得下载v1.0.8的版本，下载地址（[usbmuxd-v1.0.8](https://cgit.sukimashita.com/usbmuxd.git/snapshot/usbmuxd-1.0.8.tar.gz)）。下载完后，将下载的文件进行解压，内容如下所示：



## 二、配置debugserver

在做iOS开发时，在Mac上输入LLDB的命令就可以控制iOS端的App，是因为在我们iOS客户端中有一个debugserver服务器。debugserver专门用来连接Mac端的LLDB客户端，接收LLDB所提供的命令，并且进行相应的执行。如果你的iOS设备进行过真机调试的话，设备中就会被安装上debugserver, 不过该debugserver只能用来调试你自己的相关应用。如果想要调试从AppStore中获取的App的话，那么我们需要对iOS设备上的debugserver进行处理。该部分就是要处理我们的debugserver。

### 1.获取debugserver

首先我们得找到iOS设备中debugserver，并将其拷贝到Mac上进行处理，下方就是位于/Developer/usr/bin目录下的debugserver。此debugserver只支持调试我们自己的App, 如果需要调试其他人的App的话，需要对此debugserver进行处理，处理过程见下文。

### 2.对debugserver进行瘦身

> **lipo -thin arm64 debugserver -output debugserver**

进入到到Mac中debugserver所在的目录下执行上述命令即可，-thin后方填写你的测试机相应的ARM架构即可，因为我的测试机是iPhone 6 Plus, 是arm64的架构，所以此处填的参数是arm64, 如果你的是iPhone5的设备，那么就是armv7s了。

### 3.给debugserver添加task_for_pid权限

给debugserver添加task_for_pid权限后，我们就可以使用LLDB调试其他App了。此部分我们需要一个存储配置信息的xml文件，该文件的内容如下。你可以将下下方的文本进行拷贝，然后存储成ent.xml即可。

```
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

```



在给debugserver符权限时，我们需要使用到ldid命令，如果你的Mac上没有安装ldid命令，那么请用brew进行install。执行下方的命令行就可以给我们的debugserver赋上task_for_pid权限。需要注意的是-S与ent.xml文件名中是没有空格的。

> **ldid -Sent.xml debugserver**

### 4、将debugserver拷贝到iOS设备中

最后一步就是将处理好的debugserver拷贝到我们的越狱设备中，并且给debugserver赋上可执行的权限。因为/Developer/usr/bin目录下的debugserver是只读的，所以你不能将处理好的debugserver拷贝到上述文件，你要将处理好的debugserver拷贝到/usr/bin/目录下（当然此处我们借助IFunBox进行文件的拷贝）。

将debugserver拷贝到/usr/bin目录下后，执行下方的赋权限的命令，将可执行的权限赋给debugserver，如下所示：

> **chmod +x debugserver**

赋完权限后，你就可以使用debugserver命令来开启debuserver了，如下所示：

## 三、debugserver的开启与LLDB的连接

### 1.开启debugserver

在越狱设备中，我们就可以通过下方命令行来开启debugserver了，我们此处以调试微信App为例。下方的命令就是启动debugserver来监听来自任何IP地址的接入，iOS设备的接入端口是12345，所要调试的App为“WeChat”。命令如下：

> **debugserver \*:12345 -a "WeChat"**

在我们iOS设备上执行上述命令的效果如下所示，执行完上述命令后，我们的iOS设备就会等待Mac终端LLDB的接入。



### 2.LLDB连接debugserver

LLDB连接debugserver可以使用WIFI进行连接，可是WIFI是不稳定的，而且特别的慢，所以此处我们要使用usbmuxd进行LLDB和debugserver的连接。

#### （1）进行端口的转发

和第一部分中的内容相同，我们使用usbmuxd进行端口的转发，将上述的“12345”端口对接到Mac本地的某个端口，此处我们使用“12345”端口。进入到usbmuxd-1.0.8目录下的python-client下执行下方的命令。

> **./tcprelay.py -t 12345:12345**

具体操作步骤如下所示：

#### 2）Mac端LLDB的接入

进行端口转发后，接下来我们就开始进入lldb模式，然后进行debugserver的连接了。首先在terminal上输入lldb命令，然后输入下方的地址进行连接。因为我们使用usbmuxd进行了端口的转发，因此可以使用本地的环回测试地址来进行debugserver的连接。

> **process connect connect://127.0.0.1:12345**

下方是连接后的结果，LLDB与debugserver建立完成后，我们就可以使用lldb来调试微信这个应用了。

![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802190256997-1037680211.png)



## 四、Hopper + LLDB

在上篇博客《[iOS逆向工程之给WeChat脱壳](http://www.cnblogs.com/ludashi/p/5725743.html)》 我们已经给微信进行可脱壳处理，所以使用Hopper进行处理是没有问题的。此部分我们就要将Hopper与LLDB结合在一起发挥其双剑合璧的作用。该部分也算是本篇博客中实战的一部分。

### 1.查看线程中的WeChat

LLDB连接上debugserver后，我们首先使用下方的命令来查看当前进程中的所有模块。从这些输出信息中我们能找到“WeChat”这个进程在虚拟内存相对于模块基地址的偏移量。

> **image list -o -f**

lldb连接debugserver后，执行上述命令输出的部分结果如下所示。下方截图中，第一个就是“WeChat”程序的相关信息。左边红框就是ASLR偏移量（随机偏移量），ASLR偏移量其实就是虚拟内存的其实地址，相对于模块基地址的偏移量。右边红框中的地址就是偏移后的地址。

在介绍地址这块的东西是先熟悉一下下方的两个概念：

- 模块在内存中的起始地址----模块基地址
- ASLR偏移 ---- 虚拟内存起始地址与模块基地址的偏移量

从下方的输出结果我们可以知道:ASLR偏移量 = 0x5b000, 模块偏移后基地址 = 0x5f000



　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802193645434-1962934332.png)

 

下方是使用Hopper打开的解密后的微信的安装包，其起始地址从下图中我们可以看出是0x4000, 这个地址就是模块偏移前的地址，也就是模块在虚拟内存中的起始地址。从Hopper中我们可以知道：模块偏移前的基地址=0x4000

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802193950965-1432678937.png)

从上面两组数据我们可以得出：

　　模块偏移后的基地址（0x5f000）= ASLR偏移量（0x5b000）+ 模块偏移前基地址（0x4000）

上面这个公式是尤为重要的，因为Hopper中显示的都是“ 模块偏移前基地址”，而LLDB要操作的都是“模块偏移后的基地址”。所以从Hopper到LLDB，我们要做一个地址偏移量的转换。这个在下方会多次用到。当然，有一点需要注意的是Hopper与LLDB所选择的AMR架构的位数得一致，要么是32位，要么都是64位，如果位数不匹配的话，那么计算出来的内存地址肯定是不对的。

### 2、使用LLDB给微信登录添加断点

#### (1)、加断点前的分析

“断点”这个东西在iOS开发中可谓是经常使用的东西，接下来我们要做的就是给在微信点击登录进行页面跳转时添加一个断点。就是点击左边截图的登录按钮往右边页面跳转时添加一个断点。我们暂且将断点添加在右边页面的初始化方法中。

![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802195421075-1894146567.png)　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802195425528-1534083353.png)

 

要给上述右边页面添加断点首先得知道上面“手机号登录”视图控制器的内存地址，然后才可以使用LLDB添加断点。那么寻找上述视图控制器的内存地址的任务就交给了我们的Hopper来做了。在Hopper中我们搜索“Login”，然后会筛选出好的带有Login关键字的ViewController，然后我们在筛选的结果中再次寻找可疑目标对象。然后我们找到了一个名为“WCAccountPhoneLoginControlLogic”（我们可以翻译一下英文，大概意思就是“微信手机账号登录控制逻辑”）的类，从这个类的名字中我们不难推断出该类极有可能就是我们要寻找的“手机账号登录”页面。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802195852872-1716380837.png)

经过上述分析后，我们决定要给该类的“initWithData”（这肯定是个初始化方法）使用LLDB添加断点。

 

#### (2)、定位断点地址

经过第一步找到添加断点的类中的方法后，接下来我们要计算出该方法的内存地址，然后使用LLDB给该地址添加断点。通过Hopper我们很容易定位到上述的“initWithData:”方法，的位置，如下所示。下方截图中这个带“星号”的地址就是“initWithData:”方法偏移前的基地址。根据上面的公式我们很容易就可以计算出该方法“偏移后的基地址”也就是真正的内存地址。算法如下所示：

initWithData内存地址 = 0x1304b60 + 0x5b000（ALSR偏移） = 0x135FB60

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802200709434-1897025055.png)

 

#### (3)、添加断点

使用下述命令，给上述地址添加断点。断点添加后，点击登录按钮就会跳转到“手机号登录”页面就会执行该断点，下方截图的红框中就是“断点”执行后的效果。从下方截图中我们可以看出该断点的编号是1，Breakpoint后方就是断点编号，该编号会在操作断点是会用到，下方会给出实例。

> br s -a 0x135FB60

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802201515184-1236281255.png)

 

#### (4)、断点的单步执行（ni, si）

你可以通过nexti (简写：ni)和stepi (简写：si)来进行单步的调试。ni遇到跳转不会进入到跳转中去，而si则会跳转到相应的分支中去。下方就是通过si和ni进行单步调试的效果截图。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802202024106-2048059713.png)

 

#### (5) 放开执行该断点（c）

命令c可以执行该断点, 上面这种情况如果执行c命令，因为只有一个断点，该断点执行后，就会跳转到“手机号登陆页面”。

 

#### (6)断点的禁用和开启

上面也有提到，上述创建的断点的编号是1，我们要对该断点进行禁用和开启操作，具体命令如下所示：

> **br dis 1 -- 禁用（disable）编号为1的断点**
>
> **br en 1 -- 启用（enable）编号为1的断点**
>
> **br dis  -- 禁用所有断点**
>
> **br en  -- 启用所有断点**

具体操作结果如下, 当断点禁用后，点击登录按钮就不会触发该断点了。当断点重启后，点击登录按钮还是会触发该断点的。具体效果如下所示：

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160802203008856-2124217087.png)

 

#### (7) 断点的删除

> **br del 1 -- 删除（delete）编号为1的断点**
>
> **br del  -- 删除所有断点**

![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803090735418-748897164.png)

 

### 3.输出寄存器的值(p, po)

在iOS开发中，我们在使用LLDB调试时，经常会用到po命令来输出某个变量或者常量的值。在使用LLDB调试WeChat时，我们也可以使用某些命令来输出寄存器中的值。我们使用$来访问某个寄存器中的值，并且使用p命令进行打印。下方就是通过p命令将r1寄存器中所存的内容进行打印，在打印之前将$r1进行类型转换，po命令则输出了Objective-C的对象，而p输出的是C语言类型的数据。如下所示：

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803092245918-95608722.png)

我们还可以将一个地址所存放的值进行打印，下方这个命令就是输出了$sp指针所指的地址处所存放的值：

> **p/x $sp**

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803092702793-231598231.png)

 

4.修改寄存器中的值

我们不仅可以查看某些寄存器中的值，而且可修改寄存器中的中，通过下述命令我们就可以修改指的寄存器中的值。

> **register write 寄存器 值**

接下来我们将要通过一个实例来实战一下register write这个命令，通过在Hopper中对登录模块的分析，我们不难发现“WCAccountManualAuthControlLogic”这个类中的“handleAuthResponse:”方法就是用来处理“登录认证响应”的方法。也就是说“handleAuthResponse:”负责处理登录业务逻辑的网络响应，并且在这个函数的前边有一个比较（cmp r0, r1）, 根据r0和r1的比较结果来进行跳转。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803095404153-2063361908.png)

接下来我们要做的事情就是，在比较寄存器r0和r1中的值时我们要改变r1寄存器中的值，然后观察App的运行效果。下方这个截图是随便输入手机号和密码时所提示的内容。也就是正常的流程会弹出下方的框。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803101545215-177653099.png)

接下来我们要做的就是给**0x1063a24 + 0x5b000 = 0x10BEA24 （cmp）**这个内存地址添加断点，然后去修改寄存器r1的值。下方截图就是给0x10BEA24这个内存址添加了断点，并且在输入手机号和密码后，点击登录会执行我们添加的断点，如下所示。在断点出我们清楚的看到了cmp r0, r1这行ARM指令。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803101947075-1705922218.png)

接下来我们先将r0和r1中的值进行打印，**$r0 = 8, $r1 = 351**。然后我们将$r1中的值改成8，然后输入c继续执行，发现之前正常流程的alter就不会弹出来了，而是重新进行了一次网络请求。

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160803102528965-865784571.png)

 

上述示例都是在32位系统上做的，如果你使用的是arm64架构的设备，如iPhone6Plus,那么你的地址会比上述地址要长一倍。下方两个截图是使用iPhone 6 Plus越狱设备做实验的截图，可以和上述步骤进行一下对比，虽然有所不同，但是上述内容在调试下方内容时也是适用的。

　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160804110337122-943640538.png)

　　![img](http://images2015.cnblogs.com/blog/545446/201608/545446-20160804110345325-59886520.png)

 

本篇博客的内容就到这儿吧，至此，你应该能将LLDB与Hopper结合起来使用了吧。今天我们以“微信”为例子，并没有别的意思，只是想在真正的实例中实现一下。使用微信做实验的原因就是微信做的足够安全，毕竟微信的团队还是很强大的。因为用我的越狱设备做完上述实验后，该越狱设备已经不能登录微信账号了，肯定是微信的后台监测到该“越狱设备”的异常行为了，从而做了一些安全措施。



https://yq.aliyun.com/articles/60786?spm=5176.100239.blogcont8468.32.Hs9JbO