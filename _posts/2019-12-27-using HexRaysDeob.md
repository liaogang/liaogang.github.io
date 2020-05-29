---
layout: post  
title: using HexRaysDeob
date: 2019-12-12
categories: tech  
---



支配树图解 http://pages.cs.wisc.edu/~fischer/cs701.f08/lectures/Lecture19.4up.pdf

[Hex-Rays Microcode API vs. Obfuscating Compiler](https://www.hexblog.com/?p=1248)

[Rolf Rolles博客](https://www.msreverseengineering.com/blog?author=5111cf9ee4b0a36262da10df) https://www.msreverseengineering.com/

项目地址: https://github.com/RolfRolles/HexRaysDeob 

- Pattern-based obfuscation
- Opaque predicates
- Alloca-related stack manipulation
- Control flow flattening



implemented via pattern substitutions

https://github.com/REhints/HexRaysCodeXplorer

[IDA PLUG-IN WRITINGINC/C++](http://www.binarypool.com/idapluginwriting/idapw.pdf)


```
$ export PATH=~/idasdk/bin:$PATH
export __MAC__=1
export MACSDK=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk
export __X64__=1
make __EA64__=1
```

cmake 制作插件的例子 https://github.com/google/idaidle





https://www.secshi.com/18281.html



microcode数据结构

microcode中四个比较重要的数据结构如下。
mbl_array_t
保存关于反编译代码和基本块数组的信息，比较重要的成员和函数如下。

int qty;
// 基本块数组的数量
const mblock_t *get_mblock(int n) const { return natural[n]; }
// 根据序号返回数组中对应的基本块
mblock_t *hexapi insert_block(int bblk);
// 插入一个基本块
bool hexapi remove_block(mblock_t *blk);
// 删除一个基本块
bool hexapi remove_empty_blocks(void);
// 删除所有空的基本块
bool hexapi combine_blocks(void);
// 合并线性的基本块
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)
int hexapi for_all_topinsns(minsn_visitor_t &mv);
// 遍历所有指令(不包括子指令)

mblock_t
一个包含指令列表的基本块，比较重要的成员和函数如下。

mblock_t *nextb;
// 双向链表中的下一个基本块
mblock_t *prevb;
// 双向链表中的上一个基本块
minsn_t *head;
// 指向基本块中的第一条指令
minsn_t *tail;
// 指向基本块中的最后一条指令
mbl_array_t *mba;
// 所属的mbl_array_t
int npred(void) const { return predset.size(); }
// 该块的前驱者数目
int nsucc(void) const { return succset.size(); }
// 该块的后继者数目
int pred(int n) const { return predset[n]; }
// 该块的第n个前驱者
int succ(int n) const { return succset[n]; }
// 该块的第n个后继者
minsn_t *hexapi insert_into_block(minsn_t *nm, minsn_t *om);
// 向双向链表中插入指令
minsn_t *hexapi remove_from_block(minsn_t *m);
// 删除双向链表中的指令
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)

minsn_t
表示一条指令，比较重要的成员和函数如下。指令可以嵌套，也就是说mop_t也可能会包含一个minsn_t。

mcode_t opcode;
// 操作码
int iprops;
// 一些表示指令性质的位的组合
minsn_t *next;
// 双向链表中的下一条指令
minsn_t *prev;
// 双向链表中的上一条指令
ea_t ea;
// 指令地址
mop_t l;
// 左操作数
mop_t r;
// 右操作数
mop_t d;
// 目标操作数
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)

mop_t
表示一个操作数，根据它的类型可以表示不同的信息(数字，寄存器，堆栈变量等等)，比较重要的成员和函数如下。

