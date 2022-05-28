[toc]

# 概述

## 物理储存器和储存地址空间

物理存储器：实际存在的具体存储器芯片。

-   主板上装插的内存条

-   显示卡上的显示RAM芯片

-   各种适配卡上的RAM芯片和ROM芯片

存储地址空间：对存储器编码的范围。我们在软件上常说的内存是指这一层含义

-   ==编码：对每个物理存储单元（一个字节）分配一个号码==

-   ==寻址：可以根据分配的号码找到相应的存储单元，完成数据的读写==

## 内存地址

-   ==将内存抽象成一个很大的一维字符数组。==

-   ==编码就是对内存的每一个字节分配一个32位或64位的编号（与32位或者64位处理器相关）。==

-   ==这个内存编号我们称之为内存地址。==

-   内存中的每一个数据都会分配相应的地址：

    -   ==char:占一个字节分配一个地址==

    -   ==int: 占四个字节分配四个地址==

    -   float、struct、函数、数组等

## 指针和指针变量

-   ==内存区的每一个字节都有一个编号，这就是“地址”。==

-   ==如果在程序中定义了一个变量，在对程序进行编译或运行时，系统就会给这个变量分配内存单元，并确定它的内存地址(编号)==

-   ==指针的实质就是内存“地址”。指针就是地址，地址就是指针。==

-   ==指针是内存单元的编号，指针变量是存放地址的变量。==

-   ==通常我们叙述时会把指针变量简称为指针，实际他们含义并不一样。==

# 指针基础

-   ==指针也是一种数据类型，指针变量也是一种变量==

-   ==指针变量指向谁，就把谁的地址赋值给指针变量==

-   ==“*”操作符操作的是指针变量指向的内存空间==

```c
#include <stdio.h>

int main()
{
	int a = 0;
	char b = 100;
	printf("%p, %p\n", &a, &b); //打印a, b的地址

	//int *代表是一种数据类型，int*指针类型，p才是变量名
	//定义了一个指针类型的变量，可以指向一个int类型变量的地址
	int *p;
	p = &a;//将a的地址赋值给变量p，p也是一个变量，值是一个内存地址编号
	printf("%d\n", *p);//p指向了a的地址，*p就是a的值

	char *p1 = &b;
	printf("%c\n", *p1);//*p1指向了b的地址，*p1就是b的值

	return 0;
}
```

==注意：&可以取得一个变量在内存中的地址。但是，不能取寄存器变量，因为寄存器变量不在内存里，而在CPU里面，所以是没有地址的。==

## 通过指针简介修改变量的值

```c
	int a = 0;
	int b = 11;
	int *p = &a;

	// 将*p指针指向的地址的值赋值为100
	*p = 100;
	printf("a = %d, *p = %d\n", a, *p);
	// a = 100, *p = 100

	// 将b的地址赋值给变量p，p也是一个变量，值是一个内存地址编号
	p = &b;
	*p = 22;
	printf("b = %d, *p = %d\n", b, *p);
```

==p就是b的地址==

==*p就是b的值==

### 指针大小

-   使用sizeof()测量指针的大小，得到的总是：4或8

-   sizeof()测的是指针变量指向存储地址的大小

-   ==在32位平台，所有的指针（地址）都是32位(4字节)==

-   ==在64位平台，所有的指针（地址）都是64位(8字节)==

### 野指针和空指针

指针变量也是变量，是变量就可以任意赋值，不要越界即可（32位为4字节，64位为8字节），但是，==任意数值赋值给指针变量没有意义，因为这样的指针就成了野指针==，此指针指向的区域是未知(操作系统不允许操作此指针指向的内存区域)。所以，==野指针不会直接引发错误，操作野指针指向的内存区域才会出问题==。

```c
	int a = 100;
	int *p;
	p = a; //把a的值赋值给指针变量p，p为野指针， ok，不会有问题，但没有意义

	p = 0x12345678; //给指针变量p赋值，p为野指针， ok，不会有问题，但没有意义

	*p = 1000;  //操作野指针指向未知区域，内存出问题，err
```

但是，野指针和有效指针变量保存的都是数值，为了标志此指针变量没有指向任何变量(空闲可用)，C语言中，可以把NULL赋值给此指针，这样就标志此指针为空指针，没有任何指针。

NULL是一个值为0的宏常量：

```c
#define NULL    ((void *)0)
```

### 万能指针void *

void *指针可以指向任意变量的内存空间：

