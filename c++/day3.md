[toc]

# 立方体类设计

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


/*
设计立方体类(Cube)，求出立方体的面积( 2*a*b + 2*a*c + 2*b*c )和体积( a * b * c)，
分别用全局函数和成员函数判断两个立方体是否相等。
*/

class Cube
{
public:
	//设置长宽高
	void setL(int l)
	{
		m_L = l;
	}
	void setW(int w)
	{
		m_W = w;
	}
	void setH(int h)
	{
		m_H = h;
	}
	//获取长宽高
	int getL()
	{
		return m_L;
	}
	int getW()
	{
		return m_W;
	}
	int getH()
	{
		return m_H;
	}

	//求面积 
	int calculateS()
	{
		return 2 * m_L*m_W + 2 * m_W*m_H + 2 * m_L*m_H;
	}

	//求体积
	int calculateV()
	{
		return m_L * m_W * m_H;
	}

	//利用成员函数 判断立方体是否相等
	bool compareCubeByClass( Cube &c )
	{
		return m_L == c.getL() &&  m_W == c.getW() && m_H == c.getH();
	}

	
private:
	int m_L; //长
	int m_W; //宽
	int m_H; //高
};


//利用全局函数 判断两个立方体是否相等
bool compareCube( Cube &c1, Cube &c2 )
{
	/*if (c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH())
	{
	return true;
	}
	return false;*/

	return c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH();
}

void test01()
{
	Cube c1;
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);

	cout << "c1面积为： " << c1.calculateS() << endl; //600
	cout << "c1体积为： " << c1.calculateV() << endl; //1000

	Cube c2;
	c2.setL(10);
	c2.setW(10);
	c2.setH(10);

	//利用全局函数判断 c1 和 c2是否相等

	bool ret = compareCube(c1, c2);
	if (ret)
	{
		cout << "c1 与 c2 相等" << endl;
	}
	else
	{
		cout << "c1 与 c2 不相等" << endl;
	}


	//利用成员函数 判断  c1 和 c2是否相等
	ret = c1.compareCubeByClass(c2);
	if (ret)
	{
		cout << "成员函数判断：c1 与 c2 相等" << endl;
	}
	else
	{
		cout << "成员函数判断：c1 与 c2 不相等" << endl;
	}

}
```

# 点和圆关系

**point.h**

```c++
#pragma  once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//点类
class Point
{
public:

	//设置 x 、y
	void setX(int x);

	void setY(int y);

	//获取 x 、y
	int getX();

	int getY();

private:
	int m_X;
	int m_Y;
};

```

**point.cpp**

```c++
#include "point.h"



//设置 x 、y
void Point::setX(int x)
{
	m_X = x;
}
void Point::setY(int y)
{
	m_Y = y;
}
//获取 x 、y
int Point::getX()
{
	return m_X;
}
int Point::getY()
{
	return m_Y;
}

```

**cricle.h**

```c++
#pragma  once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "point.h"

//圆类
class Circle
{
public:
	//设置半径
	void setR(int r);

	//获取半径
	int getR();


	//设置圆心
	void setCenter(Point p);


	//获取圆心
	Point getCenter();


	//判断点和圆关系
	void isInCircleByClass(Point p);


private:

	int m_R; //半径

	Point m_Center; // 圆心
};
```

**cricle.cpp**

```c++
#include "circle.h"


//圆类

//设置半径
void Circle::setR(int r)
{
	m_R = r;
}
//获取半径
int Circle::getR()
{
	return m_R;
}

//设置圆心
void Circle::setCenter(Point p)
{
	m_Center = p;
}

//获取圆心
Point Circle::getCenter()
{
	return m_Center;
}

