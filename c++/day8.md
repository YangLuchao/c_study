[toc]

# 模板函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void mySwapInt(int &a ,int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void mySwapDouble(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}


//利用模板实现通用交换函数
template<typename T>  //T代表一个通用的数据类型，告诉编译器如果下面紧跟着的函数或者类中出现T不要报错
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

//模板不能单独使用，必须指定出T才可以使用
template<typename T>
void mySwap2()
{
}

void test01()
{
	int a = 10;
	int b = 20;
//	mySwapInt(a, b);
	char c1 = 'c';
	//1、自动类型推导，必须推导出一致的T数据类型，才可以正常的使用模板
	//mySwap(a, c1); //推导不出一致的T，因此无法调用
	//mySwap(a, b);


	//2、显示指定类型
	mySwap<int>(a, b);


	mySwap2<int>(); //必须告诉编译器T类型才可以调用

	cout << a << endl;
	cout << b << endl;


	double c = 3.14;
	double d = 1.1;

//	mySwapDouble(c, d);
	mySwap(c, d);

	cout << c << endl;
	cout << d << endl;

}

```

# 模板练习-char和int类型数组排序

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template <class T>
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

//需求 通过一个通用排序函数  实现对char和int数组的排序，排序顺序 从大到小， 算法  选择排序
template< class  T > // typename 和 class 一样
void mySort( T arr[] , int len)
{
	for (int i = 0; i < len;i++)
	{
		int max = i;
		for (int j = i + 1; j < len;j++)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}

		//判断 算出的max和开始认定的i是否一致，如果不同交换数据
		if (i != max)
		{
			mySwap(arr[i], arr[max]);
		}
	}

}

template<class T>
void printArray(T arr[] , int len)
{
	for (int i = 0; i < len;i++)
	{
		cout << arr[i] << endl;
	}
}

void test01()
{
	char charArray[] = "helloworld";
	
	int len = strlen(charArray);
	mySort(charArray, len);

//	printArray(charArray, len);


	int intArray[] = { 5, 7, 1, 4, 2, 3 };
	len = sizeof(intArray) / sizeof(int);
	mySort(intArray, len);
	printArray(intArray, len);


}

```

# 函数模板和普通函数的区别以及调用规则

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、函数模板和普通函数的区别
template<class T>
T myAdd(T a , T b)
{
	return a + b;
}

int myAdd2(int a, int b)
{
	return a + b;
}
void test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	//myAdd(a, c); //如果使用自动类型推导，是不可以发生隐式类型转换的

	cout << myAdd2(a, c) << endl; //普通函数 可以发生隐式类型转换
}


//2、函数模板和普通函数的调用规则
template<class T>
void myPrint(T a ,T b)
{
	cout << "函数模板调用" << endl;
}

/*
函数模板通过具体类型产生不同的函数  --- 通过函数模板产生的函数  称为 模板函数
void myPrint(int a ,int b)
{
cout << "函数模板调用" << endl;
}

void myPrint(double a ,double b)
{
cout << "函数模板调用" << endl;
}
*/

template<class T>
void myPrint(T a, T b ,T c)
{
	cout << "函数模板(T a, T b ,T c)调用" << endl;
}

void myPrint(int a, int b)
{
	cout << "普通函数调用" << endl;
}



void test02()
{
	//1、如果函数模板和普通函数都可以调用，那么优先调用普通函数
	int a = 10;
	int b = 20;
	//myPrint(a, b);

	//2、如果想强制调用函数模板，可以使用空模板参数列表
	myPrint<>(a, b);

	//3、函数模板也可以发生函数重载
	myPrint(a, b, 10);

	//4、如果函数模板能产生更好的匹配，那么优先使用函数模板
	char c = 'c';
	char d = 'd';
	myPrint(c, d);

}

```

# 模板的局限性

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;

};

//显示两个变量 对比 函数
template<class T>
bool myCompare(T &a ,T&b)
{
	if (a == b)
	{
		return true;
	}
	return false;
}

//利用具体化技术 实现对自定义数据类型 提供特殊模板
template<> bool myCompare(Person &a, Person &b)
{
	if (a.m_Name == b.m_Name && a.m_Age == b.m_Age)
	{
		return true;
	}
	return false;
}

void test01()
{
	//int a = 10;
	//int b = 10;

	//bool ret = myCompare(a, b);

	//if (ret )
	//{
	//	cout << "a == b" << endl;
	//}
	//else
	//{
	//	cout << "a != b" << endl;
	//}

	Person p1("Tom", 19);
	Person p2("Tom", 20);

	bool ret = myCompare(p1, p2);
	if (ret)
	{
		cout << "p1 == p2" << endl;
	}
	else
	{
		cout << "p1 != p2" << endl;
	}
}
```

