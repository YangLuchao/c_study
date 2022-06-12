[toc]

# C语言编译过程

C代码编译成可执行程序经过4步：

1）==预处理：宏定义展开、头文件展开、条件编译等，同时将代码中的注释删除，这里并不会检查语法==

2）==编译：检查语法，将预处理后文件编译生成汇编文件==

3）==汇编：将汇编文件生成目标文件(二进制文件)==

4）==链接：C语言写的程序是需要依赖各种库的，所以编译之后还需要把库链接到最终的可执行程序中去==

![c编译过程](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/C%E7%BC%96%E8%AF%91%E8%BF%87%E7%A8%8B.png)

# gcc编译过程

>预处理：gcc -E hello.c -o hello.i
>
>编  译：gcc -S hello.i -o hello.s
>
>汇  编：gcc -c hello.s -o hello.o
>
>链  接：gcc   hello.o -o hello

| ***\*选项\**** | ***\*含义\****              |
| -------------- | --------------------------- |
| -E             | 只进行预处理                |
| -S(大写)       | 只进行预处理和编译          |
| -c(小写)       | 只进行预处理、编译和汇编    |
| -o file        | 指定生成的输出文件名为 file |

| ***\*文件后缀\**** | ***\*含义\****        |
| ------------------ | --------------------- |
| .c                 | C 语言文件            |
| .i                 | 预处理后的 C 语言文件 |
| .s                 | 编译后的汇编文件      |
| .o                 | 编译后的目标文件      |

## 一步编译

==gcc hello.c -o demo（还是经过：预处理、编译、汇编、链接的过程）==

# CPU内部结构与寄存器

## 64位和32位系统区别

-   ==寄存器是CPU内部最基本的存储单元==

-   CPU对外是通过==总线(地址、控制、数据)==来和外部设备交互的，==总线的宽度是8位，同时CPU的寄存器也是8位，那么这个CPU就叫8位CPU==

-   如果总线是32位，寄存器也是32位的，那么这个CPU就是32位CPU

-   有一种CPU内部的寄存器是32位的，但总线是16位，准32为CPU

-   所有的64位CPU兼容32位的指令，32位要兼容16位的指令，所以在64位的CPU上是可以识别32位的指令

-   ==在64位的CPU构架上运行了64位的软件操作系统，那么这个系统是64位==

-   在64位的CPU构架上，运行了32位的软件操作系统，那么这个系统就是32位

-   64位的软件不能运行在32位的CPU之上

## 寄存器名称

| ***\*8位\**** | ***\*16位\**** | ***\*32位\**** | ***\*64位\**** |
| ------------- | -------------- | -------------- | -------------- |
| A             | AX             | EAX            | RAX            |
| B             | BX             | EBX            | RBX            |
| C             | CX             | ECX            | RCX            |
| D             | DX             | EDX            | RDX            |

## 寄存器、缓存、内存三者关系

==按与CPU远近来分，离得最近的是寄存器，然后缓存(CPU缓存)，最后内存。==

==CPU计算时，先预先把要用的数据从硬盘读到内存，然后再把即将要用的数据读到寄存器。于是 CPU<--->寄存器<--->内存，这就是它们之间的信息交换。==

==从远近来看：CPU〈---〉寄存器〈---> 缓存 <---> 内存。==

# 汇编语言

## C语言嵌套汇编代码

```c
#include <stdio.h>

int main()
{
	//定义整型变量a, b, c
	int a;
	int b;
	int c;

	__asm
	{
		mov a, 3	//3的值放在a对应内存的位置
		mov b, 4	//4的值放在b对应内存的位置
		mov eax, a	//把a内存的值放在eax寄存器
		add eax, b	//eax和b相加，结果放在eax
		mov c, eax	//eax的值放在c中
	}
	
	printf("%d\n",  c);//把c的值输出

	return 0;//成功完成
}
```

## 反汇编

```c
#include <stdio.h>

int main()
{
	//定义整型变量a, b, c
	int a;
	int b;
	int c;

	a = 3;
	b = 4;
	c = a + b;
	
	printf("%d\n",  c);//把c的值输出

	return 0;//成功完成
}
```

# 预处理指令

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1 、头文件包含  "" <>区别
// ""包含自定义头文件
// <> 包含系统头文件

//2、 宏 常量  
//  不重视作用域
//  可以利用 undef卸载宏
//  宏常量 没有数据类型的

//宏 函数
//  将短小、频繁使用的函数写成宏函数
//  加括号保证运算完整性
//  优点：以空间换时间

void test01()
{
	#define  MAX 1024
	//#undef  MAX
}

//3、 条件编译
//#define  DEBUG
#ifdef DEBUG
void func()
{
	printf("Debug版本发布\n");
}
#else 
	//自定义条件编译
#if 0
void func()
{
	printf("Release1版本发布\n");
}
#else 
void func()
{
	printf("Release2版本发布\n");
}
#endif


#endif



//特殊宏
void doWork(char * p)
{
	if (p == NULL)
	{
		printf("文件： %s 第 %d 行 出错了\n", __FILE__, __LINE__);
		printf("日期：%s\n", __DATE__);
		printf("时间：%s\n", __TIME__);
		return;
	}
}
void test02()
{
	doWork(NULL);
	
}
```

# 静态库

打包成lib文件，给程序依赖

**mylib.h**

```c
#pragma  once 

//实现一个加法 ，返回两个数相加的结果
int myAdd(int a, int b);
```

**mylib.c**

```c
#include "mylib.h"

int myAdd(int a, int b){
	return a + b;
}
```

**main.c**

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

	printf("%d\n", myAdd(10, 20));


	system("pause");
	return EXIT_SUCCESS;
}
```

# 动态库

***定义导出函数***

```c
#ifndef TEST_H
#define TEST_H

__declspec(dllexport) int myminus(int a, int b);

#endif
```

***实现导出函数***

```c
#pragma once
int myminus(int a, int b){
	return a + b;
}
```

打包成dll、lib文件

将mydll.lib/mydll.dll/mydll.h拷入到工程

在工程中导入就可以用了

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma  comment( lib,"./mydll.lib")

int main(){

	printf("10 - 20 = %d\n", myminus(10, 20));


	system("pause");
	return EXIT_SUCCESS;
}
```

