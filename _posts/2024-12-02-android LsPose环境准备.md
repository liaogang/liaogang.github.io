2024-12-02


# 安装platform sdk tools，主要是用到了里面的adb来管理手机





# 安装magisk app

https://github.com/topjohnwu/Magisk/

这个app可以显示magisk模块，安装lsPose模块


# 获取root权限

Rooting any Pixel Phone (Android 12 and 13) (Magisk v25.2))
https://www.youtube.com/watch?v=TJBMmuMp9ZM&t=616s
 

如果是pixel 4 xl手机， 从这里下载出厂Image, 找到里面的boot.img

https://developers.google.com/android/images?hl=zh-cn#coral


用magisk给boot.img打补丁, 拷回电脑里

adb reboot bootloader 重启到bootloader模式

fastboot flash /magisk_pacthed_xxx.img  

fastboot reboot




# Zygisk 模块安装

https://github.com/MaterialCleaner/MaterialCleaner/wiki/Zygisk-%E6%A8%A1%E5%9D%97%E5%AE%89%E8%A3%85

下载完zygisk.zip模块之后，从magisk app里加载这个模块


# lspose 模块安装

下载完LSPosed-v1.9.2-7024-zygisk-release.zip模块之后，从magisk app里加载这个模块

https://github.com/LSPosed/LSPosed


# 重启之后再下拉通知里找到lspose, 生成桌面图标



