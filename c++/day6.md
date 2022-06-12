[toc]

# 关系运算符的重载:==/!=

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class  Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	bool operator==( Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}


	bool operator!=(Person & p)
	{
		return !(this->m_Name == p.m_Name && this->m_Age == p.m_Age);
	}


	string m_Name;
	int m_Age;
};

void test01()
{
	//int a = 10;
	//int b = 20;
	//if (a == b)
	//{
	//	cout << "a == b " << endl;
	//}
	//else
	//{
	//	cout << "a != b " << endl;
	//}

	Person p1("Tom", 18);

	Person p2("Tom", 19);

	if (p1 == p2)
	{
		cout << "p1 == p2 " << endl;
	}	
	else
	{
		cout << "a != b " << endl;
	}


	if (p1 != p2)
	{
		cout << "a != b " << endl;
	}
	else
	{
		cout << "p1 == p2 " << endl;
	}

}

```

# 函数调用运算符的重载、仿函数()

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class MyPrint
{
public:
	void operator()(string text)
	{
		cout << text << endl;
	}
};


void MyPrint2(string str)
{
	cout << str << endl;
}

void test01()
{
	MyPrint myPrint;
	myPrint("hello world"); // 仿函数  本质是一个对象   函数对象

	MyPrint2("hello world"); //普通函数
}



class MyAdd
{
public:
	int operator()(int a,int b)
	{
		return a + b;
	}
};

void test02()
{
	MyAdd myAdd;
	cout << myAdd(1, 1) << endl;


	cout << MyAdd()(1, 1) << endl; // 匿名函数对象 特点：当前行执行完立即释放
}
```

# 运算符重载总结

>=, [], () 和 -> 操作符只能通过成员函数进行重载 
><< 和 >>只能通过全局函数配合友元函数进行重载 
>不要重载 && 和 || 操作符，因为无法实现短路规则

**常规建议**

| 运算符                       | 建议使用   |
| ---------------------------- | ---------- |
| 所有的一元运算符             | 成员       |
| = () [] ->-> *               | 必须是成员 |
| += -= /= *= &= != %= >>= <<= | 成员       |
| 其他二元运算符               | 非成员     |



# 字符串封装

**myString.h**

```c++
#pragma  once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyString
{
	//左移运算符友元
	friend ostream& operator<<(ostream & cout, MyString & str);
	//右移运算符 友元
	friend istream&  operator>>(istream & cin, MyString & str);
public:

	//有参构造
	MyString(char  * str);
	//拷贝构造
	MyString(const MyString & str);

	//重载=运算符 

	MyString& operator=(const char * str);
	MyString& operator=(const MyString & str);

	//重载[]运算符
	char& operator[](int index);

	//重载+运算符
	MyString operator+(const char * str);
	MyString operator+(const MyString&str);

	//重载==运算符 
	bool operator==(const char *str);
	bool operator==(const MyString &str);

	//析构
	~MyString();

private:

	char * pString; //维护在堆区开辟的字符数组

	int m_Size; //字符串长度 不统计\0

};
```

**myString.cpp**

