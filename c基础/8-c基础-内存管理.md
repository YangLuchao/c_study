[toc]

# 作用域

C语言变量的作用域分为：

-   l 代码块作用域(代码块是{}之间的一段代码)

-   l 函数作用域

-   l 文件作用域

## 局部变量

局部变量也叫auto自动变量(auto可写可不写)，一般情况下代码块{}内部定义的变量都是自动变量，它有如下特点：

-   在一个函数内定义，只在函数范围内有效

-   在复合语句中定义，只在复合语句中有效

-   随着函数调用的结束或复合语句的结束局部变量的声明声明周期也结束

-   ==如果没有赋初值，内容为随机==

```c
#include <stdio.h>

void test()
{
	//auto写不写是一样的
	//auto只能出现在{}内部
	auto int b = 10; 
}

int main(void)
{
	//b = 100; //err， 在main作用域中没有b

	if (1)
	{
		//在复合语句中定义，只在复合语句中有效
		int a = 10;
		printf("a = %d\n", a);
	}

	//a = 10; //err离开if()的复合语句，a已经不存在
	
	return 0;
}
```

## 静态(static)局部变量

-   ==static局部变量的作用域也是在定义的函数内有效==

-   static局部变量的生命周期和程序运行周期一样，同时==staitc局部变量的值只初始化一次，但可以赋值多次==

-   ==static局部变量若未赋以初值，则由系统自动赋值：数值型变量自动赋初值0，字符型变量赋空字符==

```c
#include <stdio.h>

void fun1()
{
	int i = 0;
	i++;
	printf("i = %d\n", i);
}

void fun2()
{
	//静态局部变量，没有赋值，系统赋值为0，而且只会初始化一次
	static int a;
	a++;
	printf("a = %d\n", a);
}

int main(void)
{
	fun1();
	fun1();
	fun2();
	fun2();
	
	return 0;
}
```

## 全局变量

-   在函数外定义，可被本文件及其它文件中的函数所共用，若其它文件中的函数调用此变量,须用extern声明

-   全局变量的生命周期和程序运行周期一样

-   不同文件的全局变量不可重名

## 静态(static)全局变量

-   在函数外定义,作用范围被限制在所定义的文件中

-   ==不同文件静态全局变量可以重名,但作用域不冲突==

-   ==static全局变量的生命周期和程序运行周期一样，同时staitc全局变量的值只初始化一次==

-   在运行前分配内存，程序运行结束，声明周期结束。在本文件内都可以使用这个静态变量

    ```c
    #include <stdlib.h>
    // a,b生命周期相同，作用域不同
    statis int a = 10;
    
    void test01() {
      static int b = 20;
    }
    ```

    

## extern全局变量声明 

==extern int a; ==extern 可以提高变量作用域

==声明一个变量，这个全局变量在别的文件中已经定义了，这里只是声明，而不是定义。==

```c
int main(){
  // 表示g_a变量在工程的其他文件中定义，在该文件中声明及引用
  // extern 可以提高变量作用域
	extern int g_a;
  printf("g_a = %d\n", g_a);
}
```



## 全局函数和静态函数

==在C语言中函数默认都是全局的，使用关键字static可以将函数声明为静态，函数定义为static就意味着这个函数只能在定义这个函数的文件中使用，在其他文件中不能调用，即使在其他文件中声明这个函数都没用。==

对于不同文件中的staitc函数名字可以相同:

![全局函数和静态函数](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/%E5%85%A8%E5%B1%80%E5%87%BD%E6%95%B0%E5%92%8C%E9%9D%99%E6%80%81%E5%87%BD%E6%95%B0.png)

==注意：==

-   允许在不同的函数中使用相同的变量名，它们代表不同的对象，分配不同的单元，互不干扰。

-   同一源文件中,允许全局变量和局部变量同名，在局部变量的作用域内，全局变量不起作用。

-   ==所有的函数默认都是全局的，意味着所有的函数都不能重名，但如果是staitc函数，那么作用域是文件级的，所以不同的文件static函数名是可以相同的。==

## 总结

| ***\*类型\**** | ***\*作用域\**** | ***\*生命周期\**** |      |
| -------------- | ---------------- | ------------------ | ---- |
| auto变量       | 一对{}内         | 当前函数           |      |
| static局部变量 | 一对{}内         | 整个程序运行期     |      |
| extern变量     | 整个程序         | 整个程序运行期     |      |
| static全局变量 | 当前文件         | 整个程序运行期     |      |
| extern函数     | 整个程序         | 整个程序运行期     |      |
| static函数     | 当前文件         | 整个程序运行期     |      |
| register变量   | 一对{}内         | 当前函数           |      |
| 全局变量       | 整个程序         | 整个程序运行期     |      |

# 内存布局

## 内存分区

C代码经过==预处理、编译、汇编、链接==4步后生成一个可执行程序。