mopt_t t;
// 操作数类型
uint8 oprops;
// 操作数属性
uint16 valnum;
// 操作数的值，0表示未知，操作数的值相同操作数也相同
int size;
// 操作数大小
//下面的联合体中包含有关操作数的其它信息，根据操作数类型，存储不同类型的信息
  union
  {
    mreg_t r;
    // mop_r   寄存器数值
    mnumber_t *nnn;
    // mop_n   立即数的值
    minsn_t *d;
    // mop_d   另一条指令
    stkvar_ref_t *s;
    // mop_S   堆栈变量
    ea_t g;
    // mop_v   全局变量
    int b;
    // mop_b   块编号(在jmp\call指令中使用)
    mcallinfo_t *f;
    // mop_f   函数调用信息
    lvar_ref_t *l;
    // mop_l   本地变量
    mop_addr_t *a;
    // mop_a   操作数地址(mop_l\mop_v\mop_S\mop_r)
    char *helper;
    // mop_h   辅助函数名
    char *cstr;
    // mop_str 字符串常量
    mcases_t *c;
    // mop_c   switch的case和target
    fnumber_t *fpc;
    // mop_fn  浮点数常量
    mop_pair_t *pair;
    // mop_p   操作数对
    scif_t *scif;
    // mop_sc  分散的操作数信息
  };























# 使用IDA microcode去除ollvm混淆



## 前言

