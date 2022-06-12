[toc]

# 静态成员变量和静态成员变量

>静态成员变量必须在类中声明，在类外定义
>
>静态数据成员不属于某个对象，在为对象分配空间中不包括静态成员所占空间。
>
>静态数据成员可以通过类名或者对象名来引用。

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Person
{
public:
	//1、静态成员变量
	//静态成员变量 ：编译阶段就分配了内存
	//类内声明 、类外初始化
	//静态成员变量 所有对象都共享同一份数据
	static int m_A;


	//2、静态成员函数
	//所有对象都共享同一个func函数
	static void func()
	{
		//m_C = 100; //静态成员函数 不能访问非静态成员变量
		m_A = 100; //静态成员函数 能访问静态成员变量
		cout << "func调用" << endl;
	}

	int m_C;

private:
	static int m_B; //私有静态成员变量 

	static void func2()
	{
	
	}
};

int Person::m_A = 0;
int Person::m_B = 0;


void test01()
{
	//1、通过对象进行访问
	Person p1;
	cout << p1.m_A << endl;

	Person p2;
	p2.m_A = 100;

	cout << p1.m_A << endl;

	//2、通过类名进行访问
	cout << Person::m_A << endl;

	//静态成员变量 也是有访问权限的，私有权限类外访问不到
	//cout << Person::m_B << endl;

}

void test02()
{
	//通过对象
	Person p1;
	p1.func();
	//通过类名
	Person::func();


	//Person::func2();  静态成员函数也是有访问权限的


}
```

# 单例模式

>静态实例指针私有化，类外声明
>
>将构造函数私有化，不可以创建多个对象
>
>拷贝函数私有化，不可以拷贝
>
>公有化获取实例方法

## 主席类案例

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//主席类
class ChairMan
{
public:
    static ChairMan * getInstacne()
	{
		return singleMan;
	}
private:
	//将构造函数私有化，不可以创建多个对象
	ChairMan(){};

	ChairMan(const ChairMan &){};

//public:
private:
	//将主席指针 私有化，对外提供只读接口
	static  ChairMan * singleMan; //类内声明  类外初始化
};

ChairMan *  ChairMan::singleMan = new ChairMan;

void test01()
{
	/*ChairMan c1;
	ChairMan c2;
	ChairMan * c3 = new ChairMan;*/

	//ChairMan * c1 = ChairMan::singleMan;
	//ChairMan * c2 = ChairMan::singleMan;


	ChairMan * c1 = ChairMan::getInstacne();
	ChairMan * c2 = ChairMan::getInstacne();

	//ChairMan * c3 = new ChairMan(*c1);

	if (c1 == c2)
	{
		cout << "c1 = c2" << endl;
	}
	else
	{
		cout << "c1 != c2" << endl;
	}

	//if (c1 == c3)
	//{
	//	cout << "c1 = c3" << endl;
	//}
	//else
	//{
	//	cout << "c1 != c3" << endl;
	//}


}
```



## 打印机案例

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Printer
{
public:
	static Printer * getInstance()
	{
		return printer;
	}

	void printText(string text)
	{
		m_Count++;
		cout << text << endl;
	}

	int m_Count;

private:

	Printer()
	{ 
		m_Count = 0;
		//cout << "打印机构造调用" << endl; 
	};

	Printer(const Printer & p){};

	static Printer * printer;

	
};

Printer * Printer::printer = new Printer;


void test01()
{
	Printer * p1 = Printer::getInstance();
	p1->printText("入职证明");
	p1->printText("离职证明");
	p1->printText("加薪申请");
	p1->printText("旅游申请");

	cout << "打印机使用次数： " << p1->m_Count << endl;


	Printer * p2 = Printer::getInstance();
	p2->printText("调休申请");

	cout << "打印机使用次数： " << p1->m_Count << endl;

}
```

# C++对象初探

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//#pragma pack(1)

class Person
{
public:

	int m_A; //只有非静态成员变量  属于类对象上

	void func( )  //成员函数  并不属于类对象上
	{
		
	}

	static int m_B; //静态成员变量  不属于类对象上

	static void func2()//静态成员函数  不属于类对象上
	{
		
	}

	double m_C;

};
int Person::m_B = 0;

void test01()
{
	//空类的sizeof结果是1  原因  每个对象都应该在内存上有独一无二的地址，因此给空对象分配1个字节空间
	// Person pArr[10]  pArr[0]  pArr[1]
	Person p1;
	//  空对象 大小 1  
	cout << "sizeof = " << sizeof(p1) << endl;

}

```

# this指针

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age)
	{
		//用途1 ：解决名称冲突
		this->age = age;
	}


	//this指针 隐式加在每个成员函数中
	bool compareAge(Person &p)
	{
		if (this->age == p.age)
		{
			return true;
		}
		return false;
	}


	Person&  personAddPerson(Person &p)
	{
		this->age += p.age;
		return *this; //*this 就是本体
	}

	int age;
};

void test01()
{
	//this指针 指向 被调用的成员函数 所属的对象
	Person p1(10);

	cout << "p1的年龄为： " << p1.age << endl;


	Person p2(10);

	bool ret = p1.compareAge(p2);
	if (ret)
	{
		cout << "p1与p2年龄相等" << endl;
	}


	p1.personAddPerson(p2).personAddPerson(p2).personAddPerson(p2); //链式编程
	cout << "p1的年龄为： " << p1.age << endl;

}

```

# 空指针访问成员函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Person
{
public:

	void showClass()
	{
		cout << "class Name is Person" << endl;
	}

	void showAge()
	{
		/*	if (this == NULL)
			{
			return;
			}*/
		//m_Age = 0;
		cout << "age = " << this->m_Age << endl;
	}

	int m_Age;
};


void test01()
{
	Person * p = NULL;
 
	//p->showClass();

	p->showAge();

}
```

# 常函数和常对象

***this指针的本质： Person \* const this***

>   常函数 ： 修饰成员函数中的 this指针，让指针指向的值不可以修改
>   void showPerson() const {}
>
>   常对象：
>
>   常对象 只能调用常函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age)
	{
		this->m_Age = age;
	}

	//常函数 ： 修饰成员函数中的 this指针，让指针指向的值不可以修改
	void showPerson() const
	{
		//m_Age = 100;

		m_A = 100;

		//this指针的本质： const Person * const this 
		//this = NULL; 指针的指向不可以修改，而指针指向的值 可以改
		cout << "person age = " << this->m_Age << endl;
	}

	void func()
	{
		m_Age = 100;
		cout << "func调用" << endl;
	}

	int m_Age;

	mutable int m_A; //常函数中或常对象 有些特殊属性依然想修改，加入关键字 mutable
};

void test01()
{
	//常对象
	const Person p1(10);
	//p1.m_Age = 10;
	p1.m_A = 10;

	p1.showPerson();

	//p1.func(); //常对象 只能调用常函数
}
```

# 全局函数作友元函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class Building
{
	//利用friend关键字让全局函数  goodGay作为本类好朋友，可以访问私有成员
	friend void goodGay(Building * buliding);

public:
	Building()
	{
		this->m_SittingRoom = "客厅";
		this->m_BedRoom = "卧室";
	}

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom; //卧室
};

//好基友全局函数  可以访问Building的私有属性
void goodGay( Building * buliding)
{
	cout << "好基友正在访问：" << buliding->m_SittingRoom << endl;

	cout << "好基友正在访问：" << buliding->m_BedRoom << endl;
}

void test01()
{
	Building buliding;
	goodGay(&buliding);
}
```



# 类作为友元类

>friend关键字只出现在声明处
>
>其他类、类成员函数、全局函数都可声明为友元
>
>友元函数不是类的成员，不带this指针
>
>友元函数可访问对象任意成员属性，包括私有属性

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Building;
class GoodGay
{
public:

	GoodGay();

	void visit();

	Building * m_building;
};

class Building
{
	//让goodGay类作为 Building的好朋友，可以访问私有成员
	friend class GoodGay;

public:
	Building();

	string m_SittingRoom;

private:
	string m_BedRoom;
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

GoodGay::GoodGay()
{
	this->m_building =  new Building;
}

void GoodGay::visit()
{
	cout << "好基友正在访问： " << this->m_building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << this->m_building->m_BedRoom << endl;
}

void test01()
{
	GoodGay gg;
	gg.visit();
}


```

# 成员函数作为友元函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Building;
class GoodGay
{
public:

	GoodGay();

	void visit(); //可以访问building的私有

	void visit2(); // 不可以访问building的私有

	Building * m_building;
};

class Building
{
	//让GoodGay类中的 visit成员函数作为友元
   friend void GoodGay::visit();
public:
	Building();

	string m_SittingRoom;

private:
	string m_BedRoom;
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

GoodGay::GoodGay()
{
	this->m_building = new Building;
}

void GoodGay::visit()
{
	cout << "好基友正在访问： " << this->m_building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << this->m_building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
	cout << "好基友正在访问： " << this->m_building->m_SittingRoom << endl;
	//cout << "好基友正在访问： " << this->m_building->m_BedRoom << endl;
}


void test01()
{
	GoodGay gg;
	gg.visit();
	gg.visit2();
}

```

