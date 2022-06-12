[toc]

# 数组类的封装和[]运算符的重载

**myArray.h**

```c++
#pragma  once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class MyArray
{
public:

	MyArray(); //默认构造 可以给100容量

	MyArray(int capacity); //有参构造

	MyArray(const MyArray & arr); //拷贝构造

	//尾插法
	void pushBack(int val);

	//根据位置设置数据
	void setData(int pos, int val);

	//根据位置获取数据
	int getData(int pos);

	//获取数组容量
	int getCapcity();

	//获取数组大小
	int getSize();

	//析构
	~MyArray();

	//重载[]运算符
	int& operator[](int index);
	

private:
	int m_Capacity; //数组容量
	int m_Size; //数组大小
	int *pAddress; //真实在堆区开辟的数组的指针
};
```

**myArray.cpp**

```c++
#include "myArray.h"

MyArray::MyArray()
{
	cout << "默认构造函数调用" << endl;
	this->m_Capacity = 100;
	this->m_Size = 0;
	this->pAddress = new int[this->m_Capacity];
}

MyArray::MyArray(int capacity)
{
	cout << "有参构造函数调用" << endl;
	this->m_Capacity = capacity;
	this->m_Size = 0;
	this->pAddress = new int[this->m_Capacity];
}

MyArray::MyArray(const MyArray & arr)
{
	cout << "拷贝构造函数调用" << endl;
	this->m_Capacity = arr.m_Capacity;
	this->m_Size = arr.m_Size;
	//this->pAddress = arr.pAddress;

	this->pAddress = new int[arr.m_Capacity];

	for (int i = 0; i < m_Size;i++)
	{
		this->pAddress[i] = arr.pAddress[i];
	}

}

//尾插法
void MyArray::pushBack(int val)
{
	this->pAddress[this->m_Size] = val;
	this->m_Size++;
}

//根据位置设置数据
void MyArray::setData(int pos, int val)
{
	this->pAddress[pos] = val;
}

//根据位置获取数据
int MyArray::getData(int pos)
{
	return this->pAddress[pos];
}

//获取数组容量
int MyArray::getCapcity()
{
	return this->m_Capacity;

}

//获取数组大小
int MyArray::getSize()
{
	return this->m_Size;
}

//析构
MyArray::~MyArray()
{
	if (this->pAddress != NULL)
	{
		cout << "析构函数调用" << endl;
		delete [] this->pAddress;
		this->pAddress = NULL;
	}
}

int& MyArray::operator[](int index)
{

	return this->pAddress[index];
}
```

**main.cpp**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "myArray.h"


void test01()
{
	MyArray arr;

	for (int i = 0; i < 10;i++)
	{
		arr.pushBack(i);
	}


	for (int i = 0; i < arr.getSize(); i ++)
	{
		cout << arr.getData(i) << endl;
	}


	MyArray arr2(arr);
	for (int i = 0; i < arr2.getSize(); i++)
	{
		cout << arr2.getData(i) << endl;
	}

	arr.setData(0, 1000);

	cout << "arr 0号位置数据为： " << arr.getData(0) << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arr.getData(i) << endl;
	}

	cout << "数组容量为： " << arr.getCapcity() << endl;
	cout << "数组大小为： " << arr.getSize() << endl;

	//小任务： 利用[]方式去索引数组中的元素，可读可写
	cout << "---------------------" << endl;

	arr[0] = 10000;
	cout << arr[0] << endl;

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 加号运算符的重载+

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(){};
	Person(int a, int b) :m_A(a), m_B(b)
	{};

	//利用成员函数实现加号运算符重载
	//Person operator+(Person &p)
	//{
	//	Person temp;
	//	temp.m_A = this->m_A + p.m_A;
	//	temp.m_B = this->m_B + p.m_B;
	//	return temp;
	//}

	int m_A;
	int m_B;
};


//利用全局函数实现加号运算符重载
Person operator+(Person &p1, Person &p2)
{
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}

Person operator+(Person &p1, int num)
{
	Person temp;
	temp.m_A = p1.m_A + num;
	temp.m_B = p1.m_B + num;
	return temp;
}


void test01()
{
	Person p1(10, 10);
	Person p2(20, 20);

	Person p3 = p1 + p2;
	//Person p3 = operator+(p1, p2); //全局函数本质

	//Person p3 = p1.operator+(p2); //成员函数本质

	cout << "p3.m_A = " << p3.m_A << " p3.m_B = " << p3.m_B << endl;


	//运算符重载  可不可以发生 函数重载？  可以

	//p1 + 10;

}