在 Windows 下，程序是一个普通的可执行文件，以下列出一个二进制可执行文件的基本情况：

![二进制可执行文件基本情况](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/%E4%BA%8C%E8%BF%9B%E5%88%B6%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6%E5%9F%BA%E6%9C%AC%E6%83%85%E5%86%B5.png)

通过上图可以得知，在没有运行程序前，也就是说==程序没有加载到内存前==，可执行程序内部已经分好3段信息，分别为==代码区（text）、数据区（data）和未初始化数据区（bss）==3 个部分（有些人==直接把data和bss合起来叫做静态区或全局区==）。

### 代码区

存放 CPU 执行的机器指令。通常代码区是可共享的（即另外的执行程序可以调用它），使其可共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可。==代码区通常是只读的，使其只读的原因是防止程序意外地修改了它的指令==。另外，代码区还规划了局部变量的相关信息。

### 全局初始化数据区/静态数据区（data段）

该区包含了在程序中==明确被初始化的全局变量、已经初始化的静态变量（包括全局静态变量和局部静态变量）和常量数据（如字符串常量）==

### 未初始化数据区（又叫 bss 区）

存入的是全局未初始化变量和未初始化静态变量。未初始化数据区的数据在程序开始执行之前被内核初始化为 0 或者空（NULL）。

## 进程内存管理

==程序在加载到内存前，代码区和全局区(data和bss)的大小就是固定的，程序运行期间不能改变==。然后，==运行可执行程序，系统把程序加载到内存==，==除了根据可执行程序的信息分出代码区（text）、数据区（data）和未初始化数据区（bss）之外==，==还额外增加了栈区、堆区==。

![进程内存管理](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/%E8%BF%9B%E7%A8%8B%E5%86%85%E5%AD%98%E7%BB%93%E6%9E%84.png)

### 代码区

加载的是可执行文件代码段，所有的可执行代码都加载到代码区，这块内存是不可以在运行期间修改的

### 未初始化数据区（BSS）

加载的是可执行文件BSS段，位置可以分开亦可以紧靠数据段，存储于数据段的数据（全局未初始化，静态未初始化数据）的生存周期为整个程序运行过程。

### 全局初始化数据区/静态数据区（data segment）

加载的是可执行文件数据段，存储于数据段（全局初始化，静态初始化数据，文字常量(只读)）的数据的生存周期为整个程序运行过程。

### 栈区（stack）

==栈是一种先进后出的内存结构，由编译器自动分配释放，存放函数的参数值、返回值、局部变量等。在程序运行过程中实时加载和释放，因此，局部变量的生存周期为申请到释放该段栈空间。==

### 堆区（heap）

堆是一个大容器，它的容量要远远大于栈，但没有栈那样先进后出的顺序。==用于动态内存分配。堆在内存中位于BSS区和栈区之间。一般由程序员分配和释放，若程序员不释放，程序结束时由操作系统回收。==

# ==存储类型总结==

| ***\*类型\**** | ***\*作用域\**** | ***\*生命周期\**** | ***\*存储位置\****              |
| -------------- | ---------------- | ------------------ | ------------------------------- |
| auto变量       | 一对{}内         | 当前函数           | 栈区                            |
| static局部变量 | 一对{}内         | 整个程序运行期     | 初始化在data段，未初始化在BSS段 |
| extern变量     | 整个程序         | 整个程序运行期     | 初始化在data段，未初始化在BSS段 |
| static全局变量 | 当前文件         | 整个程序运行期     | 初始化在data段，未初始化在BSS段 |
| extern函数     | 整个程序         | 整个程序运行期     | 代码区                          |
| static函数     | 当前文件         | 整个程序运行期     | 代码区                          |
| register变量   | 一对{}内         | 当前函数           | 运行时存储在CPU寄存器           |
| 字符串常量     | 当前文件         | 整个程序运行期     | data段                          |

```c
#include <stdio.h>
#include <stdlib.h>

int e;
static int f;
int g = 10;
static int h = 10;
int main()
{
	int a;
	int b = 10;
	static int c;
	static int d = 10;
	char *i = "test";
	char *k = NULL;

	printf("&a\t %p\t //局部未初始化变量\n", &a);
	printf("&b\t %p\t //局部初始化变量\n", &b);

	printf("&c\t %p\t //静态局部未初始化变量\n", &c);
	printf("&d\t %p\t //静态局部初始化变量\n", &d);

	printf("&e\t %p\t //全局未初始化变量\n", &e);
	printf("&f\t %p\t //全局静态未初始化变量\n", &f);

	printf("&g\t %p\t //全局初始化变量\n", &g);
	printf("&h\t %p\t //全局静态初始化变量\n", &h);

	printf("i\t %p\t //只读数据(文字常量区)\n", i);

	k = (char *)malloc(10);
	printf("k\t %p\t //动态分配的内存\n", k);

	return 0;
}
```