本文原文来自[Hex-Rays Microcode API vs. Obfuscating Compiler](https://www.secshi.com/goto/3t8c)。在IDA 7.1中IDA发布了反编译中使用的中间语言microcode，IDA 7.2和7.3中又新增了相关的C++和python API，这篇文章就是关于Rolf Rolles如何使用这一新功能来处理ollvm混淆的，代码地址：[HexRaysDeob](https://www.secshi.com/goto/osw5)。我翻译过程中为了方便理解加入了一些数据结构说明和相关代码对照，并不与原文完全相同。文章较长，分为上下两个部分。

## microcode和ctree

IDA反编译器中二进制代码有两种表示方式：
 microcode：处理器指令被翻译成microcode，反编译器对其进行优化和转换。
 使用[HexRaysDeob](https://www.secshi.com/goto/osw5)插件除了处理ollvm混淆也可以查看microcode。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111155707-db92f4ae-0458-1.png)
 ctree：由优化的microcode构建而成，用C语句和表达式表示像AST一样的树。
 使用[HexRaysCodeXplorer](https://www.secshi.com/goto/opaf)插件或者IDApython中的示例vds5.py可以查看ctree。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111154855-b5fdab68-0457-1.png)
 IDA反编译的整体流程如下所示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111162551-def4f238-045c-1.png)
 这篇文章重点说microcode。

## microcode数据结构

microcode中四个比较重要的数据结构如下。
 **mbl_array_t**
 保存关于反编译代码和基本块数组的信息，比较重要的成员和函数如下。

```
int qty;
// 基本块数组的数量
const mblock_t *get_mblock(int n) const { return natural[n]; }
// 根据序号返回数组中对应的基本块
mblock_t *hexapi insert_block(int bblk);
// 插入一个基本块
bool hexapi remove_block(mblock_t *blk);
// 删除一个基本块
bool hexapi remove_empty_blocks(void);
// 删除所有空的基本块
bool hexapi combine_blocks(void);
// 合并线性的基本块
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)
int hexapi for_all_topinsns(minsn_visitor_t &mv);
// 遍历所有指令(不包括子指令)
```

**mblock_t**
 一个包含指令列表的基本块，比较重要的成员和函数如下。

```
mblock_t *nextb;
// 双向链表中的下一个基本块
mblock_t *prevb;
// 双向链表中的上一个基本块
minsn_t *head;
// 指向基本块中的第一条指令
minsn_t *tail;
// 指向基本块中的最后一条指令
mbl_array_t *mba;
// 所属的mbl_array_t
int npred(void) const { return predset.size(); }
// 该块的前驱者数目
int nsucc(void) const { return succset.size(); }
// 该块的后继者数目
int pred(int n) const { return predset[n]; }
// 该块的第n个前驱者
int succ(int n) const { return succset[n]; }
// 该块的第n个后继者
minsn_t *hexapi insert_into_block(minsn_t *nm, minsn_t *om);
// 向双向链表中插入指令
minsn_t *hexapi remove_from_block(minsn_t *m);
// 删除双向链表中的指令
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)
```

**minsn_t**
 表示一条指令，比较重要的成员和函数如下。指令可以嵌套，也就是说mop_t也可能会包含一个minsn_t。

```
mcode_t opcode;
// 操作码
int iprops;
// 一些表示指令性质的位的组合
minsn_t *next;
// 双向链表中的下一条指令
minsn_t *prev;
// 双向链表中的上一条指令
ea_t ea;
// 指令地址
mop_t l;
// 左操作数
mop_t r;
// 右操作数
mop_t d;
// 目标操作数
int hexapi for_all_ops(mop_visitor_t &mv);
// 遍历所有操作数(包括子指令的)
int hexapi for_all_insns(minsn_visitor_t &mv);
// 遍历所有指令(包括子指令)
```

**mop_t**
 表示一个操作数，根据它的类型可以表示不同的信息(数字，寄存器，堆栈变量等等)，比较重要的成员和函数如下。

```
mopt_t t;
// 操作数类型
uint8 oprops;
// 操作数属性
uint16 valnum;
// 操作数的值，0表示未知，操作数的值相同操作数也相同
int size;
// 操作数大小
//下面的联合体中包含有关操作数的其它信息，根据操作数类型，存储不同类型的信息
  union
  {
    mreg_t r;
    // mop_r   寄存器数值
    mnumber_t *nnn;
    // mop_n   立即数的值
    minsn_t *d;
    // mop_d   另一条指令
    stkvar_ref_t *s;
    // mop_S   堆栈变量
    ea_t g;
    // mop_v   全局变量
    int b;
    // mop_b   块编号(在jmp\call指令中使用)
    mcallinfo_t *f;
    // mop_f   函数调用信息
    lvar_ref_t *l;
    // mop_l   本地变量
    mop_addr_t *a;
    // mop_a   操作数地址(mop_l\mop_v\mop_S\mop_r)
    char *helper;
    // mop_h   辅助函数名
    char *cstr;
    // mop_str 字符串常量
    mcases_t *c;
    // mop_c   switch的case和target
    fnumber_t *fpc;
    // mop_fn  浮点数常量
    mop_pair_t *pair;
    // mop_p   操作数对
    scif_t *scif;
    // mop_sc  分散的操作数信息
  };
```

它们之间的关系由下图所示。简单来说就是操作数(mop_t)组成指令(minsn_t)，指令(minsn_t)组成基本块(mblock_t)，基本块(mblock_t)组成mbl_array_t。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111180601-dd6784f4-046a-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111180608-e1501720-046a-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111180614-e4fcd728-046a-1.png)
 当HexRays在内部优化和转换microcode时，它将经历不同的成熟阶段(maturity  phases)，该阶段由类型为mba_maturity_t的枚举元素表示。例如，刚刚生成的microcode成熟度为MMAT_GENERATED，经过了局部优化之后的microcode成熟度为MMAT_LOCOPT，经过了函数调用的分析之后microcode成熟度为MMAT_CALLS。通过gen_microcode() API生成microcode时，用户可以指定需要优化microcode的成熟度级别。

## 使用IDA microcode去除ollvm混淆

### 样本中采用的混淆手段

样本来源：[https://www.virustotal.com/gui/file/0ac399bc541be9ecc4d294fa3545bbf7fac4b0a2d72bce20648abc7754b3df24/detection](https://www.secshi.com/goto/rg1t)

#### 基于模式的混淆

在该样本反编译的结果中可以看到相同的模式。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181322-e3feabca-046b-1.png)
  带下划线的部分在运行时始终为0，因为x是偶数或者奇数，并且x-1和x的奇偶性相反，偶数乘以奇数总是偶数，偶数的最低位为0，因此&1结果为0。这种模式还出现在带有AND复合条件的if语句中，AND复合条件结果总是为0，因此if语句永远不会执行。这是一种称为不透明谓词的混淆方式：条件分支运行时永远只会执行其中一条路径。

#### 控制流平坦化

被混淆的函数具有异常的控制流。每个被混淆的函数都包含一个循环中的switch语句，这是一种被称为控制流平坦化(control flow flattening)的混淆方式。简而言之，它的原理如下。
 1.为每个基本块分配一个数字。
 2.混淆器引入了块号变量，指示应执行哪个块。
 3.每个块都不会像往常那样通过分支指令将控制权转移给后继者，而是将块号变量更新为其所选的后继者。
 4.普通的控制流被循环内的根据块号变量执行的switch语句代替。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181512-25ff64b0-046c-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181519-29d0c7b4-046c-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181525-2d7a5c5e-046c-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181531-3117bc30-046c-1.png)
 该样本一个被控制流平坦化的函数的switch(block)部分的汇编代码如下所示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181553-3e7dddaa-046c-1.png)
  在第一行，var_1C即上面提到的块号变量被初始化为某个看起来很随机的数字。紧随其后的是一系列var_1C与其它随机数字的比较(var_1C复制到var_20中，var_20用于之后的比较)。这些比较的目标是原始函数的基本块。基本块在回到刚才显示的代码之前会更新var_1C指示下一步应执行哪个基本块，然后代码将执行比较并选择要执行的相应块。对于只有一个后继者的块，混淆器给var_1C分配一个常量，如下图所示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111181946-c95796a0-046c-1.png)
 对于具有两个可能的后继者(例如if语句)的块，混淆器引入x86 CMOV指令以将var_1C设置为两个可能的值之一，如下图所示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111182013-d96cb80e-046c-1.png)
 整个函数看起来如下所示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111182039-e8e56948-046c-1.png)
 在上图中，红色和橙色节点是switch(block)部分的实现。蓝色节点是该函数的原始基本块(可能会进一步混淆)。底部的紫色节点返回到开头的switch(block)部分。