```c++
#include "myString.h"

//重载左移运算符
ostream& operator<<(ostream & cout , MyString & str)
{
	cout << str.pString;
	return cout;
}

//重载右移运算符
istream&  operator>>(istream & cin, MyString & str)
{
	//先清空原来堆区数据
	if (str.pString)
	{
		delete[] str.pString;
		str.pString = NULL;
	}

	char buf[1024];//开辟临时数组 记录用户输入内容
	cin >> buf;

	str.pString = new char[strlen(buf) + 1];
	strcpy(str.pString, buf);
	str.m_Size = strlen(buf);

	return cin;
}

MyString::MyString(char * str)
{
	//cout << "MyString有参构造函数调用" << endl;
	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);
	this->m_Size = strlen(str);
}

MyString::MyString(const MyString & str)
{
	//cout << "拷贝构造函数调用" << endl;
	this->pString =  new char[strlen(str.pString)+1];
	strcpy(this->pString, str.pString);
	this->m_Size = str.m_Size;
}

MyString& MyString::operator=(const char * str)
{
	//先判断原来堆区释放有内容，如果有先释放
	if (this->pString != NULL)
	{
		delete[]this->pString;
		this->pString = NULL;
	}

	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);
	this->m_Size = strlen(str);
	return *this;
}

MyString& MyString::operator=(const MyString & str)
{
	if (this->pString != NULL)
	{
		delete[]this->pString;
		this->pString = NULL;
	}

	this->pString = new char[strlen(str.pString) + 1];
	strcpy(this->pString, str.pString);
	this->m_Size = strlen(str.pString);
	return *this;
}

char& MyString::operator[](int index)
{
	return this->pString[index];
}

MyString MyString::operator+(const char * str)
{
	//本身 abc   传入 def
	//计算开辟内存大小
	int newSize = this->m_Size + strlen(str) + 1;

	char * temp = new char[newSize];
	memset(temp, 0, newSize);

	strcat(temp, this->pString);
	strcat(temp, str);

	MyString newString = temp;

	delete[] temp;

	return newString;
}

MyString MyString::operator+(const MyString&str)
{
	int newSize = this->m_Size + strlen(str.pString) + 1;

	char * temp = new char[newSize];
	memset(temp, 0, newSize);

	strcat(temp, this->pString);
	strcat(temp, str.pString);

	MyString newString = temp;

	delete[] temp;

	return newString;
}

bool MyString::operator==(const char *str)
{
	if ( strcmp( this->pString , str) == 0 )
	{
		return true;
	}
	return false;
}

bool MyString::operator==(const MyString &str)
{
	if (strcmp(this->pString, str.pString) == 0)
	{
		return true;
	}
	return false;
}

MyString::~MyString()
{
	if (this->pString != NULL)
	{
		//cout << "析构调用" << endl;
		delete[] this->pString;
		this->pString = NULL;
	}

}
```

**main.cpp**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//#include <string>
#include "myString.h"


void test01()
{
	MyString str = "abc";

	cout << str << endl;

	cout << "请重新给str赋值：" << endl;

	cin >> str;

	cout << "str 新的值为： " << str << endl;


	MyString str2 = str;

	cout << "str2 = " << str2 << endl;

}

void test02()
{
	MyString str = "abcd";

	MyString str2 = "aaa";

	str2 = str;

	cout << "str2 = " << str2 << endl;

	cout << "str2[0] = " << str2[0] << endl;

	str2[0] = 'z';

	cout << "str2[0]改为z后输出：  " << str2 << endl;


	MyString str3 = "abc";
	MyString str4 = "def";
	MyString str5 = str3 + str4;
	MyString str6 = str5 + "ghe";
	cout << "str5 = " << str5 << endl;
	cout << "str6 = " << str6 << endl;


	if (str5 == str6)
	{
		cout << "str5 == str6" << endl;
	}
	else
	{
		cout << "str5 != str6" << endl;
	}

	if ( str6 == "abcdefghe")
	{
		cout << "str6 = abcdefghe" << endl;
	}
	else
	{
		cout << "str6 != abcdefghe" << endl;
	}
}
```

# 继承的基本语法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//class News
//{
//public:
//
//	void header()
//	{
//		cout << "公共的头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共的底部" << endl;
//	}
//	void leftList()
//	{
//		cout << "公共的左侧列表" << endl;
//	}
//
//	void content()
//	{
//		cout << "新闻播报..." << endl;
//	}
//};
//
//
//class Sport
//{
//public:
//
//	void header()
//	{
//		cout << "公共的头部" << endl;
//	}
//	void footer()
//	{
//		cout << "公共的底部" << endl;
//	}
//	void leftList()
//	{
//		cout << "公共的左侧列表" << endl;
//	}
//
//	void content()
//	{
//		cout << "世界杯赛况..." << endl;
//	}
//};


//利用继承模拟网页
//继承优点： 减少重复的代码，提高代码复用性
class BasePage
{
public:
	void header()
	{
		cout << "公共的头部" << endl;
	}
	void footer()
	{
		cout << "公共的底部" << endl;
	}
	void leftList()
	{
		cout << "公共的左侧列表" << endl;
	}
};
// 语法： class 子类 ： 继承方式   父类
// News		子类    派生类
// BasePage 父类    基类
class News : public BasePage
{
public:
	void content()
	{
		cout << "新闻播报..." << endl;
	}
};

class Sport :public BasePage
{
public:
	void content()
	{
		cout << "世界杯..." << endl;
	}

};


void test01()
{
	News news;
	cout << "新闻页面内容如下：" << endl;
	news.header();
	news.footer();
	news.leftList();
	news.content();


	Sport sp;
	cout << "体育页面内容如下：" << endl;
	sp.header();
	sp.footer();
	sp.leftList();
	sp.content();

}
```

