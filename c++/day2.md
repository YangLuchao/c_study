[toc]

# 设计一个类

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//设计一个类，求圆的周长

const double PI = 3.14;

//class + 类名
//周长公式 ：   2 * pi * m_R
class Circle
{
public: //公共权限

	//类中的函数  称为 成员函数  成员方法
	//求圆周长
	double calculateZC()
	{
		return 2 * PI * m_R;
	}

	//设置半径
	void setR(int r)
	{
		m_R = r;
	}

	//获取半径
	int getR()
	{
		return m_R;
	}


	//类中的变量   称为成员变量  成员属性
	//半径
	int m_R;

};

void test01()
{
	Circle  c1; //通过类 创建一个对象   实例化对象
	
	//给c1 半径赋值
	//c1.m_R = 10;
	c1.setR(10);


	//求c1圆周长
	cout << "圆的半径为： " << c1.getR() << endl;
	cout << "圆的周长为： " << c1.calculateZC() << endl;

}



//2 设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号
class Student
{
public:


	//设置姓名
	void setName(string name)
	{
		m_Name = name;
	}

	//设置学号
	void setId(int id)
	{
		m_Id = id;
	}

	//显示学生信息
	void showStudent()
	{
		cout << "姓名：" << m_Name << " 学号： " << m_Id << endl;
	}

	//属性：
	//姓名
	string m_Name;
	//学号
	int  m_Id;
};

void test02()
{
	Student s1;
	s1.m_Name = "张三";
	s1.m_Id = 1;

	cout << "姓名：" << s1.m_Name << " 学号： " << s1.m_Id << endl;

	Student s2;
	s2.setName("李四");
	s2.setId(2);
	s2.showStudent();

	Student s3;
	s3.setName("王五");
	s3.setId(3);
	s3.showStudent();
}

```

# 内联函数引出-宏缺陷

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//宏缺陷1 ： 必须要加括号保证运算完整
#define  MYADD(x,y)  ((x) +(y))
void test01()
{
	int a = 10;
	int b = 20;
	int ret = MYADD(a, b) * 20;
	cout << ret << endl;
}

//宏缺陷2：  即使加了括号，有些运算依然与预期不符

#define MYCOMPARE(a,b)  (((a) < (b)) ? (a) : (b))

//普通函数 不会出现与预期结果不符的问题
void myCompare(int a, int b)
{
	int ret = a < b ? a : b;
	cout << "ret = " << ret << endl;
}

void test02()
{
	int a = 10;
	int b = 20;

	myCompare(++a, b);

	//int ret = MYCOMPARE(++a, b); //预期是 11 结果变为12   (((++a) < (b)) ? (++a) : (b))

	//cout << "ret = " << ret << endl;

}


//内联函数
//函数的声明和实现必须同时加关键字 inline  才算内联函数
//内联函数 好处  ：解决宏缺陷，本身是一个函数，带来宏优势，以空间换时间，在适当的时候做展开
inline void func();
inline void func(){};
//类内部的成员函数 在函数前都隐式加了关键字 inline

```

c++内联编译会有一些限制，以下情况编译器可能考虑不会将函数进行内联编译：

>不能存在任何形式的循环语句
>
>不能存在过多的条件判断语句
>
>函数体不能过于庞大
>
>不能对函数进行取址操作

==内联仅仅只是给编译器一个建议，编译器不一定会接受这种建议，如果你没有将函数声明为内联函数，那么编译器也可能将此函数做内联编译。一个好的编译器将会内联小的、简单的函数==

# 函数的默认参数和占位参数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


//默认参数 语法  形参  类型 变量  = 默认值
//注意事项 ，如果有一个位置有了默认参数，那么从这个位置起，从左到右都必须有默认值
int func(int a, int b = 10 , int c = 10)
{
	return  a + b + c;
}


void test01()
{
	cout << func(20 , 10) << endl;

}


//函数的声明和实现 只能有一个 提供默认参数，不可以同时加默认参数
void myFunc(int a = 10, int b = 10);
void myFunc(int a , int b){};



//占位参数  只写一个类型进行占位，调用时候必须要传入占位值
//占位参数 用途？ 目前没用
void func2(int a , int = 1)
{

}
```

# 函数的重载

实现函数重载的条件:

>同一个作用域
>
>参数个数不同
>
>参数类型不同
>
>参数顺序不同

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//函数重载条件
//1、在同一个作用域
//2、函数名称相同
//3、参数个数、类型、顺序不同

//class Person
//{
//public:
//	void func()   成员函数 而不是全局函数
//	{
//	}
//};

void func()
{
	cout << "func()调用" << endl;
}

void func(int a)
{
	cout << "func(int a)调用" << endl;
}

void func(double a)
{
	cout << "func(double a)调用" << endl;
}

void func(int a, double b)
{
	cout << "func(int a ,double b)调用" << endl;
}

void func(double a, int b)
{
	cout << "func(double a, int b)调用" << endl;
}

//返回值可不可以作为函数重载的条件 答案：不可以
//int func(int a, double b)
//{
//	cout << "func(int a ,double b)调用" << endl;
//}



void test01()
{
	func(1,3.14);
}



//函数重载中 引用两个版本
//void myFunc(int a)
//{
//	cout << "myfunc(int a )调用" << endl;
//}
void myFunc(int &a) // int & a  = 10;
{
	cout << "myfunc(int &a )调用" << endl;
}
void myFunc(const int &a) // const int &a = 10;
{
	cout << "myfunc( const int &a )调用" << endl;
}


void test02()
{
	int a = 10;
	//myFunc(a);//需要避免二义性出现

}


//函数重载碰到默认参数  注意避免二义性出现
void func2(int a , int b = 10)
{

}

void func2(int a)
{

}

void test03()
{
	//func2(10); //出现二义性
}

```