## 内存操作函数

### memset()

>#include <string.h>
>void *memset(void *s, int c, size_t n);
>功能：将s的内存区域的前n个字节以参数c填入
>参数：
>	s：需要操作内存s的首地址
>	c：填充的字符，c虽然参数为int，但必须是unsigned char , 范围为0~255
>	n：指定需要设置的大小
>返回值：s的首地址

```c
	int a[10];

	memset(a, 0, sizeof(a));
	memset(a, 97, sizeof(a));
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		printf("%c\n", a[i]);
	}
```

### memcpy()

>#include <string.h>
>void *memcpy(void *dest, const void *src, size_t n);
>功能：拷贝src所指的内存内容的前n个字节到dest所值的内存地址上。
>参数：
>	dest：目的内存首地址
>	src：源内存首地址，注意：dest和src所指的内存空间不可重叠，可能会导致程序报错
>	n：需要拷贝的字节数
>返回值：dest的首地址

```c
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[10];
	
	memcpy(b, a, sizeof(a));
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		printf("%d, ", b[i]);
	}
	printf("\n");

	//memcpy(&a[3], a, 5 * sizeof(int)); //err, 内存重叠
```

## memmove()

memmove()功能用法和memcpy()一样，区别在于：dest和src所指的内存空间重叠时，memmove()仍然能处理，不过执行效率比memcpy()低些。

### memcmp()

>\#include <string.h>
>
>***\*int\**** ***\*memcmp\*******\*(\*******\*const\**** ***\*void\**** ***\**\*******\*s1\*******\*,\**** ***\*const\**** ***\*void\**** ***\**\*******\*s2\*******\*,\**** ***\**size_t\**\*** ***\*n\*******\*);\****
>
>功能：比较s1和s2所指向内存区域的前n个字节
>
>参数：
>
>​	s1：内存首地址1
>
>​	s2：内存首地址2
>
>​	n：需比较的前n个字节
>
>返回值：
>
>​	相等：=0
>
>​	大于：>0
>
>​	小于：<0

```c
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int flag = memcmp(a, b, sizeof(a));
	printf("flag = %d\n", flag);
```

## ==堆区内存分配和释放==

### ==malloc()==

>\#include <stdlib.h>
>
>void malloc (size_t size);
>
>功能：在内存的动态存储区(堆区)中分配一块长度为size字节的连续区域，用来存放类型说明符指定的类型。分配的内存空间内容不确定，一般使用memset初始化。
>
>参数：
>
>​	size：需要分配内存大小(单位：字节)
>
>返回值：
>
>成功：分配空间的起始地址
>
>失败：NULL

```c
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

int main()
{
	int count, *array, n;
	printf("请输入要申请数组的个数:\n");
	scanf("%d", &n);

	array = (int *)malloc(n * sizeof (int));
	if (array == NULL)
	{
		printf("申请空间失败!\n");
		return -1;
	}
	//将申请到空间清0
	memset(array, 0, sizeof(int)*n);

	for (count = 0; count < n; count++) /*给数组赋值*/
		array[count] = count;

	for (count = 0; count < n; count++) /*打印数组元素*/
		printf("%2d", array[count]);

	free(array);

	return 0;
}
```

### calloc()

>#include <stdlib.h>
>void *calloc(size_t nmemb, size_t size);
>功能：
>在内存动态存储区中分配nmemb块长度为size字节的连续区域。==calloc自动将分配的内存置0。==
>参数：
>	nmemb：所需内存单元数量
>	size：每个内存单元的大小（单位：字节）
>返回值：
>	成功：分配空间的起始地址
>	失败：NULL

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//calloc
void test01()
{
	//int * p = malloc(sizeof(int)* 10);

  //calloc 分配在堆区，与malloc不同的是 calloc会初始化数据为0
	int * p = calloc(10, sizeof(int)); 

	for (int i = 0; i < 10;i++)
	{
		printf("%d\n", p[i]);
	}

	if ( p != NULL)
	{
		free(p);
		p = NULL;
	}

}
```



### realloc()

>#include <stdlib.h>
>void *realloc(void *ptr, size_t size);
>功能：
>==重新分配用malloc或者calloc函数在堆中分配内存空间的大小。==
>==realloc不会自动清理增加的内存，需要手动清理，如果指定的地址后面有连续的空间，那么就会在已有地址基础上增加内存，如果指定的地址后面没有空间，那么realloc会重新分配新的连续内存，把旧内存的值拷贝到新内存，同时释放旧内存。==
>参数：
>	ptr：为之前用malloc或者calloc分配的内存地址，如果此参数等于NULL，那么和realloc与malloc功能一致
>	size：为重新分配内存的大小, 单位：字节
>返回值：
>	成功：新分配的堆内存地址
>	失败：NULL

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//realloc  重新分配内存
void test02()
{
	int * p = malloc(sizeof(int)* 10);

	for (int i = 0; i < 10;i++)
	{
		p[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	printf("%d\n", p);

	// 如果重新分配的内存比原来大，那么不会初始化新空间为0
	p = realloc(p, sizeof(int)* 20);

	printf("%d\n", p);

	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", p[i]);
	}

	// 如果重新分配的内存比原来小，那么释放后序空间，只有权限操作申请空间
	p = realloc(p, sizeof(int)* 5);
	printf("%d\n", p);
	printf("%d\n", p[0]);
	printf("%d\n", p[5]);
}

```



