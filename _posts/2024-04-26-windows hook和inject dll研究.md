---

## layout: post\\

title: windows hook和inject dll研究\
date: 2024-04-26\
categories: tech

用这个把dll加载到目标进程里面去\
<https://github.com/liaogang/injectCmd>

#hook\
用MinHook，在目标位置插入自己的代码\
<https://github.com/liaogang/MyDll>

frida-gum

#怎么调试windows程序

ollyIce用法

# 修改pe文件来添加依赖

<https://www.zackyang.blog/article/dll-injection-with-import-table>

InjectDll <https://github.com/UserExistsError/InjectDll>\
Inject a Dll from memory

pe-modifier

<https://github.com/adeilsonsilva/pe-modifier>

<https://whereisr0da.github.io/blog/posts/2020-10-21-inject-code/#create-a-new-import-to-a-dll>

pe-bear <https://github.com/hasherezade/pe-bear>