## 函数重载的原理

编译器为了实现函数重载，也是默认为我们做了一些幕后的工作，编译器用不同的参数类型来修饰不同的函数名，比如void func(); 编译器可能会将函数名修饰成_func，当编译器碰到void func(int x),编译器可能将函数名修饰为_func_int,当编译器碰到void func(int x,char c),==编译器可能会将函数名修饰为_func_int_char==我这里使用”可能”这个字眼是因为编译器如何修饰重载的函数名称并没有一个统一的标准，所以不同的编译器可能会产生不同的内部名。

# extern "C"浅谈

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "test.h"


//告诉编译器  show函数用C语言方式 做链接
//extern "C" void show();




void test01()
{
	show();//_Z4showv;在C++中有函数重载会修饰函数名，但是show是c语言文件，因此链接失败
}



int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}
```

**test.h**

```c
#ifdef __cplusplus  // 两个下划线  __  c plus plus
extern "C" {
#endif

#include <stdio.h>

	void show();


#ifdef __cplusplus
}
#endif
```

**test.c**

```c
#include "test.h"

void show()
{
	printf("hello world\n");
}
```

# C语言和C++语言的封装

## c语言下的封装

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Person
{
	char  name[64];
	int age;
};

void PersonEat(struct Person * p)
{
	printf("%s在吃人饭\n",p->name);
}

void test01()
{
	struct Person p;
	strcpy(p.name, "张三");
	p.age = 10;

	PersonEat(&p);
}


struct Dog
{
	char name[64];
	int age;
};

void DogEat(struct Dog * dog)
{
	printf("%s在吃狗粮\n", dog->name);
}

void test02()
{
	struct Dog d;
	strcpy(d.name, "旺财");
	d.age = 100;

	DogEat(&d);


	struct Person p;
	strcpy(p.name, "老王");

	DogEat(&p);

}
```

## c++语言下的封装

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct  Person
{
	//公共权限
public:
	char name[64];
	int age;

	void PersonEat()
	{
		printf("%s在吃人饭\n", name);
	}
};

struct Dog
{
	//公共权限
public:
	char name[64];
	int age;

	void DogEat()
	{
		printf("%s在吃狗粮\n", name);
	}
};

//C++封装 理念：  将属性和行为作为一个整体，来表现生活中的事物

//第二次理念： 将属性和行为  加以权限控制

void test01()
{
	struct Person p;
	strcpy(p.name, "老王");

	p.PersonEat();

	//p.DogEat();
}


//struct和class 区别？
//class 默认权限  私有权限  而 struct默认权限是 公共权限
//访问权限
// public  公共权限    成员 类内  类外 都可以访问	 
// private 私有权限    成员 类内  可以访问  类外  不可以访问  儿子不可以访问父亲的private权限内容
// protected 保护权限  成员 类内  可以访问  类外  不可以访问  儿子可以访问父亲的protected权限内容

class Person2
{
public:
	string m_Name; //公共权限

protected:
	string m_Car;  //保护权限

private:
	int  m_pwd;  //私有权限

public:

	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_pwd = 123456;
	}

};

void test02()
{
	Person2 p;
	p.m_Name = "李四"; //公共权限  类外可以访问
//	p.m_Car = "劳斯莱斯"; //保护权限  类外访问不到
//	p.m_pwd = 123; //私有权限  类外不可以访问
}
```



# 尽量将成员属性设置为私有

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Person
{
public:
	//设置姓名
	void setName(string name)
	{
		m_Name = name;
	}
	//获取姓名
	string getName()
	{
		return m_Name;
	}

	//获取年龄
	int getAge()
	{
		return m_Age;
	}

	//设置年龄
	void setAge(int age)
	{
		if ( age < 0 || age > 150)
		{
			cout << "你这个老妖精" << endl;
			return;
		}
		m_Age = age;
	}

	//设置情人
	void setLover(string lover)
	{
		m_Lover = lover;
	}

private:
	string m_Name;  //姓名  可读可写
	int m_Age = 18;      //年龄  可读 可写（0 ~ 150之间）
	string m_Lover; //情人  只写
};

void test01()
{
	Person p;
	//可以将char * 隐式类型转换为 string
	p.setName("张三");
	cout << "姓名： " << p.getName() << endl;

	//获取年龄
	p.setAge(100);
	cout << "年龄： " << p.getAge() << endl;

	//设置情人
	p.setLover("苍井");

	//cout << "张三情人是："<< p.m_Lover <<endl; //情人是只写权限  外部访问不到

}
```