```c
	void *p = NULL;

	int a = 10;
	p = (void *)&a; //指向变量时，最好转换为void *

	// 使用指针变量指向的内存时，转换为int *
	*( (int *)p ) = 11;
	printf("a = %d\n", a);
```

### const修饰的指针变量

重点关注两个概念，==指针指向的内存区域、指针的指向==

==从左往右看，跳过类型，看修饰哪个字符==
==如果是*， 说明指针指向的内存值不能改变==
==如果是指针变量，说明指针的指向不能改变==

```c
	int a = 100;
	int b = 200;

	// 指向常量的指针
	// 修饰*，指针指向内存区域不能修改，指针指向可以变
	const int *p1 = &a; //等价于int const *p1 = &a;
	//*p1 = 111; //err
	p1 = &b; //ok

	// 指针常量
	// 修饰p1，指针指向不能变，指针指向的内存可以修改
	int * const p2 = &a;
	//p2 = &b; //err
	*p2 = 222; //ok
```

# 指针和数组

## 数组名字

是数组的首元素地址，但它是一个地址常量

```c
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	printf("a = %p\n", a);
	printf("&a[0] = %p\n", &a[0]);

	//a = 10; //err, 数组名只是常量，不能修改
```

## 指针操作数组元素

```c
#include <stdio.h>

int  main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
  // 计算a数组的长度
  // sizeof(a)，计算a数组的大小
  // sizeof(a[0]),计算a第0个元素的大小
	int n = sizeof(a) / sizeof(a[0]);
	
	for (i = 0; i < n; i++)
	{
    // a[i]是取a数组的第i个元素，和java/js的语法一样
		printf("%d, ", a[i]);
    // a+i是取a数组的第i个元素的内存地址，*(a+i)是取那个内存地址上的值
		printf("%d, ", *(a+i));
	}
	printf("\n");

  // 定义一个指针变量保存a的地址
  // p是a数组首元素的内存地址
  // *p是a数组该内存地址上的元素值
	int *p = a; 	
	for (i = 0; i < n; i++)
	{
    // p[i]是a数组第i个元素的值
    // 等价与a[i]
		p[i] = 2 * i;
	}

	for (i = 0; i < n; i++)
	{
    // p+i是取a数组第i个元素的内存地址，等价于a+i
    // *(p+i)是取那个内存地址上的值，等价与*(a+i)
		printf("%d, ", *(p + i));
	}
	printf("\n");

	return 0;
}
```

## 指针的加减运算

### 加法运算

-   ==指针计算不是简单的整数相加==

-   ==如果是一个int *，+1的结果是增加一个int的大小==

-   ==如果是一个char *，+1的结果是增加一个char大小==

```c
#include <stdio.h>

int main()
{
  // 定义一个a 
	int a;
  // &a是a的内存地址，就是a的引用
	int *p = &a;
  // p是a的地址
	printf("%d\n", p);
  // p=p+2,p移动了2个int
	p += 2;
  // int是4个字节，两个int就是8个字节
  // 假如p=100
  // p+=2后p=108
	printf("%d\n", p);

	char b = 0;
	char *p1 = &b;
	printf("%d\n", p1);
	p1 += 2;//移动了2个char
  // char是1字节
  // 假如p1=100
  // p1+=2后p1=102
	printf("%d\n", p1);

	return 0;
}
```

通过改变指针指向操作数组元素:

```c
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	int n = sizeof(a) / sizeof(a[0]);

	int *p = a;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", *p);
    // p是地址，而且*p是int类型，所以p++，在内存上每次移动一个int型大小的位置
		p++;
	}
	printf("\n");
	
	return 0;
}
```

### 减法运算

```c
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i = 0;
	int n = sizeof(a) / sizeof(a[0]);

	int *p = a+n-1;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", *p);
    // 内存地址上减一个int型的值
		p--;
	}
	printf("\n");

	return 0;
}
```

```c
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int *p2 = &a[2]; //第2个元素地址
	int *p1 = &a[1]; //第1个元素地址
	printf("p1 = %p, p2 = %p\n", p1, p2);

  // p2和p1只差个内存位置
  // 所以p2减p1等于1
	int n1 = p2 - p1; //n1 = 1
  // 强转为int后，一个int类型4个字节
	int n2 = (int)p2 - (int)p1; //n2 = 4
	printf("n1 = %d, n2 = %d\n", n1, n2);
	
	return 0;
}
```