#### 奇怪的栈操作

最后，我们还可以看到混淆器以不同寻常的方式操纵栈指针。它用__alloca_probe为函数参数和局部变量保留栈空间，而普通的编译器会在函数开头用push指令为所有局部变量保留栈空间。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111182222-25cbb45c-046d-1.png)
 IDA具有内置的启发式方法，可以确定__alloca_probe调用的参数并跟踪这些调用对栈指针的影响。但是混淆器使得IDA无法确定参数，因此IDA无法正确跟踪栈指针。

### 反混淆器代码结构

[HexRaysDeob](https://www.secshi.com/goto/osw5)反混淆器的代码结构如下所示。
 AllocaFixer:处理__alloca_probe
 CFFlattenInfo:处理控制流平坦化之前的准备工作
 main:插件入口
 MicrocodeExplorer:显示microcode
 PatternDeobfuscate/PatternDeobfuscateUtil:处理基于模式的混淆
 Unflattener:处理控制流平坦化
 DefUtil/HexRaysUtil/TargetUtil:其它功能
  IDA的插件入口一般会有的三个函数是init，term和run，作用分别是初始化，清理和调用插件。init函数中调用了install_optinsn_handler函数和install_optblock_handler函数进行指令级别的优化(PatternDeobfuscate)和块级别的优化(Unflattener)，HexRays会自动调用注册的回调对象。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111194904-42793456-0479-1.png)
 PatternDeobfuscate和AllocaFixer的代码相对比较好理解，接下来会重点讲解关于处理控制流平坦化的代码。
  前面说了IDA反编译器中二进制代码有microcode和ctree两种表示方式，那么使用microcode相关API而不是ctree相关API有什么好处呢？从前面的介绍中我们可以了解到ctree是由microcode产生的，microcode比ctree更“底层”。如果在microcode级别操作可以利用HexRays已有的恢复控制流的算法，另外一些模式在microcode级别能更好被匹配。

### 对抗控制流平坦化

简单来说，控制流平坦化消除了块到块直接的控制流传输。平坦化过程引入了一个块号变量，在函数执行的每一步它决定应该执行的块。函数的控制流结构被转换为块号变量上的一个switch，它最终引导执行到正确的块。每个块必须更新块号变量，以指示在当前块号之后应该执行的块。
  对抗控制流平坦化的过程在概念上很简单。简单地说，我们的任务是重建块到块直接的控制流传输，在此过程中消除switch(block)机制。在下面的小节中，我们将以图片的方式展示该过程。只需要三个步骤就可以消除控制流平坦化。一旦重新构建了原始的控制流传输，HexRays现有的控制流重组机制将完成剩下的工作。

#### 确定平坦块编号到mblock_t的映射

我们的首要任务是确定哪个平坦块编号对应于哪个mblock_t。下图所示是一个被控制流平坦化的函数的switch(block)部分的microcode表示。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111184916-e831292a-0470-1.png)
 HexRays当前正在使用块号变量ST14_4.4。如果等于0xCBAD6A23，则jz指令将控制流转移到@6块。类似的，0x25F52EB5对应于@9块，0x31B8F0BC对应于@10块。