# 类模板

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
template<class NAMETYPE, class AGETYPE = int > //类模板中 可以有默认参数
class Person
{
public:
	Person(NAMETYPE name, AGETYPE age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "姓名： " << this->m_Name << " 年龄： " << this->m_Age << endl;
	}
	NAMETYPE m_Name;
	AGETYPE m_Age;
};

void test01()
{
	
	//类模板和函数模板区别：
	//1、类模板不可以使用自动类型推导，只能用显示指定类型
	//2、类模板中 可以有默认参数
	//Person p1("孙悟空", 100);

	Person<string > p1("孙悟空", 100);
	p1.showPerson();
}
```

# 类模板中成员函数的创建时机

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person1
{
public:
	void showPerson1()
	{
		cout << "Person1 show 调用" << endl;
	}
};

class Person2
{
public:
	void showPerson2()
	{
		cout << "Person2 show 调用" << endl;
	}
};


//类模板中的成员函数  并不是一开始创建的，而是在运行阶段确定出T的数据类型才去创建
template<class T>
class MyClass
{
public:
	void func1()
	{
		obj.showPerson1();
	}
	void func2()
	{
		obj.showPerson2();
	}

	T obj;
};

void test01()
{
	MyClass <Person2> p1;
	//p1.func1();
	p1.func2();
}
```

# 类模板做函数的参数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
template<class T1, class T2> //类模板中 可以有默认参数
class Person
{
public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "姓名： " << this->m_Name << " 年龄： " << this->m_Age << endl;
	}
	T1 m_Name;
	T2 m_Age;
};

//1、指定传入类型
void doWork(Person <string, int>&p)
{
	p.showPerson();
}

void test01()
{
	Person <string, int>p("孙悟空", 999);
	doWork(p);
}


//2、参数模板化
template<class T1, class T2>
void doWork2(Person <T1, T2>&p)
{
	cout << "T1数据类型： " << typeid(T1).name() << endl;
	cout << "T2数据类型： " << typeid(T2).name() << endl;
	p.showPerson();
}

void test02()
{
	Person<string, int>p("猪八戒", 998);
	doWork2(p);
}


//3、整个类 模板化
template<class T>
void doWork3( T &p)
{
	cout << "T的数据类型： " << typeid(T).name() << endl;
	p.showPerson();
}

void test03()
{
	Person<string, int>p("唐僧", 10000);
	doWork3(p);
}

```

# 类模板碰到继承问题及解决

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template<class T>
class Base
{
public:
	T m_A;
};

//必须要指定出父类中的T数据类型，才能给子类分配内存
class Son :public Base<int>
{

};



template<class T>
class Base2
{
public:
	T m_A;
};

template<class T1 ,class T2>
class Son2 :public Base2<T2>
{
public:

	Son2()
	{
		cout << typeid(T1).name() << endl;
		cout << typeid(T2).name() << endl;
	}

	T1 m_B;
};

void test01()
{
	Son2 <int, double> s;

}
```

# 类模板中的成员函数类外实现

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

template<class T1,class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	//{
	//	this->m_Name = name;
	//	this->m_Age = age;
	//}

	void showPerson();
	//{
	//	cout << "姓名： " << this->m_Name << " 年龄：" << this->m_Age << endl;
	//}

	T1 m_Name;
	T2 m_Age;
};

template<class T1,class T2>
Person<T1,T2>::Person(T1 name, T2 age)
{
	this->m_Name = name;
	this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson()
{
	cout << "姓名： " << this->m_Name << " 年龄：" << this->m_Age << endl;
}


void test01()
{
	Person <string, int>p("Tom", 10);
	p.showPerson();
}
```

# 类模板的成员函数的分文件编写

**person.hpp**

```c++
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age);

	void showPerson();
	
	T1 m_Name;
	T2 m_Age;
};