## 指针数组

指针数组，它是数组，数组的每个元素都是指针类型。

```c
#include <stdio.h>

int main()
{
	//指针数组
	int *p[3];
	int a = 1;
	int b = 2;
	int c = 3;
	int i = 0;

	p[0] = &a;
	p[1] = &b;
	p[2] = &c;

	for (i = 0; i < sizeof(p) / sizeof(p[0]); i++ )
	{
		printf("%d, ", *(p[i]));
	}
	printf("\n");
	
	return 0;
}
```

# 多级指针

-   C语言允许有多级指针存在，在实际的程序中一级指针最常用，其次是二级指针。

-   二级指针就是指向一个一级指针变量地址的指针。

-   三级指针基本用不着，但考试会考。

```c
	int a = 10;
	int *p = &a; //一级指针
	*p = 100; //*p就是a

	int **q = &p;
	//*q就是p
	//**q就是a

	int ***t = &q;
	//*t就是q
	//**t就是p
	//***t就是a
```



# 指针和函数

## 函数形参改变实参的值

```c
#include <stdio.h>

/**
值传递，只改变形参的值，不会改变实参的值
*/
void swap1(int x, int y)
{
	int tmp;
	tmp = x;
	x = y;
	y = tmp;
	printf("x = %d, y = %d\n", x, y);
}
/**
引用传递，改变形参的值的同时，改变实参的值
*/
void swap2(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

/**
值传递与引用传递最直接的解释
java中只有值传递
值传递和引用传递最直接的区别就是对传递对象是否复制
java中基本类型就直接是值传递，形参不会影响实参
引用类型，其实是将对象的引用(地址/句柄)复制作为实参传给形参，形参操作的是对象的引用的副本
*/
int main()
{
	int a = 3;
	int b = 5;
	swap1(a, b); //值传递
	printf("a = %d, b = %d\n", a, b);

	a = 3;
	b = 5;
	swap2(&a, &b); //地址传递
	printf("a2 = %d, b2 = %d\n", a, b);

	return 0;
}
```

## 数组名做函数的实参

==数组名做函数参数，函数的形参会退化为指针：==

```c
#include <stdio.h>

void printArrary(int *a, int n)	
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d, ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int n = sizeof(a) / sizeof(a[0]);

	//数组名做函数参数
	printArrary(a, n); 
	return 0;
}
```

## 指针做为函数的返回值

```c
#include <stdio.h>

int a = 10;

int *getA()
{
	return &a;
}


int main()
{
	*( getA() ) = 111;
	printf("a = %d\n", a);

	return 0;
}
```

# 指针和字符串

## 字符的指针

```c
#include <stdio.h>

int main()
{
  // 没有以“/0”结尾都是char数组
	char str[] = "hello world";
  // p为char类型的指针
	char *p = str;
  // *p是char数组首元素，首元素重新赋值为'm'
	*p = 'm';
  // p++
	p++;
  // *p是char数组第二个元素，第二个元素重新赋值为’i‘
	*p = 'i';
	printf("%s\n", str);// millo world

  // p本来就是char类型指针，p重新赋值
	p = "mike jiang";
	printf("%s\n", p);// mike jiang
	
 
	char *q = "test";
	printf("%s\n", q);// q是“test”的地址

	return 0;
}
```

## 字符指针做函数参数

```c
#include <stdio.h>

void mystrcat(char *dest, const char *src)
{
	int len1 = 0;
	int len2 = 0;
	while (dest[len1])
	{
		len1++;
	}
	while (src[len2])
	{
		len2++;
	}

	int i;
	for (i = 0; i < len2; i++)
	{
		dest[len1 + i] = src[i];
	}
}

int main()
{
	char dst[100] = "hello mike";
	char src[] = "123456";
	
  // 数组名做函数实参，会退化为函数的形参，指针类型
	mystrcat(dst, src);
	printf("dst = %s\n", dst);

	return 0;
}
```