### ==free()==

>\#include <stdlib.h>
>
>***\*void\**** ***\**free\**\******\*(\*******\*void\**** ***\**\*******\*ptr\*******\*);\****
>
>功能：释放ptr所指向的一块内存空间，ptr是一个任意类型的指针变量，指向被释放区域的首地址。对同一内存空间多次释放会出错。
>
>参数：
>
>​	ptr：需要释放空间的首地址，被释放区应是由malloc函数所分配的区域。
>
>返回值：无

# 内存分区代码分析

## 返回栈区地址

野指针的产生

```c
#include <stdio.h>
int *fun()
{
	int a = 10;
	return &a;//函数调用完毕，a释放
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	p = fun();
	*p = 100; //操作野指针指向的内存,err

	return 0;
}
```

## 返回data区地址

```c
#include <stdio.h>

int *fun()
{
	static int a = 10;
	return &a; //函数调用完毕，a不释放
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	p = fun();
	*p = 100; //ok
	printf("*p = %d\n", *p);

	return 0;
}
```

## 值传递1

```c
#include <stdio.h>
#include <stdlib.h>

void fun(int *tmp)
{
	tmp = (int *)malloc(sizeof(int));
	*tmp = 100;
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	fun(p); //值传递，形参修改不会影响实参
	printf("*p = %d\n", *p);//err，操作空指针指向的内存

	return 0;
}
```

## 值传递2

```c
#include <stdio.h>
#include <stdlib.h>

void fun(int *tmp)
{
	*tmp = 100;
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	p = (int *)malloc(sizeof(int));

	fun(p); //值传递
	printf("*p = %d\n", *p); //ok，*p为100

	return 0;
}
```

## 返回堆区地址

```c
#include <stdio.h>
#include <stdlib.h>

int *fun()
{
	int *tmp = NULL;
	tmp = (int *)malloc(sizeof(int));
	*tmp = 100;
	return tmp;//返回堆区地址，函数调用完毕，不释放
}

int main(int argc, char *argv[])
{
	int *p = NULL;
	p = fun();
	printf("*p = %d\n", *p);//ok

	//堆区空间，使用完毕，手动释放
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}

	return 0;
}
```

# 注意

==主调函数没有分配内存，被调函数需要用更高级的指针去修饰低级指针，进行分配内存==

错误示例

```c
// pp指针变量为地址值
void allocateSpace(char * pp)
{
  // 在堆上申请100字节
	char * temp  =  malloc(100);
  // 初始化为0
	memset(temp, 0, 100);
  // 复制字符串hello world
	strcpy(temp, "hello world");
  // 将pp指针变量地址值改为hello world
  // 但是跟*p内存空间没有任何关系
	pp = temp;
}

// 目的是调用allocateSpace将*P指针所指的内存区域赋值为“hello world”
// 实际上执行allocateSpace后p是char<null>
void test02()
{
  // 定义了一个指针，初始化为NULL
	char * p = NULL;
  // 将指针变量p做实参
	allocateSpace(p);
	printf("%s\n", p);
}
```

栈图如下：本质上是值传递的锅

![同级指针修饰内存失败解析图](https://raw.githubusercontent.com/YangLuchao/c_study/main/%E5%9B%BE/%E5%90%8C%E7%BA%A7%E6%8C%87%E9%92%88%E4%BF%AE%E9%A5%B0%E5%86%85%E5%AD%98%E5%A4%B1%E8%B4%A5%E8%A7%A3%E6%9E%90%E5%9B%BE.png)

正确示例

``` c
// 参数为二级指针，指向的是*p的内存空间
void allocateSpace2(char ** pp)
{
  // 申请了100字节的内存空间
	char * temp = malloc(100);
  // 全部赋值为0
	memset(temp, 0, 100);
  // 赋值hello world
	strcpy(temp, "hello world");
	// 二级指针指向的一级指针的内存空间
  // 将一级指针的内存空间赋值为temp
	*pp = temp

}

void test03()
{
  // 定义指针*P
	char * p = NULL;
  // 传入*p的引用
	allocateSpace2(&p);
	printf("%s\n", p);

	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}

```