#### 确定每个平坦块的后继者

接下来对于每个平坦块，我们需要确定控制流可能转移到的平坦块编号。如果原始控制流是无条件的，则它们可能具有一个后继者；如果其原始控制流是有条件的，则可能具有两个后继者。
  @9块中的microcode有一个后继者(第9.3行已被截断，因为它很长并且其细节不重要)。我们可以在9.4行上看到，该块在执行goto返回到switch(block)之前将块号变量更新为0xCBAD6A23，switch(block)会将控制流转移到@6块。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111185039-19b834de-0471-1.png)
  @6块中的microcode有两个后继者。在第8.1行执行goto返回到switch(block)之前，第8.0行用eax的值更新块号变量。如果第6.4行的jz为true，eax值为0x31B8F0BC；如果第6.4行的jz为false，eax值为0x25F52EB5。switch(block)会将控制流转移到@10块或@9块。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111185122-33796d34-0471-1.png)

#### 直接将控制流从源块转移到目标块

最后我们可以修改microcode中的控制流指令以直接指向其后继，而不是通过switch(block)。如果对所有平坦化的块执行此操作，则switch(block)将不再可用，我们可以将其删除，仅保留函数原始的未平坦化的控制流。
 前面我们确定@9块最终将控制流转移到@6块。@9块结尾用goto声明返回到位于@2块的switch(block)。我们只需将现有goto语句的目标修改为指向@6块而不是@2块，如下图所示(同时也删除了对块号变量的分配，因为不再需要)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191111185236-5f4d8ac6-0471-1.png)
 有两个后继者的块的情况稍微复杂一些，但是基本思想是相同的：将现有的控制流直接指向目标块而不是switch(block)。
 为了解决这个问题，我们将：
 1.将@8块的指令复制到@7块的末尾。
 2.更改@7块(刚从@8块复制过来)的goto指令，使其指向@9块。
 3.更改@8块的goto指令，使其指向@10块。
 我们还可以清除8.0行对块号变量的更新以及6.1行和7.0行中对eax的赋值。



## 工程实现

### 启发式识别被展平的函数

事实证明，二进制文件中的一些非库函数未被展平。我设计了一种启发式方法来确定给定函数是否被展平。被展平的函数将块号变量与jz和jg指令中的数字常量进行比较，这些数字常量似乎是伪随机生成的。有了这种特征就可以编写用于启发式确定某个函数是否被展平的算法。
 1.遍历函数中的所有microcode。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118144854-7cb110f2-09cf-1.png)
 2.对于每一个将变量和常数比较的jz/jg指令，记录相应的信息(变量，变量和常量比较的次数，对应的所有常量)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118144924-8eb44d6e-09cf-1.png)
 3.选择被比较次数最多的变量对应的所有常量。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145048-c07a0c3a-09cf-1.png)
 4.计算常量中为1的位数然后除以总位数，因为这些常量应该是伪随机生成的，所以这个值应该接近0.5。如果这个值在0.4和0.6之间则可以确定该函数已被展平。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145111-ce6d403c-09cf-1.png)

### 简化图结构

被展平的函数有时具有直接导致其它跳转的跳转，或者有时microcode翻译器插入以其它goto指令为目标的goto指令。例如在下图中，块4包含goto到块8的指令，而块8又包含goto到块15的指令。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145252-0af66592-09d0-1.png)
 如果@X块以goto @N指令结尾，并且@N块为一条goto @M指令，则将goto @N更新为goto @M。对于任意数量的goto以递归的方式应用此过程。
 在RemoveSingleGotos函数中第一次遍历所有的块，如果该块的第一条指令是goto指令则记录下目的地址到forwarderInfo中，否则forwarderInfo为-1。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145324-1de768d6-09d0-1.png)
  第二次遍历所有的块，如果该块的最后一条指令是call或者该块有不止一个后继者则跳过，考虑两种情况：最后一条指令是goto和最后一条指令不是goto。如果最后一条指令是goto指令，将iGotoTarget设置为goto的目标；如果最后一条指令不是goto指令，将iGotoTarget设置为其唯一后继者。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145401-33c94bc4-09d0-1.png)
  在while循环中将下一个块设置为forwarderInfo[iGotoTarget]，如果该块已经在while循环中遇到过说明这是一个死循环，将bShouldReplace设置为false并退出。如果forwarderInfo为-1说明遇到了一个第一条指令不是goto指令的块，也退出。只要遇到了一个第一条指令是goto指令的块就将bShouldReplace设置为true。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118145631-8d7c763c-09d0-1.png)
 如果最后一条指令是goto指令，将目的地址更改为while循环中的最后一个块；如果最后一条指令不是goto指令，增加一个目的地址为while循环中的最后一个块的goto指令。修改相应的前驱者和后继者信息。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150001-0a756a40-09d1-1.png)