## const修饰的指针变量

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	//const修饰一个变量为只读
	const int a = 10;
	//a = 100; //err

	//指针变量， 指针指向的内存， 2个不同概念
	char buf[] = "aklgjdlsgjlkds";

	//从左往右看，跳过类型，看修饰哪个字符
	//如果是*， 说明指针指向的内存不能改变
	//如果是指针变量，说明指针的指向不能改变，指针的值不能修改
	const char *p = buf;
	// 等价于上面 char const *p1 = buf;
	//p[1] = '2'; //err
	p = "agdlsjaglkdsajgl"; //ok

	char * const p2 = buf;
	p2[1] = '3';
	//p2 = "salkjgldsjaglk"; //err

	//p3为只读，指向不能变，指向的内存也不能变
	const char * const p3 = buf;

	return 0;
}
```

## 指针数组做为main函数的形参

```c
int main(int argc, char *argv[]);
```

-   main函数是操作系统调用的，第一个参数标明argc数组的成员数量，argv数组的每个成员都是char *类型

-   argv是命令行参数的字符串数组

-   argc代表命令行参数的数量，程序名字本身算一个参数

```c
#include <stdio.h>

//argc: 传参数的个数（包含可执行程序）
//argv：指针数组，指向输入的参数
int main(int argc, char *argv[])
{

	//指针数组，它是数组，每个元素都是指针
	char *a[] = { "aaaaaaa", "bbbbbbbbbb", "ccccccc" };
	int i = 0;

	printf("argc = %d\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return 0;
}
```

## 项目开发常用字符串应用模型

### strstr中的while和do-while模型

利用strstr标准库函数找出一个字符串中substr出现的个数。

#### while模型

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  // 申请一片内存
  // p是首char的地址
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

  // p改为abcd开头首char的地址
	while ((p = strstr(p, "abcd")) != NULL)
	{
		//能进来，肯定有匹配的子串
		//重新设置起点位置
		p = p + strlen("abcd");
		n++;

		if (*p == 0) //如果到结束符
		{
			break;
		}

	}

	printf("n = %d\n", n);

	return 0;
}
```

#### do-while模型

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *p = "11abcd111122abcd333abcd3322abcd3333322qqq";
	int n = 0;

	do
	{
    // 从前到后找abcd
		p = strstr(p, "abcd");
    // p地址有值
		if (p != NULL)
		{
			n++; //累计个数

			//重新设置查找的起点
			p = p + strlen("abcd");

		}
		else //如果没有匹配的字符串，跳出循环
		{
			break;
		}
	} while (*p != 0); //如果没有到结尾

	printf("n = %d\n", n);
	return 0;
}
```

### 两头堵模型

求非空字符串元素的个数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int fun(char *p, int *n)
{
	if (p == NULL || n == NULL)
	{
		return -1;
	}

	int begin = 0;
	int end = strlen(p) - 1;

	//从左边开始
	//如果当前字符为空，而且没有结束
	while (p[begin] == ' ' && p[begin] != 0)
	{
		begin++; //位置从右移动一位
	}

	//从右往左移动
	while (p[end] == ' ' && end > 0)
	{
		end--; //往左移动
	}

	if (end == 0)
	{
		return -2;
	}

	//非空元素个数
	*n = end - begin + 1;

	return 0;
}

int main(void)
{
	char *p = "      abcddsgadsgefg      ";
	int ret = 0;
	int n = 0;

	ret = fun(p, &n);
	if (ret != 0)
	{
		return ret;
	}
	printf("非空字符串元素个数：%d\n", n);

	return 0;
```

### 字符串反转模型(逆置)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inverse(char *p)
{
	if (p == NULL)
	{
		return -1;
	}
	char *str = p;
	int begin = 0;
	int end = strlen(str) - 1;
	char tmp;

	while (begin < end)
	{
		//交换元素
		tmp = str[begin];
		str[begin] = str[end];
		str[end] = tmp;

		begin++;  //往右移动位置
		end--;	    //往左移动位置
	}

	return 0;
}

int main(void)
{
	//char *str = "abcdefg"; //文件常量区，内容不允许修改
	char str[] = "abcdef";

	int ret = inverse(str);
	if (ret != 0)
	{
		return ret;
	}

	printf("str ========== %s\n", str);
	return 0;
}
```

## 字符串处理函数

### strcpy()

>#include <string.h>
>char *strcpy(char *dest, const char *src);
>功能：把src所指向的字符串复制到dest所指向的空间中，'\0'也会拷贝过去
>参数：
>	dest：目的字符串首地址
>	src：源字符首地址
>返回值：
>	成功：返回dest字符串的首地址
>	失败：NULL

注意：如果参数dest所指的内存空间不够大，可能会造成缓冲溢出的错误情况。

```c
	char dest[20] = "123456789";
	char src[] = "hello world";
	strcpy(dest, src);
	printf("%s\n", dest);
