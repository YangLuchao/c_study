[toc]

# ＃include头文件包含

和Java的import一样，导入其他文件的代码

#是预处理指令

include 是“包含”的意思

\#include " XX" 或者 #include ,意思是将"XX"或者中的文件引用到本程式中来,

"XX"或者中的文件通常是由系统提供的，其扩展名为 **.h**。

因此也称为头文件或首部文件

#includ<>与#includ ""的区别

*   < > 表示系统直接按系统指定的目录检索
*   "" 表示系统先在 "" 指定的路径(没写路径代表当前路径)查找头文件，如果找不到，再按系统指定的目录检索

# C标注库

[c标准库](https://www.runoob.com/cprogramming/c-standard-library-time-h.html)

<assert.h>：断言
<ctype.h>：用于测试和映射字符
<errno.h>：
<float.h>：包含了一组与浮点值相关的依赖于平台的常量
<limits.h>：包含了一组与浮点值相关的依赖于平台的常量，如一个无符号可以存储的最大值是 255
<locale.h>：
<math.h>：做计算用
<setjmp.h>：
<signal.h>：
<stdarg.h>
<stddef.h>
<stdio.h>：printf()函数
<stdlib.h>
<string.h>
<time.h>

# 常量、变量

#define PI 3.1415  定义常量

int r = 3 定义变量

const int r = 3 只读变量，相当于Java的final

# 关键字

![c的关键字](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/C%E5%85%B3%E9%94%AE%E5%AD%97.png)

# 数据类型

![数据类型](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/C%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B.png)

# sizeof数据类型大小

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main0302(void)
{
	int a = 3;
	short b = 4;
	long c = 5;			// 5L  5l
	long long d = 6;  // 5LL  5ll

	printf("sizeof(int) = %d\n", sizeof(int));
	printf("sizeof(short) = %d\n", sizeof(short));
	printf("sizeof(long) = %d\n", sizeof(long));
	printf("sizeof(long long) = %d\n", sizeof(long long));

	printf("--------------------------------------\n");

	unsigned int aun = 3;		// 3u
	unsigned short bun = 4;		// 3u
	unsigned long cun = 5;		// 3lu
	unsigned long long dun = 6;	// 3llu

	printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int)); // aun
	printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
	printf("sizeof(unsigned long) = %d\n", sizeof(unsigned long));
	printf("sizeof(unsigned long long) = %d\n", sizeof(unsigned long long));
}
```

# 无符号整形

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main0401(void)
{
	size_t var = 10;
	printf("var = %u\n", var);

	unsigned int a = 10u;  // 简写成 unsigned int a = 10;
	unsigned short b = 20u;// 简写成 unsigned short b = 20;
	unsigned long c = 30Lu; 
	unsigned long long d = 40LLu;

	printf("unsigned int 型数据值：%u\n", a);
	printf("unsigned short 型数据值：%hu\n", b);
	printf("unsigned long 型数据值：%lu\n", c);
	printf("unsigned long long 型数据值：%llu\n", d);

	system("pause");

	return EXIT_SUCCESS;
}
```

# #define _CRT_SECURE_NO_WARNINGS

>我们在编译老的用C语言的开源项目如lua源包的时候，可能因为一些老的.c文件使用了strcpy,scanf等不安全的函数，而报警告和错误，而导致无法编译通过
>
>解决方案如下：
>
>在指定的源文件的开头定义：#define _CRT_SECURE_NO_WARNINGS （只会在该文件里起作用）

# printf函数

*   printf是C语言库函数，功能是向标准输出设备输出一个字符串

*   printf(“hello world\n”);//\n的意思是回车换行

# system函数

```c
#include <stdlib.h>
int system(const char *command);
```

>   功能：在已经运行的程序中执行另外一个外部程序
>
>   参数：外部可执行程序名字
>
>   返回值：
>
>   成功：0
>
>   失败：任意数字

```c
实例代码：
#include <stdio.h> // 输出
#include <stdlib.h> // system

int main()
{
	//system("calc"); //windows平台
	system("ls"); //Linux平台, 需要头文件#include <stdlib.h>

	return 0;
}
```