### 提取块号信息

许多平坦化函数使用两个变量来实现与块号相关的功能。对于使用两个变量的情况，该函数的基本块更新的变量与switch(block)所比较的变量不同。这里将这两个变量分别称为块更新变量和块比较变量。在switch(block)开始时，将块更新变量的值复制到块比较变量中，此后所有后续比较均参考块比较变量。下图中switch(block)从@2块开始，@1块为ST18_4.4变量分配了一个数值。switch(block)中第一个比较在第2.3行，跟此变量相关。第2.1行将该变量复制到另一个名为ST14_4.4的变量中，然后将其用于后续比较(如第3.1行以及此后的所有switch(block)比较)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150123-3b615d80-09d1-1.png)
 然后，函数的平坦块更新变量ST18_4.4。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118154304-0e1f9066-09d7-1.png)
 (令人困惑的是，函数的平坦块更新了两个变量，但是仅使用了对块更新变量ST18_4.4的赋值。块比较变量ST14_4.4在使用其值之前，在第2.1行中被重新定义了)。
 因此，我们实际上有三个任务：
 1.确定哪个变量是块比较变量(我们已经通过熵检查得知)。
 2.确定是否存在块更新变量，如果存在，则确定它是哪个变量。
 3.从jz针对块比较变量/块更新变量的比较中提取数字常数，以确定平坦块编号到mblock_t的映射。
  首先，我们获取switch(block)之前的第一个块。从函数的开头开始一直向后移动，直到下一个块有多个前驱者。此时这个块就是switch(block)之前的第一个块(例如上面例子中的@1块)，下一个块就是switch(block)(例如上面例子中的@2块)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150217-5ba35e7c-09d1-1.png)
 找到switch(block)之前的第一个块中所有对变量赋常量值的指令，如果找到了块比较变量说明此时不存在块更新变量。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150251-6f8f0d5a-09d1-1.png)
 否则说明此时存在块更新变量，如果switch(block)之前的第一个块中对某变量赋常量值并且在switch(block)中将该变量拷贝给块比较变量，那么这个变量就是块更新变量。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150328-85b25cd6-09d1-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150333-88f36bc4-09d1-1.png)
 从jz针对块比较变量(位于switch(block)的块更新变量)的比较中提取数字常数，以确定平坦块编号到mblock_t的映射。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150404-9b29dfc6-09d1-1.png)

### 取消控制流平坦化

我们现在知道哪个变量是块更新变量/块比较变量。我们还知道哪个平坦块编号对应于哪个mblock_t。对于每个被展平的块，我们需要确定块更新变量的值。
 如前所述，平坦块有两种情况：
 平坦块始终将块更新变量设置为单个值(对应于无条件分支)。
 平坦块使用x86 CMOV指令将块更新变量设置为两个可能值之一(对应于条件分支)。
 对于如下所示的第一种情况找到一个数字就可以了。下图中块更新变量为ST14_4.4，我们的任务是在第9.4行找到数字分配。现在可以将最后一行的goto更改为对应的mblock_t。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150450-b663c608-09d1-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150454-b94849ca-09d1-1.png)
 对于如下所示的第二种情况需要确定ST14_4.4可能被更新为0xCBAD6A23(6.0)或0x25F52EB5(7.0)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150515-c5c84d6c-09d1-1.png)
 更新jz为true执行的块的goto指令(上面的例子中，将@8块的goto指令更新为goto @6)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150535-d14e749a-09d1-1.png)
 将jz为true执行的块拷贝到jz为false执行的块(上面的例子中，将@8块拷贝到@7块)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150553-dc4580fa-09d1-1.png)
 更新jz为false执行的块的goto指令(上面的例子中，将@7块的goto指令更新为goto @9)。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150609-e5d4f204-09d1-1.png)