```

### strncpy()

>#include <string.h>
>char *strncpy(char *dest, const char *src, size_t n);
>功能：把src指向字符串的前n个字符复制到dest所指向的空间中，是否拷贝结束符看指定的长度是否包含'\0'。
>参数：
>	dest：目的字符串首地址
>	src：源字符首地址
>	n：指定需要拷贝字符串个数
>
>返回值：
>
>​	成功：返回dest字符串的首地址
>
>​	失败：NULL

```c
	char dest[20] ;
	char src[] = "hello world";

	strncpy(dest, src, 5);
	printf("%s\n", dest);

	dest[5] = '\0';
	printf("%s\n", dest);
```

### strncat()

>#include <string.h>
>char *strncat(char *dest, const char *src, size_t n);
>功能：将src字符串前n个字符连接到dest的尾部，‘\0’也会追加过去
>参数：
>	dest：目的字符串首地址
>	src：源字符首地址
>	n：指定需要追加字符串个数
>返回值：
>	成功：返回dest字符串的首地址
>	失败：NULL

```c
	char str[20] = "123";
	char *src = "hello world";
	printf("%s\n", strncat(str, src, 5));
```

### strcmp()

>#include <string.h>
>int strcmp(const char *s1, const char *s2);
>功能：比较 s1 和 s2 的大小，比较的是字符ASCII码大小。
>参数：
>	s1：字符串1首地址
>	s2：字符串2首地址
>返回值：
>	相等：0
>	大于：>0 在不同操作系统strcmp结果会不同   返回ASCII差值
>	小于：<0

```c
	char *str1 = "hello world";
	char *str2 = "hello mike";

	if (strcmp(str1, str2) == 0)
	{
		printf("str1==str2\n");
	}
	else if (strcmp(str1, str2) > 0)
	{
		printf("str1>str2\n");
	}	
	else
	{
		printf("str1<str2\n");
	}
```

### sprintf()

>#include <stdio.h>
>int sprintf(char *str, const char *format, ...);
>功能：根据参数format字符串来转换并格式化数据，然后将结果输出到str指定的空间中，直到出现字符串结束符 '\0'  为止。
>参数：
>	str：字符串首地址
>	format：字符串格式，用法和printf()一样
>返回值：
>	成功：实际格式化的字符个数
>	失败： - 1

```c
	char dst[100] = { 0 };
	int a = 10;
	char src[] = "hello world";
	printf("a = %d, src = %s", a, src);
	printf("\n");

	int len = sprintf(dst, "a = %d, src = %s", a, src);
	printf("dst = \" %s\"\n", dst);
	printf("len = %d\n", len);
```

### sscanf()

>#include <stdio.h>
>int sscanf(const char *str, const char *format, ...);
>功能：从str指定的字符串读取数据，并根据参数format字符串来转换并格式化数据。
>参数：
>	str：指定的字符串首地址
>	format：字符串格式，用法和scanf()一样
>返回值：
>	成功：参数数目，成功转换的值的个数
>	失败： - 1

```c
	char src[] = "a=10, b=20";
	int a;
	int b;
	sscanf(src, "a=%d,  b=%d", &a, &b);
	printf("a:%d, b:%d\n", a, b);
```

### strchr()

>#include <string.h>
>char *strchr(const char *s, int c);
>功能：在字符串s中查找字母c出现的位置
>参数：
>	s：字符串首地址
>	c：匹配字母(字符)
>返回值：
>	成功：返回第一次出现的c地址
>	失败：NULL

```c
	char src[] = "ddda123abcd";
	char *p = strchr(src, 'a');
	printf("p = %s\n", p);
```

### strstr()

>#include <string.h>
>char *strstr(const char *haystack, const char *needle);
>功能：在字符串haystack中查找字符串needle出现的位置
>参数：
>	haystack：源字符串首地址
>	needle：匹配字符串首地址
>返回值：
>	成功：返回第一次出现的needle地址
>	失败：NULL

```c
	char src[] = "ddddabcd123abcd333abcd";
	char *p = strstr(src, "abcd");
	printf("p = %s\n", p);