# 继承的方式:public private protected

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/////////////////   公共继承  ////////////////
class Base1
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1 :public Base1
{
public:

	void func()
	{
		m_A = 100; //父类中 公共权限 子类中变为  公共权限
		m_B = 100; //父类中 保护权限 子类中变为  保护权限
		//m_C = 100;// 父类中私有成员，子类无法访问
	}
};

void test01()
{
	Son1 s1;
	s1.m_A = 100; //在Son1中 m_A是公共权限  类外可以访问
	//s1.m_B = 100; //在Son1中 m_B是保护权限  类外不可以访问
}


/////////////////   保护继承  ////////////////
class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son2 : protected Base2
{
public:
	void func()
	{
		m_A = 100;//父类中 公共权限 子类中变为  保护权限
		m_B = 100;//父类中 保护权限 子类中变为  保护权限
		//m_C = 100;//父类中私有成员，子类无法访问
	}
};

void test01()
{
	Son2 s;
	//s.m_A = 100;  //子类中 保护权限 无法访问
	//s.m_B = 100;  //子类中 保护权限 无法访问
	//s.m_C = 100; //子类本身没有访问权限
}


/////////////////   私有继承  ////////////////
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3 :private Base3
{
public:
	void func()
	{
		m_A = 100;  //父类中 公共权限 子类中变为  私有权限
		m_B = 100;  //父类中 保护权限 子类中变为  私有权限
		//m_C = 100;//父类中私有成员，子类无法访问
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//m_A = 100;//在Son3中 已经变为私有权限，GrandSon3访问不到
		//m_B = 100;
	}
};
void test03()
{
	Son3 s;
	//s.m_A = 100;//在Son3中变为私有权限，类外访问不到
	//s.m_B = 100;//在Son3中变为私有权限，类外访问不到

}

```

# 继承中的对象模型

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;  //父类中私有属性，子类访问不到，是由编译器给隐藏了
};

class Son : public Base
{
public:
	int m_D;
};


void test01()
{
	//4  8    12   16
	cout << "size of  Son = " << sizeof(Son) << endl; // 结果为16

}

```

# 继承中的构造和析构

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base1
{
public:
	Base1()
	{
		cout << "Base1的构造函数调用" << endl;

	}

	~Base1()
	{
		cout << "Base1的析构函数调用" << endl;
	}

};


class Other
{
public:
	Other()
	{
		cout << "Other的构造函数调用" << endl;
	}

	~Other()
	{
		cout << "Other的析构函数调用" << endl;
	}
};

class Son1 :public Base1
{
public:
	Son1()
	{
		cout << "Son1的构造函数调用" << endl;
	}

	~Son1()
	{
		cout << "Son1的析构函数调用" << endl;
	}

	Other other;
};