template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
	this->m_Name = name;
	this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson()
{
	cout << "姓名： " << this->m_Name << " 年龄：" << this->m_Age << endl;
}
```

**person.cpp**

```c++
//#include "person.h"
//
//template<class T1, class T2>
//Person<T1, T2>::Person(T1 name, T2 age)
//{
//	this->m_Name = name;
//	this->m_Age = age;
//}
//
//template<class T1, class T2>
//void Person<T1, T2>::showPerson()
//{
//	cout << "姓名： " << this->m_Name << " 年龄：" << this->m_Age << endl;
//}
```

**main.cpp**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "person.hpp"
#include <string>

void test01()
{
	Person<string, int> P("Jerry", 20);
	P.showPerson();
}


int main(){

	test01();

	
	system("pause");
	return EXIT_SUCCESS;
}
```

# 类模板碰到友元函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

template<class T1,class T2>
class Person;

template<class T1,class T2>
void printPerson2(Person<T1, T2> &p);

template<class T1,class T2>
void printPerson3(Person<T1, T2>&p)
{
	cout << "类外实现 --- 姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

template<class T1, class T2>
class Person
{
	//1、友元函数 类内实现
	friend void printPerson(Person<T1, T2> &p)
	{
		cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
	}

	//2、友元函数 类外实现
	friend void printPerson2<>(Person<T1, T2> &p);

	
	friend void printPerson3<>(Person<T1, T2> &p);
public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

private:
	T1 m_Name;
	T2 m_Age;
};

template<class T1,class T2>
void printPerson2(Person<T1, T2> &p)
{
	cout << "类外实现 --- 姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

void test01()
{
	Person <string, int> p("Tom", 100);
	printPerson(p);
	printPerson2(p);
	printPerson3(p);
}
```

# 模板应用-数组类封装

**myArray.hpp**

```c++
#pragma  once 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template<class T>
class MyArray
{
public:
	//MyArray(){};

	//有参构造
	MyArray(int capacity)
	{
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	//拷贝构造
	MyArray(const MyArray & arr)
	{
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[this->m_Capacity];
		for (int i = 0; i < arr.m_Size;i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//重载=   
	MyArray& operator=( const MyArray & arr)
	{
		if (this->pAddress)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
		}

		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[this->m_Capacity];
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}


	//重载[] 
	T& operator[] (int index)
	{
		return this->pAddress[index];
	}

	//尾插法
	void pushBack(const T&val)
	{
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}

	//获取数组容量
	int getCapacity()
	{
		return this->m_Capacity;
	}

	//获取数组大小
	int getSize()
	{
		return this->m_Size;
	}

	//析构
	~MyArray()
	{
		if (this->pAddress)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}

private:
	T * pAddress; //指向堆区真实数组指针

	int m_Capacity; //数组容量

	int m_Size;  //数组大小

};
```

**main.cpp**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "myArray.hpp"
#include <string>

class Person
{
public:
	Person(){};
	Person(string name,int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void myPrintInt(MyArray <int> &myIntArr)
{

	for (int i = 0; i < myIntArr.getSize();i++)
	{
		cout << myIntArr[i] << endl;
	}
}

void test01()
{
	MyArray <int> myIntArr(100);
	for (int i = 0; i < 10;i++)
	{
		myIntArr.pushBack(i + 100);
	}
	myPrintInt(myIntArr);

}

void myPrintPerson(MyArray<Person> &myPersonArr)
{
	for (int i = 0; i < myPersonArr.getSize();i++)
	{
		cout << "姓名： " << myPersonArr[i].m_Name << " 年龄：" << myPersonArr[i].m_Age << endl;
	}
}

void test02()
{
	MyArray<Person> myPersonArr(100);
	Person p1("孙悟空", 1000);
	Person p2("猪八戒", 800);
	Person p3("唐僧", 500);
	Person p4("沙悟净", 300);
	Person p5("白龙马", 10000);

	myPersonArr.pushBack(p1);
	myPersonArr.pushBack(p2);
	myPersonArr.pushBack(p3);
	myPersonArr.pushBack(p4);
	myPersonArr.pushBack(p5);

	myPrintPerson(myPersonArr);

	cout << "数组容量： " << myPersonArr.getCapacity() << endl;
	cout << "数组大小： " << myPersonArr.getSize() << endl;
}

```