# C语言编译过程

C代码编译成可执行程序经过4步

1.   **预处理**：宏定义展开、头文件展开、条件编译等，同时将代码中的注释删除，这里并不会检查语法
2.   **编译**：检查语法，将预处理后文件编译生成汇编文件
3.   **汇编**：将汇编文件生成目标文件(二进制文件)
4.   **链接**： C语言写的程序是需要依赖各种库的，所以编译之后还需要把库链接到最终的可执行程序中去

![c编译过程](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/C%E7%BC%96%E8%AF%91%E8%BF%87%E7%A8%8B.png)

# 有符号数和无符号数的区别

## 有符号数

有符号数是最高位为符号位，0代表正数，1代表负数

## 无符号数

无符号数最高位不是符号位，而就是数的一部分，无符号数不可能是负数

# sizeof关键字

*   sizeof不是函数，所以不需要包含任何头文件，它的功能是计算一个数据类型的大小，单位为字节
*    sizeof的返回值为size_t
*   size_t类型在32位操作系统下是unsigned int，是一个无符号的整数

# 计算机内存数值存储方式

## 原码

一个数的原码(原始的二进制码)有如下特点：

-   最高位做为符号位，0表示正,为1表示负

-   其它数值部分就是数值本身绝对值的二进制数

-   负数的原码是在其绝对值的基础上，最高位变为1

| ***\*十进制数\**** | ***\*原码\**** |
| ------------------ | -------------- |
| +15                | 0000 1111      |
| -15                | 1000 1111      |
| +0                 | 0000 0000      |
| -0                 | 1000 0000      |

## 反码

-   对于正数，反码与原码相同
-   对于负数，符号位不变，其它部分取反(1变0,0变1)

| ***\*十进制数\**** | ***\*反码\**** |
| ------------------ | -------------- |
| +15                | 0000 1111      |
| -15                | 1111 0000      |
| +0                 | 0000 0000      |
| -0                 | 1111 1111      |

## 补码

**==在计算机系统中，数值一律用补码来存储。==**

补码特点

-   对于正数，原码、反码、补码相同
-   对于负数，其补码为它的反码加1
-   补码符号位不动，其他位求反，最后整个数加1，得到原码

| **十进制数** | **补码**  |
| ------------ | --------- |
| +15          | 0000 1111 |
| -15          | 1111 0001 |
| +0           | 0000 0000 |
| -0           | 0000 0000 |

```c
#include <stdio.h>

int main()
{
	int  a = -15;

	printf("%x\n", a);
	//结果为 fffffff1
	//fffffff1对应的二进制：1111 1111 1111 1111 1111 1111 1111 0001
	//符号位不变，其它取反：1000 0000 0000 0000 0000 0000 0000 1110
	//上面加1：1000 0000 0000 0000 0000 0000 0000 1111  最高位1代表负数，就是-15

	return 0;
}
```

## 补码的意义

==**在计算机系统中**，**数值一律用补码来存储**==，主要原因是：

-   统一了零的编码

-   将符号位和其它位统一处理

-   将减法运算转变为加法运算

-   两个用补码表示的数相加时，如果最高位(符号位)有进位，则进位被舍弃

# 类型限定符

| **限定符** | **含义**                                                     |
| ---------- | ------------------------------------------------------------ |
| extern     | 声明一个变量，extern声明的变量没有建立存储空间。<br />extern int a;//变量在定义的时候创建存储空间 |
| const      | 定义一个常量，常量的值不能修改。const int a = 10;            |
| Volatile   | 防止编译器优化代码                                           |
| register   | 定义寄存器变量，提高效率。register是建议型的指令，而不是命令型的指令，如果CPU有空闲寄存器，那么register就生效，如果没有空闲寄存器，那么register无效。 |

# 字符常量与字符串常量的不同

每个字符串的结尾，编译器会自动的添加一个结束标志位'\0'，即 "a" 包含两个字符'a'和’\0’