```

# 左移运算符重载<<

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
	friend ostream& operator<<(ostream &cout, Person & p1);

public:

	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}

	//试图利用成员函数 做<<重载
	//void operator<<( Person & p)    // p.operator<<(cout)    p<<cout
	//{
	//
	//}

private:
	int m_A;
	int m_B;
};

//利用全局函数 实现左移运算符重载
ostream& operator<<(ostream &cout, Person & p1)
{
	cout << "m_A = " << p1.m_A << " m_B = " << p1.m_B;
	return cout;
}

void test01()
{
	Person p1(10, 10);

	cout << p1 << endl;

}

```

# 递增运算符重载++

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyInter
{
	friend ostream& operator<<(ostream& cout, MyInter& myInt);
public:
	MyInter()
	{
		m_Num = 0;
	}

	//前置++ 重载
	MyInter& operator++()
	{
		this->m_Num++;
		return *this;
	}

	//后置++ 重载
	MyInter operator++(int)
	{
		//先记录初始状态
		MyInter temp = *this;

		this->m_Num++;

		return temp;
	}

private:
	int m_Num;
};


ostream& operator<<(ostream& cout , MyInter& myInt)
{
	cout << myInt.m_Num;
	return cout;
}

void test01()
{
	MyInter myInt;
	cout << ++(++myInt) << endl; 
	cout << myInt << endl; 
}

void test02()
{
	MyInter myInt;

	cout << myInt++ << endl;
	cout << myInt << endl;

}

```

# 指针运算符的重载-> *

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age)
	{	
		cout << "Person的有参构造调用" << endl;
		this->m_Age = age;
	}

	void showAge()
	{
		cout << "年龄为： "<< this->m_Age << endl;
	}

	~Person()
	{
		cout << "Person的析构调用" << endl;
	}

	int m_Age;
};

class SmartPoint
{
public:
	SmartPoint(Person * person)
	{
		this->m_person = person;
	}

	//重载->运算符
	Person * operator->()
	{
		return this->m_person;
	}
	//重载 * 运算符
	Person& operator*()
	{
		return *m_person;
	}
	~SmartPoint()
	{
		if (this->m_person)
		{
			delete this->m_person;
			this->m_person = NULL;
		}
	}
private:
	Person * m_person;
};

void test01()
{
	//Person * p = new Person(18);
	//(*p).showAge();
	//p->showAge();
	//delete p;


	//利用智能指针 管理 new出来的person的释放操作
	SmartPoint sp(new Person(18));

	sp->showAge(); // 本质sp->->showAge(); 编译器简化为 sp->showAge();

	(*sp).showAge();

}
```

# 赋值运算符的重载=

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//编译器 默认给一个类4个函数   默认构造   析构   拷贝构造 （值拷贝）  operator= (值拷贝)
class Person
{
public:
	Person(char * name, int age)
	{
		this->m_Name = new char[strlen(name) + 1];
		strcpy(this->m_Name, name);
		this->m_Age = age;
	}

	//重载 =
	Person& operator=( const Person &p)
	{
		//先判断原来堆区释放有内容，如果有先释放
		if (this->m_Name != NULL)
		{
			delete [] this->m_Name;
			this->m_Name = NULL;
		}

		this->m_Name = new char[strlen(p.m_Name) + 1];
		strcpy(this->m_Name, p.m_Name);
		this->m_Age = p.m_Age;
		return *this;
	}

	//拷贝构造
	Person(const Person & p)
	{
		this->m_Name = new char[strlen(p.m_Name) + 1];
		strcpy(this->m_Name, p.m_Name);
		this->m_Age = p.m_Age;
	}

	~Person()
	{
		if (this->m_Name!=NULL)
		{
			delete [] this->m_Name;
			this->m_Name = NULL;
		}
	}

	char * m_Name;
	int m_Age;
};


void test01()
{
	Person p1("Tom",10);
	
	Person p2("Jerry",19);
	p2 = p1;

	Person p3("", 0);
	p3 = p2 = p1;


	Person p4 = p3;

	cout << "p1姓名： "<< p1.m_Name << "  p1年龄： " << p1.m_Age << endl;
	cout << "p2姓名： "<< p2.m_Name << "  p2年龄： " << p2.m_Age << endl;
	cout << "p3姓名： " << p3.m_Name << " p3年龄： " << p3.m_Age << endl;

}
```