void test01()
{
	Son1 s; //先调用父类构造，再调用其他成员构造， 再调用自身构造 ，析构的顺序与构造相反

}



class Base2
{
public:
	Base2(int a)
	{
		this->m_A = a;
		cout << "Base2的构造函数调用" << endl;
	}
	int m_A;
};
class Son2 :public Base2
{
public:
	Son2(int a = 1000 ) :Base2(a)  //利用初始化列表语法  显示调用父类中的其他构造函数
	{
		cout << "Son2的构造函数调用" << endl;
	}
};
void test02()
{
	Son2 s;
	cout << s.m_A << endl;
}


//父类中 构造、析构、拷贝构造 、operator=  是不会被子类继承下去的
```

# 继承中同名成员的处理

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		this->m_A = 10;
	}

	void func()
	{
		cout << "Base中的func调用" << endl;
	}

	void func(int a)
	{
		cout << "Base中的func(int)调用" << endl;
	}

	int m_A;
};

class Son :public Base
{
public:

	Son()
	{
		this->m_A = 20;
	}

	void func()
	{
		cout << "Son中的func调用" << endl;
	}

	int m_A;
};




void test01()
{
	Son s1;

	cout << "s1.m_A = " <<  s1.m_A << endl;

	//我们可以利用作用域 访问父类中的同名成员
	cout << "Base中的m_A = " << s1.Base::m_A << endl;
}

void test02()
{
	Son s1;
	s1.func();
	s1.Base::func(10);

	//当子类重新定义了父类中的同名成员函数，子类的成员函数会 隐藏掉父类中所有重载版本的同名成员，可以利用作用域显示指定调用

}

```

# 继承中同名静态成员处理

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:

	static void func()
	{
		cout << "Base中的func调用 " << endl;
	}

	static void func(int a)
	{
		cout << "Base中的func(int a)调用 " << endl;
	}

	static int m_A;

};

int Base::m_A = 10;


class Son :public Base
{
public:

	static void func()
	{
		cout << "Son中的func调用 " << endl;
	}

	static int m_A;
};
int Son::m_A = 20;

void test01()
{
	//1、通过对象访问
	Son s;
	cout << "m_A = " << s.m_A << endl;
	cout << "Base中的m_A = " << s.Base::m_A << endl;

	//2、通过类名访问

	cout << "m_A = " << Son::m_A << endl;
	//通过类名的方式 访问 父类作用域下的m_A静态成员变量
	cout << "Base中的m_A = " <<  Son::Base::m_A << endl;
}


void test02()
{
	//1、通过对象
	Son s;
	s.func();
	s.Base::func();


	//2、通过类名
	Son::func();
	//当子类重定义父类中同名成员函数，子类的成员函数会隐藏掉父类中所有版本，需要加作用域调用
	Son::Base::func(1);
}


```

# 多继承的基本语法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base1
{
public:
	Base1()
	{
		this->m_A = 10;
	}
	int m_A;
};

class Base2
{
public:
	Base2()
	{
		this->m_A = 20;
	}
	int m_A;
};

//多继承
class Son : public Base1, public Base2
{
public:

	int m_C;
	int m_D;
};

void test01()
{
	cout << "sizeof Son = " << sizeof(Son) << endl;

	Son s;
	//当多继承的两个父类中有同名成员，需要加作用域区分
	cout << s.Base1::m_A << endl;
	cout << s.Base2::m_A << endl;
}

```

# 菱形继承问题及解决

**虚继承解决菱形继承问题**

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//动物类
class Animal
{
public:
	int m_Age; // 年龄
};

//Animal称为 虚基类

//羊类
class Sheep : virtual public Animal{};
//驼类
class Tuo : virtual public Animal{};

//羊驼
class SheepTuo : public Sheep, public Tuo
{
};


