[toc]

# 数组和字符串

数组属于构造数据类型

-   l 一个数组可以分解为多个数组元素：这些数组元素可以是基本数据类型或构造类型。

```c
int a[10];  
struct Stu boy[10];
```

-   按数组元素类型的不同，数组可分为：数值数组、字符数组、指针数组、结构数组等类别

```c
int a[10];
char s[10];
char *p[10];
```

## 一维数组

### 一维数组初始化

```c
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };//定义一个数组，同时初始化所有成员变量
	int a[10] = { 1, 2, 3 };//初始化前三个成员，后面所有元素都设置为0
	int a[10] = { 0 };//所有的成员都设置为0
	
	//[]中不定义元素个数，定义时必须初始化
	int a[] = { 1, 2, 3, 4, 5 };//定义了一个数组，有5个成员
```

### 二维数组初始化

```c
//分段赋值 	int a[3][4] = {{ 1, 2, 3, 4 },{ 5, 6, 7, 8, },{ 9, 10, 11, 12 }};
	int a[3][4] = 
	{ 
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8, },
		{ 9, 10, 11, 12 }
	};

	//连续赋值
	int a[3][4] = { 1, 2, 3, 4 , 5, 6, 7, 8, 9, 10, 11, 12  };

	//可以只给部分元素赋初值，未初始化则为0
	int a[3][4] = { 1, 2, 3, 4  };

	//所有的成员都设置为0
	int a[3][4] = {0};

	//[]中不定义元素个数，定义时必须初始化
	int a[][4] = { 1, 2, 3, 4, 5, 6, 7, 8};
```

### 数组名

==数组名是一个地址的常量，代表数组中首元素的地址。==

### 一维数组名

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// int arr[]  可读性更高
void printArray(int arr[] , int len) //int arr[]等价于  int * arr
{
	for (int i = 0; i < len;i++)
	{
		printf("%d\n", arr[i]);
	}
}

void test01()
{

	//一维数组名是不是指针？
	int arr[5] = { 1, 2, 3, 4, 5 };

	printf("%d\n", sizeof(arr));

	//有两种特殊情况，一维数组名不是 指向第一个元素的指针
	//1、sizeof
	//2、对数组名取地址   得到数组指针 步长是整个数组长度

	
	//printf("%d\n", &arr);
	//printf("%d\n", &arr + 1);
	
	//int * p =  arr;
	int len = sizeof(arr) / sizeof(int);
	printArray(arr, len);

	//arr数组名  它是一个指针常量 指针的指向不可以修改的，而指针指向的值可以改 int * const a ; 
	//arr[0] = 1000;
	//arr = NULL;

	//数组索引 可不可以为负数   答案：可以
	int * p = arr;
	p = p + 3;
	printf("%d\n",p[-1]);     //给人看的
	printf("%d\n", *(p - 1)); //给机器看的
}

```

### 数组指针的定义方式

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//数组指针的定义方式
//1、先定义数组类型，再通过类型定义数组指针
void test01()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	// ARRARY_TYPE 代表存放5个int类型元素的数组 的数组类型
	typedef int(ARRARY_TYPE)[5];
	
	/*ARRARY_TYPE arr2;
	for (int i = 0; i < 5;i++)
	{
		arr2[i] = 100 + i;
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", arr2[i]);
	}*/

	ARRARY_TYPE * arrP = &arr;
	// *arrP == arr == 数组名
	for (int i = 0; i < 5;i++)
	{
		printf("%d\n", (*arrP)[i]);
	}

}

void test02()
{
	//先定义数组指针类型，再通过类型定义数组指针
	int arr[5] = { 1, 2, 3, 4, 5 };

	typedef int(*ARRARY_TYPE)[5];

	ARRARY_TYPE arrP = &arr;

	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", (*arrP)[i]);
	}

}

void test03()
{
	//直接定义数组指针变量
	int arr[5] = { 1, 2, 3, 4, 5 };

	int(* p )[5] = &arr;

	for (int i = 0; i < 5;i++)
	{
		printf("%d\n", (*p)[i]);
	}

}
```

### 二维数组名

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void test01()
{
	//可读性高
	int arr[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9}
	};

	/*int arr2[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr3[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };*/


	//除了两种特殊情况外 ，二维数组名称是 指向第一个一维数组  数组指针
	//特殊情况1  sizeof
	//特殊情况2  对数组名取地址 &arr  获取的是二维数组的 数组指针 int(*p)[3][3] = &arr;
	//printf("%d\n", sizeof(arr));

	int(*pArray)[3] = arr;

	//访问二维数组中的 6 这个元素
	printf("%d\n", arr[1][2]);  //给人看
	printf("%d\n", *(*(pArray + 1) + 2)); //给机器看

}


//void printArray(int (*array)[3], int row, int col)
//void printArray(int array[][3], int row ,int col)
void printArray(int array[3][3], int row ,int col) //array[3][3] 等价于 一维数组指针   int (*array)[3]
{
	for (int i = 0; i < row; i ++)
	{
		for (int j = 0; j < col;j ++)
		{
			//printf("%d ", array[i][j]);
			printf("%d ", *(*(array + i) + j));
		}
		printf("\n");
	}
}

//二维数组做函数参数
void test02()
{
	int arr[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};

	printArray(arr, 3, 3);

}
```



## 字符数组与字符串

-   ==C语言中没有字符串这种数据类型，可以通过char的数组来替代；==
-   ==字符串一定是一个char的数组，但char的数组未必是字符串；==
-   ==数字0(和字符‘\0’等价)结尾的char数组就是一个字符串==，但如果char数组没有以数字0结尾，那么就不是一个字符串，只是普通字符数组，所以==字符串是一种特殊的char的数组。==

```c
#include <stdio.h>

int main()
{
	char c1[] = { 'c', ' ', 'p', 'r', 'o', 'g' }; //普通字符数组
	printf("c1 = %s\n", c1); //乱码，因为没有’\0’结束符

	//以‘\0’(‘\0’就是数字0)结尾的字符数组是字符串
	char c2[] = { 'c', ' ', 'p', 'r', 'o', 'g', '\0'}; 
	printf("c2 = %s\n", c2);

	//字符串处理以‘\0’(数字0)作为结束符，后面的'h', 'l', 'l', 'e', 'o'不会输出
	char c3[] = { 'c', ' ', 'p', 'r', 'o', 'g', '\0', 'h', 'l', 'l', 'e', 'o', '\0'};
	printf("c3 = %s\n", c3);

	return 0;
}
```

## 字符串数组初始化

```c
#include <stdio.h>

// C语言没有字符串类型，通过字符数组模拟
// C语言字符串，以字符‘\0’, 数字0
int main()
{
	//不指定长度, 没有0结束符，有多少个元素就有多长
	char buf[] = { 'a', 'b', 'c' };
	printf("buf = %s\n", buf);	//乱码

	//指定长度，后面没有赋值的元素，自动补0
	char buf2[100] = { 'a', 'b', 'c' };
char buf[1000]={“hello”};
	printf("buf2 = %s\n", buf2);

	//所有元素赋值为0
	char buf3[100] = { 0 };

	//char buf4[2] = { '1', '2', '3' };//数组越界

	char buf5[50] = { '1', 'a', 'b', '0', '7' };
	printf("buf5 = %s\n", buf5);

	char buf6[50] = { '1', 'a', 'b', 0, '7' };
	printf("buf6 = %s\n", buf6);

	char buf7[50] = { '1', 'a', 'b', '\0', '7' };
	printf("buf7 = %s\n", buf7);

	//使用字符串初始化，编译器自动在后面补0，常用
	char buf8[] = "agjdslgjlsdjg";

	//'\0'后面最好不要连着数字，有可能几个数字连起来刚好是一个转义字符
	//'\ddd'八进制字义字符，'\xdd'十六进制转移字符
	// \012相当于\n
	char str[] = "\012abc";
	printf("str == %s\n", str);

	return 0;
}
```

## 字符创的输入输出

#### gets()

>\#include <stdio.h>
>
>char *gets (char *s);
>
>功能：从标准输入读入字符，并保存到s指定的内存空间，直到出现换行符或读到文件结尾为止。
>
>参数：
>
>​	s：字符串首地址
>
>返回值：
>
>​	成功：读入的字符串
>
>​	失败：NULL

gets(str)与scanf(“%s”,str)的区别：

-   gets(str)允许输入的字符串含有空格

-   scanf(“%s”,str)不允许含有空格

注意：由于scanf()和gets()无法知道字符串s大小，必须遇到换行符或读到文件结尾为止才接收输入，因此容易导致字符数组越界(缓冲区溢出)的情况。

#### fgets()

>\#include <stdio.h>
>
>char *fgets (char *s,int size,FILE *stream);
>
>功能：从stream指定的文件内读入字符，保存到s所指定的内存空间，直到出现换行字符、读到文件结尾或是已读了size - 1个字符为止，最后会自动加上字符 '\0' 作为字符串结束。
>
>参数：
>
>​	s：字符串
>
>​	size：指定最大读取字符串的长度（size - 1）
>
>​	stream：文件指针，如果读键盘输入的字符串，固定写为stdin
>
>返回值：
>
>​	成功：成功读取的字符串
>
>​	读到文件尾或出错： **NULL**

fgets()在读取一个用户通过键盘输入的字符串的时候，同时把用户输入的回车也做为字符串的一部分。通过scanf和gets输入一个字符串的时候，不包含结尾的“\n”，但通过fgets结尾多了“\n”。fgets()函数是安全的，不存在缓冲区溢出的问题。

#### puts()

>#include <stdio.h>
>int puts(const char *s);
>功能：标准设备输出s字符串，在输出完成后自动输出一个'\n'。
>参数：
>	s：字符串首地址
>返回值：
>	成功：非负数
>	失败：-1

#### fputs()

>#include <stdio.h>
>int fputs(const char * str, FILE * stream);
>功能：将str所指定的字符串写入到stream指定的文件中， 字符串结束符 '\0'  不写入文件。 
>参数：
>	str：字符串
>	stream：文件指针，如果把字符串输出到屏幕，固定写为stdout
>返回值：
>	成功：0
>	失败：-1

fputs()是puts()的文件操作版本，但fputs()不会自动输出一个'\n'。

#### strlen()

>#include <string.h>
>size_t strlen(const char *s);
>功能：计算指定指定字符串s的长度，不包含字符串结束符‘\0’
>参数：
>s：字符串首地址
>返回值：字符串s的长度，size_t为unsigned int类型

#### sscanf()

>#include <stdio.h>
>int sscanf(const char *str, const char *format, ...);
>功能：
>    从str指定的字符串读取数据，并根据参数format字符串来转换并格式化数据。
>参数：
>	str：指定的字符串首地址
>	format：字符串格式，用法和scanf()一样
>返回值：
>	成功：成功则返回参数数目，失败则返回-1
>	失败： - 1

| ***\*格式\**** | ***\*作用\****                     |
| -------------- | ---------------------------------- |
| %*s或%*d       | 跳过数据                           |
| %[width]s      | 读指定宽度的数据                   |
| %[a-z]         | 匹配a到z中任意字符(尽可能多的匹配) |
| %[aBc]         | 匹配a、B、c中一员，贪婪性          |
| %[^a]          | 匹配非a的任意字符，贪婪性          |
| %[^a-z]        | 表示读取除a-z以外的所有字符        |

```c
//1. 跳过数据
void test01(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	//匹配第一个字符是否是数字，如果是，则跳过
	//如果不是则停止匹配
	sscanf("123456aaaa", "%*d%s", buf); 
	printf("buf:%s\n",buf);
}

//2. 读取指定宽度数据
void test02(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	sscanf("123456aaaa", "%7s", buf);
	printf("buf:%s\n", buf);
}
//3. 匹配a-z中任意字符
void test03(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	//先匹配第一个字符，判断字符是否是a-z中的字符，如果是匹配
	//如果不是停止匹配
	sscanf("abcdefg123456", "%[a-z]", buf);
	printf("buf:%s\n", buf);
}

//4. 匹配aBc中的任何一个
void test04(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	//先匹配第一个字符是否是aBc中的一个，如果是，则匹配，如果不是则停止匹配
	sscanf("abcdefg123456", "%[aBc]", buf);
	printf("buf:%s\n", buf);
}

//5. 匹配非a的任意字符
void test05(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	//先匹配第一个字符是否是aBc中的一个，如果是，则匹配，如果不是则停止匹配
	sscanf("bcdefag123456", "%[^a]", buf);
	printf("buf:%s\n", buf);
}

//6. 匹配非a-z中的任意字符
void test06(){
	char buf[1024] = { 0 };
	//跳过前面的数字
	//先匹配第一个字符是否是aBc中的一个，如果是，则匹配，如果不是则停止匹配
	sscanf("123456ABCDbcdefag", "%[^a-z]", buf);
	printf("buf:%s\n", buf);
}
```



# 查找子串

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
	算法优化
	memcmp(str , subStr ,3 ) == 0;
*/
int myStrstr(char * str , char * subStr)
{
	int num = 0;
	while (*str != '\0')
	{
		if (*str != *subStr)
		{
			num++;
			str++;
			continue;
		}

		//创建两个临时指针 做二次对比
		char * tmpStr = str;
		char * tmpSubstr = subStr;

		while (*tmpSubstr != '\0')
		{
			if (*tmpStr != *tmpSubstr)
			{
				//匹配失败
				num++;
				str++;
				break;
			}
			tmpStr++;
			tmpSubstr++;
		}
		if (*tmpSubstr == '\0')
		{
			//匹配成功
			return num;
		}

	}

	return -1;
}

void test01()
{
	char * str = "abdnfcdefgdfasdfaf";

	int ret = myStrstr(str, "dnf");

	if ( ret != -1)
	{
		printf("找到了子串，位置为：%d\n", ret);
	}
	else
	{
		printf("未找到子串\n");
	}

}
```