```

### strtok()

>#include <string.h>
>char *strtok(char *str, const char *delim);
>功能：来将字符串分割成一个个片段。当strtok()在参数s的字符串中发现参数delim中包含的分割字符时, 则会将该字符改为\0 字符，当连续出现多个时只替换第一个为\0。
>参数：
>	str：指向欲分割的字符串
>	delim：为分割字符串中包含的所有字符
>返回值：
>	成功：分割后字符串首地址
>	失败：NULL

-   在第一次调用时：strtok()必需给予参数s字符串

-   往后的调用则将参数s设置成NULL，每次调用成功则返回指向被分割出片段的指针

```c
	char a[100] = "adc*fvcv.ebcy*hghbdfg$casdert";
	char *s = strtok(a, ".*$");//将"*"分割的子串取出
	while (s != NULL)
	{
		printf("%s\n", s);
		s = strtok(NULL, "*");
	}
```

### atoi()

>#include <stdlib.h>
>int atoi(const char *nptr);
>功能：atoi()会扫描nptr字符串，跳过前面的空格字符，直到遇到数字或正负号才开始做转换，而遇到非数字或字符串结束符('\0')才结束转换，并将结果返回返回值。
>参数：
>	nptr：待转换的字符串
>返回值：成功转换后整数

类似的函数有：

-   atof()：把一个小数形式的字符串转化为一个浮点数。

-   atol()：将一个字符串转化为long类型

```c
	char str1[] = "          -10";
	int num1 = atoi(str1);
	printf("num1 = %d\n", num1);

	char str2[] = "0.123";
	double num2 = atof(str2);
	printf("num2 = %lf\n", num2);

	char str3[] = "123L";
	long num3 = atol(str3);
	printf("num3 = %ld\n", num3);
```

# 指针小结

| ***\*定义\**** | ***\*说明\****                               |
| -------------- | -------------------------------------------- |
| int  i         | 定义整形变量                                 |
| int *p         | 定义一个指向int的指针变量                    |
| int a[10]      | 定义一个有10个元素的数组，每个元素类型为int  |
| int *p[10]     | 定义一个有10个元素的数组，每个元素类型为int* |
| int func()     | 定义一个函数，返回值为int型                  |
| int *func()    | 定义一个函数，返回值为int *型                |
| int **p        | 定义一个指向int的指针的指针，二级指针        |

# 指针强化

==指针是存放地址的变量。指针变量本身也是一种变量，指针有解引用的操作，* 找到内存空间。==

==不允许向NULL和非法地址拷贝内存==

```c
void test(){
	char *p = NULL;
	//给p指向的内存区域拷贝内容
	strcpy(p, "1111"); //err

	char *q = 0x1122;
	//给q指向的内存区域拷贝内容
	strcpy(q, "2222"); //err		
}
```

==只想一个不属于指针的内存区域，叫野指针==

## 什么情况下会导致野指针

>-   ***\*指针变量未初始化\****
>
>任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的，它会乱指一气。所以，指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存。
>
>-   ***\*指针释放后未置空\****
>
>有时指针在free或delete后未赋值 NULL，便会使人以为是合法的。别看free和delete的名字（尤其是delete），它们只是把指针所指的内存给释放掉，但并没有把指针本身干掉。此时指针指向的就是“垃圾”内存。释放后的指针应立即将指针置为NULL，防止产生“野指针”。
>
>-   ***\*指针操作超越变量作用域\****
>
>不要返回指向栈内存的指针或引用，因为栈内存在函数结束时会被释放。

## 野指针出现情况

```c
//指针操作超越变量作用域
int * doWork()
{
	int a = 10;
	int * p = &a;
	return p;
}

void test02()
{
	//2.1 指针变量未初始化
	int * p;
	printf("%d\n",*p);

	//2.2 指针释放后未置空
	char * str  = malloc(100);
	free(str);
	// 记住释放后 置空，防止野指针出现
	//str = NULL;

	//free(str);
	//2.3 空指针可以重复释放、野指针不可以重复释放

	//2.4 指针操作超越变量作用域
  // p指针指向a，doWork()后，a被释放，p变为野指针
	int * p = doWork();
	printf("%d\n", *p);
	printf("%d\n", *p);
}
```

## 指针的步长

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stddef.h> //offsetof的头文件

//1、指针的步长代表 指针+1之后跳跃的字节数
void test01()
{
	char * p = NULL;
	printf("%d\n", p);
	printf("%d\n", p+1);


	double * p2 = NULL;
	printf("%d\n", p2);
	printf("%d\n", p2 + 1);

}

//2、解引用的时候，解出的字节数量
void test02()
{
	char buf[1024] = { 0 };

	int a = 1000;

	memcpy(buf + 1, &a, sizeof(int));

	char * p = buf;
	printf("%d\n", *(int *)(p+1));

}

// 步长练习，自定义数据类型练习
struct Person
{
	char a;     // 0 ~ 3
	int b;      // 4 ~ 7
	char buf[64]; // 8 ~ 71
	int d;     // 72 ~ 75
};

void test03()
{
	struct Person p = { 'a', 10, "hello world", 20 };
	
	printf("d属性的偏移量： %d\n", offsetof(struct Person, d));

	printf("d属性的值为：%d\n", *(int *)((char *)&p + offsetof(struct Person, d)));
}

int main(){
	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}
```

