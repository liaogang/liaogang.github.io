---
layout: post  
title: 虚拟机保护Visual Machine Protect
date: 2020-11-02
categories: tech  
---

[MIPS64 Architecture](!https://www.mips.com/products/architectures/mips64/)



# 

The MIPS64 architecture has been used in a variety of applications including game consoles, office automation and set-top boxes. It  continues to be popular today in networking and telecommunications  infrastructure applications, and is at the heart of next-generation  servers, advanced driver assistance systems (ADAS) and autonomous  driving SoCs. As design complexity and software footprints continue to  increase, the 64-bit MIPS architecture will be used in an even broader  set of connected consumer devices, SOHO networking products, and  emerging intelligent applications.

The MIPS64® architecture provides a solid high-performance foundation for future MIPS processor-based development by incorporating powerful  features, standardizing privileged mode instructions, supporting past  ISAs, and providing a seamless upgrade path from the [MIPS32](https://www.mips.com/products/architectures/mips32/) architecture.

The MIPS32 and MIPS64 architectures incorporate important  functionality including SIMD (Single Instruction Multiple Data) and  virtualization. These technologies, in conjunction with technologies  such as [multi-threading (MT)](https://www.mips.com/products/architectures/ase/multi-threading/), [DSP extensions](https://www.mips.com/products/architectures/ase/dsp/) and EVA (Enhanced Virtual Addressing), enrich the architecture for use  with modern software workloads which require larger memory sizes,  increased computational horsepower and secure execution environments.

The MIPS64 architecture is based on a fixed-length, regularly encoded instruction set, and it uses a load/store data model. It is streamlined to support optimized execution of high-level languages. Arithmetic and  logic operations use a three-operand format, allowing compilers to  optimize complex expressions formulation. Availability of 32  general-purpose registers enables compilers to further optimize code  generation by keeping frequently accessed data in registers.

By providing backward compatibility, standardizing privileged mode,  and memory management and providing the information through the  configuration registers, the MIPS64 architecture enables real-time  operating systems and application code to be implemented once and reused with future members of both the MIPS32 and the MIPS64 processor  families.

### High-Perfomance Caches

Flexibility of high-performance caches and memory management schemes  are strengths of the MIPS architecture. The MIPS64 architecture extends  these advantages with well-defined cache control options. The size of  the instruction and data caches can range from 256 bytes to 4 MB. The  data cache can employ either a write-back or write-through policy. A  no-cache option can also be specified. The memory management mechanism  can employ either a TLB or a Block Address Translation (BAT) policy.  With a TLB, the MIPS64 architecture meets the memory management  requirements of Linux, Android™, Windows® CE and other historically  popular operating systems.

The addition of data streaming and predicated operations supports the increasing computation needs of the embedded market. Conditional data  move and data prefetch instructions are standardized, allowing for  improved system-level data throughput in communication and multimedia  applications.

### Fixed-Point DSP-Type Instructions

Fixed-point DSP-type instructions further enhance multimedia  processing. These instructions that include Multiply (MUL), Multiply and Add (MADD), Multiply and Subtract (MSUB), and “count leading 0s/1s,”  previously available only on some 64-bit MIPS processors, provide  greater performance in processing data streams such as audio, video, and multimedia without adding additional DSP hardware to the system.

### Powerful 64-bit Floating-Point Registers

Powerful 64-bit floating-point registers and execution units speed  the tasks of processing some DSP algorithms and calculating graphics  operations in real-time. Paired-single instructions pack two 32-bit  floating-point operands into a single 64-bit register, allowing Single  Instruction Multiple Data operations (SIMD). This provides twice as fast execution compared to traditional 32-bit floating-point units. Floating point operations can optionally be emulated in software.

### Addressing Modes

The MIPS64 architecture features both 32-bit and 64-bit addressing  modes, while working with 64-bit data. This allows reaping the benefits  of 64-bit data without the extra memory needed for 64-bit addressing. In order to allow easy migration from the 32-bit family, the architecture  features a 32-bit compatibility mode, in which all registers and  addresses are 32-bit wide and all instructions present in the MIPS32  architecture are executed.

### Documentation

#### MIPS64 Architecture for Programmers: Release 6

[ Introduction to the MIPS64 Architecture v6.01 (874.83 KB)](https://www.mips.com/?do-download=introduction-to-the-mips64-architecture-v6-01)

[ The MIPS64 Instruction Set v6.06 (2.7  MB)](https://www.mips.com/?do-download=the-mips64-instruction-set-v6-06)

[ The microMIPS64 Instruction Set v6.05 (2.3 MB)](https://www.mips.com/?do-download=the-micromips64-instruction-set-v6-05)

[ The MIPS64 and microMIPS64 Privileged Resource Architecture v6.03 (3.3 MB)](https://www.mips.com/?do-download=the-mips64-and-micromips64-privileged-resource-architecture-v6-03)

#### MIPS64 Architecture for Programmers: Releases 1-5

[ Introduction to the MIPS64 Architecture v5.04 (1.27 MB)](https://www.mips.com/?do-download=introduction-to-the-mips64-architecture-v5-04)

[ Introduction to the microMIPS64 Architecture v5.03 (1020.18 KB)](https://www.mips.com/?do-download=introduction-to-the-micromips64-architecture-v5-03)

[ The MIPS64 Instruction Set v5.04 (4.64 MB)](https://www.mips.com/?do-download=the-mips64-instruction-set-v5-04)

[ The microMIPS64 Instruction Set v5.04 (5.59 MB)](https://www.mips.com/?do-download=the-micromips64-instruction-set-v5-04)

[ The MIPS64 and microMIPS64 Privileged Resource Architecture v5.04 (2.58 MB)](https://www.mips.com/?do-download=the-mips64-and-micromips64-privileged-resource-architecture-v5-04)













 [MIPS Instruction Formats](!http://max.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/InstructionFormats.html)

# MIPS Instruction Formats

 

------

- All MIPS instructions are encoded in binary.

- All MIPS instructions are 32 bits long. 

  - ​	(Note: some assembly langs do not have uniform length for all instructions)            

- There are three instruction categories: R-format (most common), I-format, and J-format.

- All instructions have: 

  - - ​	op (or opcode): operation code (specifies the operation) (first 6 bits)        

------

### R-format Instructions

- Have op `0`.  (all of them!)

- ​    Also have: 

  - - ​	rs: 1st register operand (register source) (5 bits)        

    - ​	rt: 2nd register operand (5 bits)        

    - ​	rd: register destination (5 bits)        

    - ​	shamt: shift amount (0 when N/A) (5 bits)        

    - ​	funct: function code (identifies the specific R-format instruction) (6 bits)        

      




​                        Name            Format            Layout            Example                            6 bits            5 bits            5 bits            5 bits            5 bits            6 bits                            op            rs            rt            rd            shamt            funct                             addR0            2310            32add $1, $2, $3                            adduR0            2310            33addu $1, $2, $3                            subR0            2310            34sub $1, $2, $3                            subuR0            2310            35subu $1, $2, $3                            andR0            2310            36and $1, $2, $3                            orR0            2310            37or $1, $2, $3                            norR0            2310            39nor $1, $2, $3                            sltR0            2310            42slt $1, $2, $3                            sltuR0            2310            43sltu $1, $2, $3                            sllR0            02110            0sll $1, $2, 10                            srlR0            02110            2srl $1, $2, 10                            jrR0            31000            8jr $31            

*NOTE: op is 0, so funct disambiguates*

- #### Example

- ```
          add $s0, $s1, $s2       (registers 16, 17, 18)
  ```

op rs rt rd shamt funct  `0` `17` `18` `16` `0` `32`  `000000` `10001` `10010` `10000` `00000` `100000`

> ​    NOTE: Order of components in    machine code is different from assembly code.  Assembly code order    is similar to C, destination first.  Machine code has destination    last.

| C:             | `a = b + c`                                                  |
| -------------- | ------------------------------------------------------------ |
| assembly code: | `add $s0, $s1, $s2                  # add                    rd,                    rs, rt` |
| machine code:  | `000000 10001 10010 10000 0000 100000`             (`op rs rt                    rd                    shamt funct`) |

 

------

### I-format Instructions

- Have a constant value immediately present in the instruction.

- Also have: 

  - - ​		rs: register containing base address (5 bits)
      ​            
    - ​		rt: register destination/source (5 bits)
      ​            
    - ​		immediate: value or offset (16 bits)
      ​            

​                        Name            Format            Layout            Example                            6 bits            5 bits            5 bits            5 bits            5 bits            6 bits                            op            rs            rt            immediate                             beqI4            1225 (offset)            beq $1, $2, 100                            bneI5            1225 (offset)            bne $1, $2, 100                            addiI8            21100            addi $1, $2, 100                            addiuI9            21100            addiu $1, $2, 100                            andiI12            21100            andi $1, $2, 100                            oriI13            21100            ori $1, $2, 100                            sltiI10            21100            slti $1, $2, 100                            sltiuI11            21100            sltiu $1, $2, 100                            luiI15            01100            lui $1, 100                            lwI35            21100 (offset)            lw $1, 100($2)                            swI43            21100 (offset)            sw $1, 100($2)            

- #### Example

- ```
          lw $t0, 32($s3)       (registers 8 and 19)
  ```

op rs rt immediate  `35` `19` `8`     `32`  `100011` `10011` `01000`     `0000000000100000`

- #### Example: `beq`

- ```
          beq $t0, $zero, ENDIF
  ```

- The offset stored in a `beq` (or `bne`) instruction is the number of instructions from the PC (the instruction after the `beq` instruction) to the label (`ENDIF` in this example).  Or, in terms of addresses, it is the difference between the address associated with the label and the PC, divided by four.

- ```
      offset = (addrFromLabelTable - PC) / 4
  ```

- In the example above, if the `beq` instruction is at address `1004`, and thus the PC is `1008`, and if `ENDIF` is at address `1028`, then the value stored in the machine instruction would be

- ```
      offset = (1028 - 1008) / 4 = 5
  ```

op rs rt immediate  `4` `8` `0`     `5`  `000100` `01000` `00000`     `0000000000000101`

------

### J-format Instructions

- Have an address (part of one, actually) in the instruction.

​                        Name            Format            Layout            Example                            6 bits            5 bits            5 bits            5 bits            5 bits            6 bits                            op            address                             jJ2            2500j 10000                            jalJ3            2500jal 10000            

- #### Example

- ```
          j LOOP
  ```

- The address stored in a `j` instruction is 26 bits of the address associated with the specified label.  The 26 bits are achieved by dropping the high-order 4 bits of the address and the low-order 2 bits (which would always be 00, since addresses are always divisible by 4).

- ```
      address = low-order 26 bits of (addrFromLabelTable/4)
  ```

- In the example above, if `LOOP` is at address `1028`, then the value stored in the machine instruction would be `257`.

op address  `2`     `257`  `000010`     `00000000000000000100000001`



------

[Previous Slide](http://max.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/DesignPrinciples.html)

[Next Slide](http://max.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/mipsTable.html)

Alyce Brady, Kalamazoo College



[MIPS Instruction Reference](!http://www.mrc.uidaho.edu/mrc/people/jff/digital/MIPSir.html)

https://github.com/adeys/litemips

arm64 noop 

```
1f 20 03 d5 1f 20 03 d5 1f 20 03 d5 1f 20 03 d5
```

http://www.cs.iit.edu/~virgil/cs470/

https://github.com/RomanCastellarin/MIPS-VM

https://github.com/Gz3zFork/simple-virtual-machine

[Tutorial for Building and Reverse Engineering Simple Virtual Machine Protection](https://resources.infosecinstitute.com/topic/tutorial-building-reverse-engineering-simple-virtual-machine-protection/)

# 1. Introduction

The virtual machine protection refers to the kind of software  protection technology by which the original executable and readable code are translated into a string of pseudo-code byte stream, and a virtual  machine is embedded into the program to interpret and execute that  pseudo-code byte stream. The difference between virtual machine  protection technology and the other virtual machine technology, such as  Java Virtual Machine, is that virtual machine protection technology is  designed for software protection and uses a custom instruction set.

虚拟机保护是一种软件保护技术，通过该技术，原始的可执行文件和可读代码被转换为一串伪代码字节流，并将虚拟机嵌入到程序中以解释并执行该伪代码字节。 流。 虚拟机保护技术与其他虚拟机技术（例如Java虚拟机）之间的区别在于，虚拟机保护技术是为软件保护而设计的，并使用自定义指令集。

There are some famous commercial virtual machine protection products, such as VMProtect, Themida, etc., but all of them are too complex to  analyze. To illustrate the software protection technology, we turn to  build a simple virtual machine project. Although this project is far  from the commercial products, it is enough for building a CrackMe.

有一些著名的商业虚拟机保护产品，例如VMProtect，Themida等，但是它们都太复杂而无法分析。 为了说明软件保护技术，我们转向构建一个简单的虚拟机项目。 尽管该项目与商业产品相距甚远，但足以构建CrackMe。



By the way, GitHub is a fantastic site, and we have found a perfect  source code written by NWMonster. The rest of this paper is organized as follows: the CrackMe built by NWMonster’s source code is reverse  engineered in section 2, and source code is introduced in section 3, and we summarize this paper in section 4.

顺便说一下，GitHub是一个很棒的站点，我们找到了由NWMonster编写的完美源代码。 本文的其余部分安排如下：由NWMonster的源代码构建的CrackMe在第2部分中进行了逆向工程，在第3部分中介绍了源代码，在第4部分中对本文进行了总结。

# 2. Reverse Analysis

Before we reverse engineer this CrackMe, there are something that we  need to understand. The flowchart of a simple virtual machine protection is shown in the following figure:

# 

Before we reverse engineer this CrackMe, there are something that we  need to understand. The flowchart of a simple virtual machine protection is shown in the following figure:

![img](https://gitee.com/liaogang/upic/raw/master/ulZo4N.png)


In this figure, VM_code represents the pseudo-code byte stream, and  VM_register simulates the general registers of CPU. In the one run of  VM_loop, the virtual machine will run the specific VM_handler according  to the VM_code read in Loop head. To reverse engineer a simple virtual  machine protection, we need to figure out the meaning of every  VM_handler, and thus grasp the main idea of the origin program, which is protected by the virtual machine.

Pay attention that this flowchart does NOT apply to commercial  virtual machine protection products because this flowchart is too  simple.

From now on, let’s begin our reverse engineering. Usually, OllyDbg  (OD) is used to trace out the VM_loop, but this time we use IDA because  the graphic view of IDA is much clearer. To make it easy for our  discussion, we rebuild the source code to run in x86 Windows environment with debug version. All the materials will be uploaded to GitHub for  the readers who need them.

After putting this CrackMe into IDA, it is easy to find out the 207 bytes VM_code in the CrackMe:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor2.png)

In addition, VM_code in the above figure is assigned to [eax + 20h]:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor3.png)

From those instructions, we can assume that EAX points to VM_register structure and EAX+20h points to IP register, like this:



Structure VM_register{
 +0x00 ??



+0x04 ??

+0x08 ??

+0x0C ??

+0x10 ??

+0x14 ??

+0x18 ??

+0x1C ??

+0x20 IP register

}



The VM_loop can be found just after VM_register initialization:

By counting the squares in the figure, it seems that there are  totally 23 VM_handlers in this virtual machine. Now, we need to analyze  those VM_handlers in the order of VM_code sequence. The first byte of  VM_code is 0xDE, which corresponds to VM_handler_defaultcase:



![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor5.png)

The detail of VM_handler_defaultcase is:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor6.png)

Notice that VM_register is the first element of VM class, so the  another 0x4 offset is added to the origin 0x20 offset, which means  *(this + 0x24) point to IP register in the VM_register:

Now, we can see that VM_handler_defaultcase does nothing but increase the IP register. The second, third and fourth byte of VM_code also  corresponds to VM_handler_defaultcase. To make it more comprehensive, we can rewrite VM_code as:

From this figure, we can understand that VM_handler_22 XORs the following 0xF bytes VM_code with 0x66:

Currently, we cannot tell why those bytes are XORed with 0x66. The  21st VM_code is 0x70, which makes the virtual machine run to  VM_handler_10, and the detail of VM_handler_10 is:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor8.png)

This is a typical PUSH stack operations, which pushes the next 4 bytes VM_code into VM_stack. It is equals to:

Besides, *(this + 0x20) seems to point to the SP register, thus, we can find another element in VM_register structure:

Until now, we have figured out the 25 bytes of VM_code, three  handlers of VM_handler and part of VM_register. The whole analysis is  too long to post here so that we leave the rest work for the readers to  analyze by themselves. Anyone who is interested can check yourself by  reading the source and the whole algorithm, which is protected by that  simple virtual machine, is translated into CPP-file in the corresponding GitHub.

# 3. Build a simple virtual machine

# 

With that source code in hand, it is rather easy to build a simple  virtual machine. Let us first into that source code. The VM_register is  defined as:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor9.png)

Where ‘cf’ is condition flag, and ‘*db’ points to user-input data. The VM_loop is achieved by a while-switch structure:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor10.png)

Where ‘r.ip’ points to the VM_code. Moreover, VM_code is defined as an array of unsigned char:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor11.png)

The VM_handler is defined in the VM class:

![img](https://mk0resourcesinfm536w.kinstacdn.com/wp-content/uploads/052317_2156_Tutorialfor12.png)

As we can see, the first element of VM class is a REG structure,  which is what we called VM_register structure; all the 23 VM_handlers  can be found in the VM class. In the one run of VM_loop, the VM_code is  read, and one of those VM_handlers is chosen to be executed.



Based on those source codes, we can easily build a simple virtual  machine for ourselves. To make it easy, we use the existing VM_handler  and VM_register. One can define more and obscure VM_handlers to make the virtual machine more difficult to analyze.

基于这些源代码，我们可以轻松地为自己构建一个简单的虚拟机。 为简单起见，我们使用现有的VM_handler和VM_register。 可以定义更多且晦涩的VM_handlers，以使虚拟机更加难以分析。

All we need to do is to design the sequence of VM_code to accomplish  our purpose. For example, if we want to check out whether the 0x27 bytes user-input is a hexadecimal number or not, we can use the follow  VM_code listed below:

我们要做的就是设计VM_code的序列以实现我们的目的。 例如，如果要检查用户输入的0x27字节是否为十六进制数，可以使用下面列出的VM_code：

The above code is taken modified from the origin source code. In the  above list, each byte of 0x27 bytes user-input is compared with char  ‘F’, ‘0’, ‘9’, ‘A’ to determine whether it is a hexadecimal number. If  all the user-input are hexadecimal numbers, this virtual machine will  leave with R0=1; otherwise, R0=0.

上面的代码是从原始源代码中修改而来的。 在上面的列表中，将用户输入的每个0x27字节字节与char“ F”，“ 0”，“ 9”，“ A”进行比较，以确定它是否为十六进制数。 如果所有用户输入均为十六进制数，则该虚拟机将以R0 = 1离开； 否则，R0 = 0。

As soon as we finish writing VM_code, we need to replace the origin  code with this VM_code, put them into practice and make sure that there  is no bug.



一旦完成编写VM_code，我们需要用此VM_code替换原始代码，将它们投入实践并确保没有错误。

# 4. Summary

In this paper, we reverse engineer a simple open source virtual  machine protected CrackMe and build a simple virtual machine protection  for ourselves. To reverse engineer a simple virtual machine protection,  the key step is to find out all VM_handlers and understand the meaning  of each VM_handler. When building a simple virtual machine protection,  we need to design the sequence of VM_code to accomplish our purpose.

Besides, we have found some other virtual machine protected CrackMe  from bbs.pediy.com, and we leave them for readers who are interested in  reverse engineering them. All the materials mentioned above are uploaded to GitHub: