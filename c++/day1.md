[toc]

# 初识c++

```c++
#include <iostream>  //标准输入输出流   i - input  输入  o - output 输出  stream 流  相当于 stdio.h
using namespace std; //使用  标准  命名空间  


//#include <time.h>
//#include <ctime>
//
//#include <math.h>
//#include <cmath>


//程序入口函数
int main()
{
	// cout  标准输出流对象
	// << 左移  在C++下有了新的寓意  用于在cout后拼接输出的内容   
	// endl   --- end line  刷新缓冲区 并且换行  
	cout << "hello world"  << endl;

	system("pause");  //阻塞
	return EXIT_SUCCESS;  //返回正常退出
}

```

# 双冒号作用域运算符

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//using namespace std;


int atk = 1000;
void test01()
{
	int atk = 2000;
	std::cout << "atk = " << atk << std::endl;
	// ::代表作用域  如果前面什么都不添加 代表全局作用域
	std::cout << "全局 atk = " << ::atk << std::endl;
}


int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}
```

# namespace命名空间

**game1.h**

```c++
#include <iostream>
using namespace std;


namespace KingGlory
{
	void goAtk();
}

```

**game1.cpp**

```c++
#include "game1.h"

void KingGlory::goAtk()
{
	cout << "王者荣耀攻击实现" << endl;
}
```

**game2.h**

```c++
#include <iostream>
using namespace std;


namespace LOL
{
	void goAtk();
}

```

**game2.cpp**

```c++
#include "game2.h"

void  LOL::goAtk()
{
	cout << "LOL攻击实现" << endl;

}
```

**main.cpp**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "game1.h"
#include "game2.h"

//1、命名空间用途： 解决名称冲突
void test01()
{
	KingGlory::goAtk();

	LOL::goAtk();
}

//2、命名空间下 可以放  变量、函数、结构体、类...
namespace A
{
	int m_A;
	void func();
	struct Person
	{};
	class Animal
	{};
}

//3、命名空间 必须要声明在全局作用域下
void test02()
{
	//namespace B{}; 不可以命名到局部作用域
}

//4、命名空间可以嵌套命名空间
namespace B
{
	int m_A = 10;
	namespace C
	{
		int m_A = 20;
	}
}
void test03()
{
	cout << "B空间下的m_A = " << B::m_A << endl;
	cout << "C空间下的m_A = " << B::C::m_A << endl;
}

//5、命名空间是开放的，可以随时给命名空间添加新的成员
namespace B
{
	int m_B = 100;
}
void test04()
{
	cout << "B空间下的m_A = " << B::m_A << endl;
	cout << "B空间下的m_B = " << B::m_B << endl;
}

//6、命名空间可以是匿名的
namespace
{
	int m_C = 1000;
	int m_D = 2000; 
	//当写的命名空间的匿名的，相当于写了  static int m_C = 1000; static int m_D = 2000;
}

void test05()
{
	cout << "m_C = " << m_C   << endl;
	cout << "m_D = " << ::m_D << endl;
}

//7、命名空间可以起别名
namespace veryLongName
{
	int m_E = 10000;
	void func()
	{
		cout << "aaa" << endl;
	}
}



void test06()
{
	namespace veryShortName = veryLongName;
	cout << veryShortName::m_E << endl;
	cout << veryLongName::m_E << endl;

}

int main(){
	//test01();
	//test03();
	//test04();
	//test05();
	test06();
	

	system("pause");
	return EXIT_SUCCESS;
}
```

# using声明以及using编译指令

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace KingGlory
{
	int sunwukongId = 1;
}

namespace LOL
{
	int sunwukongId = 3;
}

void test01()
{
	int sunwukongId = 2;

	//1、using声明
	//using KingGlory::sunwukongId ;  

	//当using声明与 就近原则同时出现，出错，尽量避免
	cout << sunwukongId << endl;

}


void test02()
{
	//int sunwukongId = 2;
	//2、using编译指令
	using namespace KingGlory;
	using namespace LOL;
	//当using编译指令  与  就近原则同时出现，优先使用就近
	//当using编译指令有多个，需要加作用域 区分
	cout << KingGlory::sunwukongId << endl;
	cout << LOL::sunwukongId << endl;
}

```

# C++对C的增强和扩展

## C

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1、全局变量检测增强
int a;
int a = 10;

//2、函数检测增强  返回值没有检测  形参类型没有检测   函数调用参数个数没有检测
getRectS( w  , h)
{

	return w *h;
}
void test01()
{
	printf("%d\n", getRectS(10, 10, 10));
}


//3、类型转换检测增强
void test02()
{
	char * p = malloc(64);
}


//4、struct增强
struct Person
{
	int age;
	//void func(); C语言下 结构体不可以有函数
};

void test03()
{
	struct Person p; //创建结构体变量时候，必须加关键字struct
	p.age = 100;
}


//5、bool类型扩展  C语言下 没有这个类型
//bool a;


//6、三目运算符增强
void test04()
{
	//?:
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	*(a > b ? &a : &b) = 100;  //C语言下 返回的是值  20 = 100

	printf("a = %d\n", a);
	printf("b = %d\n", b);

}


//7、const增强
//全局const
const int m_A = 100; // 受到常量区保护，运行修改失败

void test05()
{
	//m_A = 200;
	//int * p = &m_A;
	//*p = 200;

	//局部const
	const int m_B = 100; //分配到栈上
	//m_B = 200;
	int * p = &m_B;
	*p = 200;

	printf("%d\n", m_B);

	//int arr[m_B]; 在C语言下 const是伪常量，不可以初始化数组

}


```

## c++

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、全局变量检测增强  C++检测出重定义
int a;
//int a = 10;

//2、函数检测增强 返回值检测、形参类型检测、函数调用参数个数
int getRectS(int w,int h)
{

	return w *h;
}
void test01()
{
	printf("%d\n", getRectS(10, 10));
}


//3、类型转换检测增强
void test02()
{
	char * p = (char *)malloc(64);
}

//4、struct增强  C++可以放函数，创建结构体变量，可以简化关键字 struct
struct Person
{
	int age;
	void func()
	{
		age++;
	}
};

void test03()
{
	Person p;
	p.age = 17;
	p.func();
	cout << "p的age = " << p.age << endl;
}

//5、bool类型扩展  C语言下 没有这个类型  C++有bool类型
bool flag = true; // bool类型 代表  真和假   true  ---- 真(1)    false  ---- 假(0)

void test04()
{
	cout << sizeof(bool) << endl; //结果是1个字节
	//flag = false;
	//flag = 100; //将非0的数都转为1
	cout << flag << endl;
}

//6、三目运算符增强
void test05()
{
	//?:
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	(a < b ? a : b )= 100; // C++下返回的是变量  b = 100

	printf("a = %d\n", a);
	printf("b = %d\n", b);
}


//7、const增强
//全局const   和C语言结论一致
const int m_A = 100;
void test06()
{
	//m_A = 200;
	//int * p = (int *)&m_A;

	//*p = 200;


	//局部const
	const int m_B = 100;
	//m_B = 200;
	int * p = (int *)&m_B;
	*p = 200;
	cout << "m_B = " << m_B << endl;

	int arr[m_B]; //C++下const修饰的变量 称为常量 ，可以初始化数组

}

```

# const连接属性

## C

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

	extern const int g_a; 

	printf("g_a = %d\n", g_a);

	system("pause");
	return EXIT_SUCCESS;
}
```

## C++

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main(){

	extern const int g_b;

	cout << "g_b = " << g_b << endl;;

	system("pause");
	return EXIT_SUCCESS;
}
```

## const分配内存的情况

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//1、对const变量 取地址 ，会分配临时内存  
void test01()
{
	const int a = 10;
	int * p = (int *)&a;
}

//2、使用普通变量  初始化 const变量
void test02()
{
	int a = 10;
	const int b = a;

	int *p = (int *)&b;
	*p = 1000;

	cout << "b = " << b << endl;

}

//3、对于自定义数据类型 
struct Person
{
	string m_Name;
	int m_Age;
};
void test03()
{
	const Person p;
	//p.m_Age = 10;

	Person * pp = (Person *)&p;
	(*pp).m_Name = "Tom";
	pp->m_Age = 10;

	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}


int main(){

	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}
```

# 引用的基本语法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//引用基本语法：  类型  &别名 = 原名
void test01()
{
	int a = 10;
	int &b = a;

	b = 100;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}


void test02()
{
	int a = 10;
	//int &b; //引用必须要初始化

	int &b = a;

	//引用一旦初始化后，就不可以引向其他变量

	int c = 100;

	b = c; // 赋值

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//对数组建立引用
void test03()
{
	//1、直接建立引用
	int arr[10];
	int(&pArr)[10] = arr;

	for (int i = 0; i < 10; i++)
	{
		arr[i] = 100 + i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << pArr[i] << endl;
	}


	//2、先定义出数组类型，再通过类型 定义引用
	typedef int(ARRAY_TYPE)[10];
	//类型  &别名 = 原名
	ARRAY_TYPE & pArr2 = arr;

	for (int i = 0; i < 10; i++)
	{
		cout << pArr2[i] << endl;
	}

}

int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 引用

***引用的本质在c++内部实现是一个指针常量.***

***<u>c++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同，只是这个过程是编译器内部实现，用户不可见。</u>***

```c++
//发现是引用，转换为 int* const ref = &a;
void testFunc(int& ref){
	ref = 100; // ref是引用，转换为*ref = 100
}
int main(){
	int a = 10;
	int& aRef = a; //自动转换为 int* const aRef = &a;这也能说明引用为什么必须初始化
	aRef = 20; //内部发现aRef是引用，自动帮我们转换为: *aRef = 20;
	cout << "a:" << a << endl;
	cout << "aRef:" << aRef << endl;
	testFunc(a);
	return EXIT_SUCCESS;
}
```

1 引用

-   1.1 目的：起别名

-   1.2 语法： 类型（与原名类型必须一致）  &别名  =  原名

-   1.3 引用必须要初始化

-   1.4 引用一旦初始化后，就不可以引向其他变量

-   1.5 建立对数组引用

    -   1.5.1 直接建立引用

    -   1.5.2 int arr[10];

    -   1.5.3 int(&pArr)[10] = arr;

-   1.6 先定义出数组类型，再通过类型 定义引用

    -   1.6.1 typedef int(ARRAY_TYPE)[10];

    -   1.6.2 ARRAY_TYPE & pArr2 = arr;

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//引用基本语法：  类型  &别名 = 原名
void test01()
{
	int a = 10;
	int &b = a;

	b = 100;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}


void test02()
{
	int a = 10;
	//int &b; //引用必须要初始化

	int &b = a;

	//引用一旦初始化后，就不可以引向其他变量

	int c = 100;

	b = c; // 赋值

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//对数组建立引用
void test03()
{
	//1、直接建立引用
	int arr[10];
	int(&pArr)[10] = arr;

	for (int i = 0; i < 10; i++)
	{
		arr[i] = 100 + i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << pArr[i] << endl;
	}


	//2、先定义出数组类型，再通过类型 定义引用
	typedef int(ARRAY_TYPE)[10];
	//类型  &别名 = 原名
	ARRAY_TYPE & pArr2 = arr;

	for (int i = 0; i < 10; i++)
	{
		cout << pArr2[i] << endl;
	}

}
```

# 参数的传递方式

1 参数的传递方式

-   1.1 值传递

-   1.2 地址传递

-   1.3 引用传递

```C++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、值传递
void mySwap01(int a  , int b)
{
	int temp = a;
	a = b;
	b = temp;

	/*cout << ":::a = " << a << endl;
	cout << ":::b = " << b << endl;*/
}

//2、地址传递
void mySwap02(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//3、引用传递
void mySwap03(int &a , int &b) // int &a = a; int &b = b;
{
	int temp = a;
	a = b;
	b = temp;
}

void test01()
{
	int a = 10;
	int b = 20;
	//mySwap01(a, b);
	//mySwap02(&a, &b);

	mySwap03(a, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}

int& func()
{
	int a = 10;
	return a;
}

//引用注意事项
void test02()
{
	//1、引用必须引一块合法内存空间
	//int &a = 10;

	//2、不要返回局部变量的引用
	int &ref = func();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
}

int& func2()
{
	static int a = 10;
	return a;
}

void test03()
{
	int &ref = func2();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
	//当函数返回值是引用，那么函数的调用可以作为左值
	func2() = 1000;

	cout << "ref = " << ref << endl;


}
```

## 引用的注意事项

1 注意事项

-   1.1 引用必须引一块合法内存空间

-   1.2 不要返回局部变量的引用

-   1.3 当函数返回值是引用时候，那么函数的调用可以作为左值进行运算

# 指针的引用

1 指针的引用

-   1.1 利用引用可以简化指针

-   1.2 可以直接用同级指针的 引用  给同级指针分配空间

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Person
{
	int age;
};

void allocateSpace(Person ** p)
{
	//p指向指针的指针    *p  指针 指向的是person 本体   **p  person本体
	*p = (Person *)malloc(sizeof(Person));
	(*p)->age = 10;

}

void test01()
{
	Person * p = NULL;
	allocateSpace(&p);

	cout << "p.age = " << p->age <<  endl;
}



void allocateSpace2(Person* &pp) // Person * &pp = p;
{
	pp = (Person *)malloc(sizeof(Person));
	pp->age = 20;
}

void test02()
{
	Person *p = NULL;
	allocateSpace2(p);
	cout << "p.age = " << p->age << endl;
}
```

# 常量的引用

1 常量的引用

-   1.1 const int &ref = 10;

-   1.2 // 加了const之后，  相当于写成  int temp = 10;  const int &ref = temp;

-   1.3 常量引用的使用场景 修饰函数中的形参，防止误操作

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void test01()
{
	//int &ref = 10;

	const int &ref = 10; // 加了const之后，  相当于写成   int temp = 10;  const int &ref = temp;

	int *p = (int *)&ref;
	*p = 10000;

	cout << ref << endl;
}

void showValue(const int &a)
{
	//a = 100000;

	cout << "a = " << a << endl;

}
//常量引用的使用场景 修饰函数中的形参，防止误操作
void test02()
{
	int a = 100;
	showValue(a);

}
```