## 其它问题

### 平坦块可能包含许多mblock_t

One complication is that a flattened block may be implemented by more than one Hex-Rays `mblock_t` as in the first case above, or more than three Hex-Rays `mblock_t` objects in the second case above. In particular, Hex-Rays splits basic blocks on function call boundaries — so there may be any number of Hex-Rays `mblock_t` objects for a single flattened block. Since we need to work backwards from the end of a flattened region, how do we know where the end of the region is? I solved this problem by computing the function’s [dominator     tree](https://en.wikipedia.org/wiki/Dominator_(graph_theory)) and finding the block dominated by the flattened block header that branches back to the control flow switch.



如上述第一种情况，mblock_t可以通过一个以上的mblock_t来实现平坦块；或者如上述第二种情况，mblock_t可以通过三个以上的mblock_t来实现平坦块。HexRays在函数调用边界上分割基本块，因此单个平坦块可以有任意数量的mblock_t。由于查找分配给块更新变量的数值需要从平坦区域的末端开始工作，所以需要知道该区域的末端在哪里。这里通过计算函数的支配树(dominator  tree)并找到将回到switch(block)并且由平坦块块头支配的块解决了这个问题。计算支配树的算法如下所示。如果一个函数含有X个基本块则每个基本块用X位的bitset来表示支配关系，第Y位为1表示基本块Y支配基本块X。初始化时每个基本块都支配每个基本块，即每个基本块的bitset每一位都为1，然后将第一个基本块的bitset设置为只有第一位为1，即对于第一个基本块只有它自己支配自己。然后遍历基本块，更新该基本块的bitset为它的bitset和它的前驱的bitset的与，然后设置该基本块自己支配自己。一直重复这样循环，直到bitset不再发生改变。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150745-1ed0e662-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150806-2b559b08-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150809-2d4ecab0-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150813-2f7d3010-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150816-312c2510-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150818-32c84408-09d2-1.png)
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150821-34a81672-09d2-1.png)

### 查找分配给块更新变量的数值

查找分配给块更新变量的数值有些情况下很简单，有些情况下很困难。有时HexRays的常量传播算法会创建将常量直接移动到块更新变量中的microcode或者通过几个寄存器或栈变量对块更新变量赋值。FindNumericDefBackwards函数从一个块的底部开始搜索对块更新变量的赋值。如果块更新变量是由另一个变量赋值的，它将执行递归搜索。一旦最终找到数字常量赋值则返回true。如果找到了支配该块的mbClusterHead块仍然没有找到则返回false。然而当平坦块通过指针写入内存时上述算法将不起作用。如下所示，在平坦块的开头常量被写入寄存器，然后被保存到栈变量中。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150907-4fccd2e4-09d2-1.png)
 稍后用指针写入内存。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150924-5a139b2a-09d2-1.png)
 最后从栈变量中读取。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118150940-6383ab96-09d2-1.png)
  这给我们带来的问题是HexRays需要证明中间的内存写入不会覆盖已保存的数据。通常，指针混叠是一个无法确定的问题，这意味着不可能编写算法来解决它的每个实例。当FindNumericDefBackwards函数返回false并且最后是从栈变量中读取时调用FindForwardStackVarDef函数转到平坦块的开头查找。以上面的情况为例，跳到第一个代码片段并且找到分配给var_B4和var_BC的常量。这样做不安全，但是恰好适用于此样本中的每个函数，并且很可能适用于该混淆编译器编译的每个样本。
 ![img](https://xzfile.aliyuncs.com/media/upload/picture/20191118151014-77953d16-09d2-1.png)

## 总结

控制流平坦化这一混淆技术早已经在代码保护工具和恶意代码样本中屡见不鲜，Rolf Rolles的方法为解决这一问题提供了新的思路。目前idapython已经提供了Rolf Rolles所开源代码的python版本[pyhexraysdeob](https://www.secshi.com/goto/lefl)。国外有研究人员基于Rolf Rolles的成果对APT10样本中类似的混淆进行了处理，也取得了比较好的效果：[Defeating APT10 Compiler-level Obfuscations](https://www.secshi.com/goto/73tq)。