void test01()
{
	SheepTuo st;

	st.Sheep::m_Age = 10;
	st.Tuo::m_Age = 20;

	cout << "Sheep::m_Age = " << st.Sheep::m_Age << endl;
	cout << "Tuo::m_Age = " << st.Tuo::m_Age << endl;
	cout << "age = " << st.m_Age << endl;

	//当发生虚继承后，sheep和tuo类中 继承了一个  vbptr指针   虚基类指针   指向的是一个 虚基类表  vbtable
	//虚基类表中记录了  偏移量 ，通过偏移量 可以找到唯一的一个m_Age
}


void test02()
{
	SheepTuo st;
	st.m_Age = 10;

	//通过Sheep找到 偏移量
	//*(int *)&st 解引用到了 虚基类表中
	cout << *((int *)*(int *)&st + 1) << endl;

	//通过Tuo 找到偏移量
	cout << *((int *)*((int *)&st + 1) + 1) << endl;

	//通过偏移量  访问m_Age

	cout << "m_Age = " << ((Animal *)((char *)&st + *((int *)*(int *)&st + 1)))->m_Age << endl;

	cout << "m_Age = " << *((int *)((char *)&st + *((int *)*(int *)&st + 1))) << endl;
}
```

## 虚继承实现原理

```c++
class BigBase{
public:
	BigBase(){ mParam = 0; }
	void func(){ cout << "BigBase::func" << endl; }
public: int mParam;
};
#if 0 //虚继承
class Base1 : virtual public BigBase{};
class Base2 : virtual public BigBase{};
#else //普通继承
class Base1 :  public BigBase{};
class Base2 :  public BigBase{};
#endif
class Derived : public Base1, public Base2{};
```

>BigBase 菱形最顶层的类，内存布局图没有发生改变。
>
>Base1和Base2通过虚继承的方式派生自BigBase,这两个对象的布局图中可以看出编译器为我们的对象中增加了一个vbptr (virtual base pointer),vbptr指向了一张表，这张表保存了当前的虚指针相对于虚基类的首地址的偏移量。
>
>Derived派生于Base1和Base2,继承了两个基类的vbptr指针，并调整了vbptr与虚基类的首地址的偏移量。

由此可知编译器帮我们做了一些幕后工作，使得这种菱形问题在继承时候能只继承一份数据，并且也解决了二义性的问题。现在模型就变成了Base1和 Base2 Derived三个类对象共享了一份BigBase数据。

当使用虚继承时，虚基类是被共享的，也就是在继承体系中无论被继承多少次，对象内存模型中均只会出现一个虚基类的子对象（这和多继承是完全不同的）。即使共享虚基类，但是必须要有一个类来完成基类的初始化（因为所有的对象都必须被初始化，哪怕是默认的），同时还不能够重复进行初始化，那到底谁应该负责完成初始化呢？C++标准中选择在***\*每一次继承子类\****中都必须书写初始化语句（因为每一次继承子类可能都会用来定义对象），但是虚基类的初始化是由最后的子类完成，其他的初始化语句都不会调用。

```c++
class BigBase{
public:
	BigBase(int x){mParam = x;}
	void func(){cout << "BigBase::func" << endl;}
public:
	int mParam;
};
class Base1 : virtual public BigBase{
public:
	Base1() :BigBase(10){} //不调用BigBase构造
};
class Base2 : virtual public BigBase{
public:
	Base2() :BigBase(10){} //不调用BigBase构造
};

class Derived : public Base1, public Base2{
public:
	Derived() :BigBase(10){} //调用BigBase构造
};
//每一次继承子类中都必须书写初始化语句
int main(){
	Derived derived;
	return EXIT_SUCCESS;
}
```

==虚继承只能解决具备公共祖先的多继承所带来的二义性问题，不能解决没有公共祖先的多继承的.==

==工程开发中真正意义上的多继承是几乎不被使用，因为多重继承带来的代码复杂性远多于其带来的便利，多重继承对代码维护性上的影响是灾难性的，在设计方法上，任何多继承都可以用单继承代替。==