==指针的步长代表 指针+1之后跳跃的字节数==

==解引用的时候，解出的字节数量==

offserof宏函数可以找到结构体某个数学的偏移量，#include <stddef.h> //offsetof的头文件

## 指针的意义-间接赋值

通过指针间接赋值成立的三大条件：

1.  2个变量（一个普通变量一个指针变量、或者一个实参一个形参）
2.  建立关系
3.  通过 * 操作指针指向的内存

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// 间接赋值三大条件
// 一个普通变量  和 指针变量   或  一个实参和一个形参
// 建立关系
// * 操作内存
void changeValue(int *a) // int * a = &a2;
{
	*a = 1000;
}

void test01()
{
	int  a = 10;
	int * p = NULL;


	p = &a;

	*p = 100;

	int a2 = 10;
	changeValue(&a2);

	printf("%d\n", a2);
	printf("%d\n", &a2);
}

int main(){
	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

## 指针做函数参数的输入输出特性

### 输入特性

在主调函数中分配内存，被调函数使用

分配在栈上和堆区

### 输出特性

在被调函数中分配内存，主调函数使用

## 字符串强化

字符串结束标志 \0

### sizeof和strlen

strlen统计到\0结束

sizeof统计全部长度，包括\0 

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void test01()
{
	////字符串结束标志位 \0
	//char str1[] = { 'h', 'e', 'l', 'l', 'o' ,'\0'};
	//printf("%s\n", str1);


	//char str2[100] = { 'h', 'e', 'l', 'l', 'o' };
	//printf("%s\n", str2);


	//char str3[] = "hello";
	//printf("%s\n", str3);
	//printf("sizeof str:%d\n", sizeof(str3)); //6
	//printf("strlen str:%d\n", strlen(str3)); //5


	//char str4[100] = "hello";
	//printf("sizeof str:%d\n", sizeof(str4));
	//printf("strlen str:%d\n", strlen(str4));


	//char str5[] = "hello\0world";
	//printf("%s\n", str5);
	//printf("sizeof str5:%d\n", sizeof(str5)); //12
	//printf("strlen str5:%d\n", strlen(str5)); //5


	char str6[] = "hello\012world";
	printf("%s\n", str6);
	printf("sizeof str6:%d\n", sizeof(str6)); //12
	printf("strlen str6:%d\n", strlen(str6)); //11

}
```

### 拷贝字符串的三种方式

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//字符串拷贝实现
//1、利用[] 实现
void copyString01(char * dest , char * src)
{
	int len =strlen(src);
	for (int i = 0; i < len;i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

//2、利用字符串指针
void copyString02(char * dest, char * src)
{
	while (*src != '\0')
	{
		*dest = *src;

		dest++;
		src++;
	}
	*dest = '\0';
}

//3
void copyString03(char * dest, char * src)
{
	while (*dest++ = *src++){}
}
```

### 字符串翻转

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//字符串翻转
void reverseString01(char * str)
{
	//利用[]
	int len = strlen(str);
	int start = 0;
	int end = len - 1;

	while (start < end)
	{
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;

		start++;
		end--;
	}

}

void reverseString02(char * str)
{
	int len = strlen(str);
	char * start = str;
	char * end = str + len - 1;

	while (start < end)
	{
		char temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

void test03()
{
	char str[] = "abcdefg";

	//reverseString01(str);
	reverseString02(str);
	printf("%s\n",str);
}

int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 一级指针易错点

## 指针叠加会不断改变指针指向

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void test01()
{
	char * p = malloc(sizeof(char)* 64);
	char * pp = p; //通过创建临时指针操作内存，防止出错
	for (int i = 0; i < 10;i++)
	{
		*pp = i + 97;
		printf("%c\n", *pp);
		pp++; //更改指针位置，释放出错
	}

	if (p!= NULL)
	{
		free(p);
	}


}
```

# 二级指针做形参输入特性

==二级指针做形参输入特性是指由主调函数分配内存。==

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printArray(int ** pArray , int len)
{
	for (int i = 0; i < len;i++)
	{
		printf("%d\n", *pArray[i]);
	}

}

void test01()
{
	//创建在堆区
	int ** pArray = malloc(sizeof(int *)* 5);

	//在栈上创建5个数据
	int a1 = 10;
	int a2 = 20;
	int a3 = 30;
	int a4 = 40;
	int a5 = 50;

	pArray[0] = &a1;
	pArray[1] = &a2;
	pArray[2] = &a3;
	pArray[3] = &a4;
	pArray[4] = &a5;

	//打印数组
	printArray(pArray, 5);

	//释放堆区数据
	if (pArray != NULL)
	{
		free(pArray);
		pArray = NULL;
	}

}

void freeSpace(int **pArray , int len)
{
	for (int i = 0; i < len;i++)
	{
		free(pArray[i]);
		pArray[i] = NULL;
	}

}

void test02()
{
	//创建在栈区
	int * pArray[5];

	for (int i = 0; i < 5;i++)
	{
		pArray[i] = malloc(4);
		*(pArray[i]) = 10 + i;
	}

	printArray(pArray, 5);

	//释放堆区
	freeSpace(pArray,5);

}
```



# 二级指针做形参输出特性

==二级指针做参数的输出特性是指由被调函数分配内存。==

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void allocateSpace(int ** p)
{
	int *  temp = malloc(sizeof(int)* 10);
	for (int i = 0; i < 10;i++)
	{
		temp[i] = 100 + i;
	}
	*p = temp;

}

void printArray(int ** pArray, int len)
{
	for (int i = 0; i < len;i++)
	{
		printf("%d\n", (*pArray)[i]);
	}
}

void freeSpace(int ** pArray)
{
	if (*pArray != NULL)
	{
		free(*pArray);
		*pArray = NULL;
	}
}

void test01()
{
	int * p = NULL;
	allocateSpace(&p);

	printArray(&p, 5);

	freeSpace(&p, 5);
	
	if (p == NULL)
	{
		printf("空指针\n");
	}
	else
	{
		printf("野指针\n");
	}
}
```

# 二级指针配合文件练习

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//获取有效行数
int getFileLines(FILE * pFile)
{
	if (pFile == NULL)
	{
		return -1;
	}

	char buf[1024] = { 0 };
	int lines = 0;
	while (fgets(buf,1024,pFile) != NULL)
	{
		//printf("%s", buf);
		lines++;
	}

	// 将文件光标置首
	fseek(pFile, 0, SEEK_SET);
	return lines;

}

//读取数据放入到pArray中
void readFileData(FILE * pFile, int len, char ** pArray)
{
	if (pFile == NULL)
	{
		return;
	}
	if (len <= 0 )
	{
		return;
	}
	if ( pArray ==NULL)
	{
		return;
	}
	char buf[1024] = { 0 };
	int index = 0;
	while (fgets(buf, 1024, pFile) != NULL)
	{
		/*
		aaaaaaaaaa
		bbbb
		cccccc
		*/
		int currentLen = strlen(buf) +1 ;
		char * currentStrP = malloc(sizeof(char)* currentLen);
		strcpy(currentStrP, buf);
		pArray[index++] = currentStrP;

		memset(buf, 0, 1024);
	}

}

void showFileData(char ** pArray, int len)
{
	for (int i = 0; i < len;i++)
	{
		printf("%d行的数据为 %s", i + 1, pArray[i]);
	}
	
}

void test01()
{
	//打开文件
	FILE * pFile =	fopen("./test.txt", "r");
	if (pFile == NULL)
	{
		printf("文件打开失败\n");
		return;
	}

	//统计有效行数
	int len =  getFileLines(pFile);
	//printf("文件的有效行数为：%d\n", len);
	char ** pArray =  malloc(sizeof(char *)* len);

	//读取文件中的数据并且放入到 pArray中
	readFileData(pFile, len, pArray);

	//读取数据
	showFileData(pArray , len);

	//释放堆区内容
	for (int i = 0; i < len; i++)
	{
		if (pArray[i] != NULL)
		{
			free(pArray[i]);
			pArray[i] = NULL;
		}
	}
	free(pArray);
	pArray = NULL;
	//关闭文件
	fclose(pFile);
}

```