//判断点和圆关系
void Circle::isInCircleByClass(Point p)
{

	int distance = (m_Center.getX() - p.getX())*(m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());

	int rDistance = m_R * m_R;

	if (distance == rDistance)
	{
		cout << "成员函数判断：点在圆上" << endl;
	}
	else if (distance > rDistance)
	{
		cout << "成员函数判断：点在圆外" << endl;
	}
	else
	{
		cout << "成员函数判断：点在圆内" << endl;
	}
}
```

mian.cpp

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "circle.h"
#include "point.h"
/*
设计一个圆形类（AdvCircle），和一个点类（Point），计算点和圆的关系。
假如圆心坐标为x0, y0, 半径为r，点的坐标为x1, y1：
*/

////点类
//class Point
//{
//public:
//
//	//设置 x 、y
//	void setX(int x)
//	{
//		m_X = x;
//	}
//	void setY(int y)
//	{
//		m_Y = y;
//	}
//	//获取 x 、y
//	int getX()
//	{
//		return m_X;
//	}
//	int getY()
//	{
//		return m_Y;
//	}
//private:
//	int m_X;
//	int m_Y;
//};

//
////圆类
//class Circle
//{
//public:
//	//设置半径
//	void setR(int r)
//	{
//		m_R = r;
//	}
//	//获取半径
//	int getR()
//	{
//		return m_R;
//	}
//
//	//设置圆心
//	void setCenter(Point p)
//	{
//		m_Center = p;
//	}
//
//	//获取圆心
//	Point getCenter()
//	{
//		return m_Center;
//	}
//
//	//判断点和圆关系
//	void isInCircleByClass(Point p)
//	{
//
//		int distance = (m_Center.getX() - p.getX())*(m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());
//
//		int rDistance = m_R * m_R;
//
//		if (distance == rDistance)
//		{
//			cout << "成员函数判断：点在圆上" << endl;
//		}
//		else if (distance > rDistance)
//		{
//			cout << "成员函数判断：点在圆外" << endl;
//		}
//		else
//		{
//			cout << "成员函数判断：点在圆内" << endl;
//		}
//	}
//
//private:
//
//	int m_R; //半径
//
//	Point m_Center; // 圆心
//};

//利用全局函数 判断点和圆关系
void isInCircle( Circle c , Point p )
{

	int distance = (c.getCenter().getX() - p.getX())*(c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) *(c.getCenter().getY() - p.getY());

	int rDistance = c.getR() * c.getR();

	if (distance == rDistance)
	{
		cout << "点在圆上" << endl;
	}
	else if (distance > rDistance)
	{
		cout << "点在圆外" << endl;
	}
	else
	{
		cout << "点在圆内" << endl;
	}

}

void test01()
{
	Point p;
	p.setX(10);
	p.setY(9);

	Circle c;
	Point pCenter;
	pCenter.setX(10);
	pCenter.setY(0);
	c.setCenter(pCenter);
	c.setR(10);

	isInCircle(c, p);

	c.isInCircleByClass(p);

}


class A
{
	virtual void func() = 0;
};
class B :public A
{

};
class C :public B
{
};

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 构造函数和析构函数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public: //构造和析构必须要声明在全局作用域

	//构造函数
	//没有返回值  不用写void
	//函数名 与 类名相同
	//可以有参数  ，可以发生重载
	//构造函数 由编译器自动调用一次 无须手动调用
	Person()
	{
		cout << "Person的构造函数调用" << endl;
	}
	

	//析构函数
	//没有返回值   不用写void
	//函数名 与类名相同  函数名前 加 ~
	//不可以有参数 ，不可以发生重载
	//析构函数 也是由编译器自动调用一次，无须手动调用
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

};

void test01()
{
	Person p;

}
```

# 构造函数的分类及地调用

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//构造函数分类
//按照参数分类： 无参构造(默认构造函数) 和 有参构造
//按照类型分类： 普通构造函数    拷贝构造函数
class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数调用" << endl;
	}

	Person(int age)
	{
		m_Age = age;
		cout << "Person的有参构造函数调用" << endl;
	}


	//拷贝构造函数
	Person(const Person &p )  
	{
		cout << "Person的拷贝构造函数调用" << endl;
		m_Age = p.m_Age;
	}

	//析构函数
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

	int m_Age;
	
};

//构造函数的调用
void test01()
{
	//Person p;

	//1、括号法
	//Person p1(10);
	//Person p2(p);

	//注意事项一 
	//不要用括号法 调用无参构造函数  Person p3();  编译器认为代码是函数的声明
	

	//2、显示法
	//Person p3 = Person(10); //有参构造
	//Person p4 = Person(p3); //拷贝构造

	//Person(10); //匿名对象  特点： 当前行执行完后 立即释放

	//cout << "aaa" << endl;

	//注意事项二
	//不要用拷贝构造函数 初始化 匿名对象 Person(p3); 编译器认为 Person p3对象实例化  如果已经有p3  p3就重定义

	
	//3、隐式法  
	Person p5 = 10; //Person p5 = Person(10);
	Person p6 = p5;



}

```

# 拷贝构造函数的调用时机

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数调用" << endl;
	}

	Person(int age)
	{
		m_Age = age;
		cout << "Person的有参构造函数调用" << endl;
	}


	//拷贝构造函数
	Person(const Person &p)
	{
		cout << "Person的拷贝构造函数调用" << endl;
		m_Age = p.m_Age;
	}

	//析构函数
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

	int m_Age;

};


//1、用已经创建好的对象来初始化新的对象
void test01()
{
	Person p1(18);

	Person p2 = Person(p1);

	cout << "p2的年龄：" << p2.m_Age<< endl;

}

//2、值传递的方式 给函数参数传值
void doWork(Person p)
{

}
void test02()
{
	Person p1(100);

	doWork(p1);

}

//3、以值方式 返回局部对象
Person doWork2()
{
	Person p;
	return p;
}

void test03()
{
	Person p = doWork2();
}

/*	
	编译器优化代码后 release版本代码类似以下：
	void doWork2( Person &p ){};

	Person p;
	doWork2(p);
*/

```

# 构造函数的调用规则

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、编译器会给一个类 至少添加3个函数    默认构造（空实现）   析构函数（空实现）   拷贝构造（值拷贝）
//2、如果我们自己提供了 有参构造函数，编译器就不会提供默认构造函数，但是依然会提供拷贝构造函数
//3、如果我们自己提供了 拷贝构造函数，编译器就不会提供其他构造函数
class Person
{
public:

	Person()
	{
		cout << "默认构造函数调用" << endl;
	}

	Person(int age)
	{
		m_Age = age;
		cout << "有参构造函数调用" << endl;
	}

	Person(const Person &p)
	{
		m_Age = p.m_Age;
		cout << "拷贝构造函数调用" << endl;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}

	int m_Age;
};

void test01()
{
	Person p1;//提供拷贝构造后，要自己提供默认构造，否则出错
	p1.m_Age = 20;

	Person p2(p1);

	cout << "p2的年龄为： " << p2.m_Age << endl;

}
```

# 深拷贝与浅拷贝问题以及解决

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	Person( char * name ,int age )
	{
		m_Name = (char *) malloc(strlen(name) + 1);

		strcpy(m_Name, name);

		m_Age = age;
	}

	Person(const Person&p)
	{
	   m_Name =(char*)malloc(strlen(p.m_Name) + 1);
	   strcpy(m_Name, p.m_Name);
	   m_Age = p.m_Age;
	}

	~Person()
	{
		if (m_Name != NULL)
		{
			cout << "Person析构调用" << endl;
			free(m_Name);
			m_Name = NULL;
		}
	}

	char * m_Name; //姓名
	int m_Age;     //年龄
};


void test01()
{
	Person p("德玛西亚", 18);
	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;

	Person p2(p);
	cout << "姓名： " << p2.m_Name << " 年龄： " << p2.m_Age << endl;
}
```

# 初始化列表

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	//Person(int a, int b, int c)
	//{
	//	m_A = a;
	//	m_B = b;
	//	m_C = c;
	//}

	//Person() :m_A(10), m_B(20), m_C(30)
	//{
	//}

	//构造函数名称后  ： 属性(值), 属性（值）...
	Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c)
	{
	}

	int m_A;
	int m_B;
	int m_C;
};

void test01()
{
	Person p(10, 20, 30);
	
	cout << "m_A = " << p.m_A << endl;
	cout << "m_B = " << p.m_B << endl;
	cout << "m_C = " << p.m_C << endl;
}

```

# 类对象作为类成员

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class Phone
{
public:

	Phone(string pName)
	{
		cout << "phone 的有参构造调用" << endl;
		m_PhoneName = pName;
	}

	~Phone()
	{
		cout << "phone 的析构函数调用" << endl;
	}

	string m_PhoneName;
};

class Game
{
public:

	Game(string gName)
	{
		cout << "Game 的有参构造调用" << endl;
		m_GameName = gName;
	}
	~Game()
	{
		cout << "Game 的析构函数调用" << endl;
	}

	string m_GameName;
};


class Person
{
public:

	Person(string name, string pName, string gName) : m_Name(name), m_Phone(pName), m_Game(gName)
	{
		cout << "Person 的有参构造调用" << endl;
	}

	void PlayGame()
	{
		cout << m_Name << "拿着 << " << m_Phone.m_PhoneName << " >> 牌手机，玩着 :" << m_Game.m_GameName << endl;
	}

	~Person()
	{
		cout << "Person 的析构函数调用" << endl;
	}

	string m_Name; //姓名
	Phone m_Phone; //手机
	Game  m_Game;  //游戏
};



void test01()
{
	//当其他类对象 作为本类成员，先构造其他类对象，再构造自身，析构的顺序和构造相反
	Person p("张三", "苹果", "王者荣耀");
	p.PlayGame();

	Person p2("李四", "三星", "消消乐");
	p2.PlayGame();
}

```

# explicit关键字使用

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyString
{
public:
	MyString(char * str)
	{
	
	}
	//explicit用途： 防止利用隐式类型转换方式来构造对象
	explicit MyString(int len)
	{
		
	}
};

void test01()
{


	MyString str1(10);

	MyString str2 = MyString(100);

	//MyString str3 = 10; // "10"

}
```

# new和delete使用

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "Person构造函数调用" << endl;
	}

	Person(int a)
	{
		cout << "Person有参构造调用" << endl;
	}

	~Person()
	{
		cout << "Person析构函数调用" << endl;
	}
};

//malloc 和 new 区别
//malloc 和 free 属于 库函数     new 和delete属于 运算符
//malloc不会调用构造函数   new会调用构造函数
//malloc返回void* C++下要强转     new 返回创建的对象的指针

void test01()
{
	Person * p = new Person;

	delete p;
}

//注意事项 不要用void*去接受new出来的对象,利用void*无法调用析构函数
void test02()
{
	void * p = new Person;

	delete p;
} 

//利用new开辟数组
void test03()
{
	//int * pInt = new int[10];
	//double * pD = new double[10];


	//堆区开辟数组，一定会调用默认构造函数
	Person * pPerson = new Person[10];

	////释放数组时候  需要加[]
	//delete [] pPerson;


	//栈上开辟数组，可不可以没有默认构造,可以没有默认构造
	//Person pArray[10] = { Person(10), Person(20), Person(20) };

}
```

