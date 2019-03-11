## Learning LLVM



```
Lexical analysis 词法分析 lexer 词法分析器 tokenizer scanner
lexing 词法分析 
tokenization 标记化
AST Abstract Syntax Tree 抽象语法树
Precedence 优先级
IR intermediate representation 中间产物
Instruction 指令
```

|             |                                                              |
| ----------- | ------------------------------------------------------------ |
| LLVMContext | 上下文类，基本是最核心的保存上下文符号的类                   |
| Module      | 模块类，一般一个文件是一个模块，里面有函数列表和全局变量表   |
| Function    | 函数类，函数类，生成出来就是一个C函数                        |
| Constant    | 常量类，各种常量的定义，都是从这里派生出来的                 |
| Value       | 各值类型的基类，几乎所以的函数、常量、变量、表达式，都可以转换成Value型 |
| Type        | 类型类，表示各种内部类型或用户类型，每一个Value都有个getType方法来获取其类型。 |
| BasicBlock  | 基本块，一般是表示一个标签，注意这个块不是嵌套形式的结构，而是每个块结尾可以用指令跳转 到其他块，类似C语言中的标签的功能 |

 [使用 LLVM 框架创建有效的编译器](https://www.ibm.com/developerworks/cn/opensource/os-createcompilerllvm2/index.html)

[LLVM零基础学习](https://blog.csdn.net/snsn1984/column/info/llvm)

 [Writing an LLVM Pass](https://llvm.org/docs/WritingAnLLVMPass.html#running-a-pass-with-opt)

[自己动手实现基于llvm的字符串加密](http://bbs.iosre.com/t/llvm/10610)

