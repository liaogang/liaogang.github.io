

layout: post  
title: 编写LLDB Python脚本来跟踪所有指令并记录寄存器的变动
date: 2019-02-28
categories: tech  
---





编写LLDB Python脚本来跟踪所有指令并记录寄存器的变动

动机: 反混淆一段OLLVM加密过的程序功能



https://github.com/zeroepoch/ibatlvl/blob/master/lldb-trace.py

https://opensource.apple.com/source/lldb/lldb-159/www/python-reference.html

https://lldb.llvm.org/python_reference/index.html





比如当前程序停止在这个地址:

```sh
(lldb) n
Process 4717 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = instruction step over
    frame #0: 0x0000000183468e54 libsystem_kernel.dylib`mach_msg + 72
libsystem_kernel.dylib`mach_msg:
->  0x183468e54 <+72>: cbz    w0, 0x183468ed8           ; <+204>
    0x183468e58 <+76>: tbnz   w24, #0x6, 0x183468e90    ; <+132>
    0x183468e5c <+80>: mov    w27, #0x10000000
    0x183468e60 <+84>: movk   w27, #0x7
Target 0: (Aweme) stopped.

--------------------------------------------------------
# disasm next instruction
lldb.frame = lldb.thread.GetSelectedFrame()
insn = lldb.target.ReadInstructions(lldb.frame.addr, 1)[0]
#指令的助记符
>>> insn.mnemonic
'cbz'
#指令的操作数
>>> insn.operands
'w0, 0x183468ed8'
```

我们把python做成一个命令asdf

```sh
    lldb.debugger.HandleCommand('command script add -f ls.ls ls')
        lldb.debugger.HandleCommand('br ')
```