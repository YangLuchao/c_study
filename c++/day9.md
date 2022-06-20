[toc]

# 类型转换

>-   1 类型转换
>    -   1.1 静态类型转换  static_cast
>        -   1.1.1 允许内置数据类型转换
>        -   1.1.2 允许父子之间的指针或者引用的转换
>        -   1.1.3 语法 static_cast<目标类型>(原变量/原对象)
>    -   1.2 动态类型转换  dynamic_cast
>        -   1.2.1 不允许内置数据类型转换 
>        -   1.2.2 允许父子之间指针或者引用的转换
>            -   1.2.2.1 父转子  不安全的  转换失败
>            -   1.2.2.2 子转父  安全  转换成功
>            -   1.2.2.3 如果发生多态，总是安全，可以成功
>        -   1.2.3 语法 dynamic_cast<目标类型>(原变量/原对象)
>    -   1.3 常量转换  const_cast
>        -   1.3.1 只允许 指针或者引用 之间转换
>        -   1.3.2 语法 const	_cast<目标类型>(原变量/原对象)
>    -   1.4 重新解释转换
>        -   1.4.1 reinterpret_cast 最不安全一种转换，不建议使用
>
>

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、静态类型转换  static_cast
void test01()
{
	//允许内置数据类型之间转换
	char a = 'a';

	double d = static_cast<double>(a);

	cout << d << endl;

}

class Base{ virtual void func(){} };
class Son :public Base{ virtual void func(){} };
class Other{};

void test02()
{
	Base * base = NULL;
	Son * son = NULL;

	//语法：   static_cast<目标类型>(原对象)
	//父子之间的指针或者引用可以转换
	//将base 转为 Son *   父转子  向下类型转换  不安全
	Son * son2 = static_cast<Son *> (base);

	//son  转为 Base*    子转父  向上类型转换  安全
	Base * base2 = static_cast<Base*>(son);


	//base 转为Other*
	//Other * other = static_cast<Other*>(base);  转换无效

}


//动态类型转换  dynamic_cast
void test03()
{
	//不允许内置数据类型之间转换
	//char c = 'c';
	//double d = dynamic_cast<double>(c);
}

void test04()
{
	Base * base = new Son;
	Son * son = NULL;

	//将base 转为 Son *  父转子 不安全  如果发生了多态，那么转换总是安全的
	Son * son2 = dynamic_cast<Son*>(base);


	//son 转为 Base*  子转父  安全
	Base * base2 = dynamic_cast<Base*>(son);

	//base 转 Other*
	//Other* other = dynamic_cast<Other*>(base); //无法转换
}

//常量转换  const_cast
void test05()
{
	//不可以将非指针或非引用做const_cast转换
	const int * p = NULL;
	int * pp = const_cast<int*>(p);

	const int * ppp =  const_cast<const int *>(pp);


	//const int a = 10;
	//int b = const_cast<int>(a);


	int num = 10;
	int &numRef = num;

    const int& num2 = const_cast<const int&>(numRef);

}

//重新解释转换  reinterpret_cast 最不安全一种转换，不建议使用
void test06()
{
	int a = 10;
	int * p = reinterpret_cast<int*>(a);

	Base * base = NULL;
	//base 转 Other *
	Other * other = reinterpret_cast<Other *>(base);
}
```

# 异常的基本语法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class MyException
{
public:
	void printError()
	{
		cout << "我自己的异常" << endl;
	}
};

class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数调用" << endl;
	}
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}
};

int myDivision(int a , int b)
{
	if ( b == 0)
	{
		//return -1;
		//throw 1; //抛出int类型的异常
		//throw 'a'; //抛出char类型的异常
		//throw 3.14; //抛出double类型的异常
		/*string str = "abc";
		throw str;*/


		//从try代码块开始，到throw抛出异常之前，所有栈上的数据都会被释放掉，
		//释放的顺序和创建顺序相反的，这个过程我们称为栈解旋
		Person p1;
		Person p2;


		throw MyException(); //抛出 MyException的匿名对象
	}

	return a / b;
}

void test01()
{
	int a = 10;
	int b = 0;

	//C语言处理异常 有缺陷：返回值不统一，返回值只有一个，无法区分是结果还是异常
	//int ret =myDivision(a, b);
	//if ( ret == -1)
	//{
	//	cout << "异常" << endl;
	//}

	try
	{
		myDivision(a, b);
	}
	catch (int)
	{
		cout << "int类型异常捕获" << endl;
	}
	catch (char)
	{
		cout << "char类型异常捕获" << endl;
	}
	catch (double)
	{
		//捕获到了异常，但是不想处理，继续向上抛出这个异常
		//异常必须有函数进行处理，如果没有任何处理，程序自动调用 terminate 函数，让程序中断
		throw;
		cout << "double类型异常捕获" << endl;
	}
	catch (MyException e)
	{
		e.printError();
	}
	catch (...)
	{
		cout << "其他类型异常捕获" << endl;
	}
	
}

int main(){

	try
	{
		test01();
	}
	catch (double)
	{
		cout << "double函数中 double类型异常捕获" << endl;
	}
	catch (...)
	{
		cout << "main函数中 其他类型异常捕获" << endl;
	}

	


	system("pause");
	return EXIT_SUCCESS;
}
```

# 栈解旋

==异常被抛出后，从进入try块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构。析构的顺序与构造的顺序相反，这一过程称为栈的解旋(unwinding).==

# 异常的接口声明

```c++
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

//异常接口声明   throw(空)代表 不允许抛出异常
void func()throw(int ,double)
{

    throw 3.14;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    try
    {
        func();
    }
    catch(int)
    {
        qDebug() << "int 类型的异常捕获"<<endl;
    }
    catch(...)
    {
         qDebug() << "其他 类型的异常捕获"<<endl;
    }

    return a.exec();
}
```

# 异常变量的生命周期

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
	MyException()
	{
		cout << "MyException默认构造函数调用" << endl;
	}

	MyException(const MyException & e)
	{
		cout << "MyException拷贝构造函数调用" << endl;
	}

	~MyException()
	{
		cout << "MyException析构函数调用" << endl;
	}

};

void doWork()
{
	throw  new MyException();
}

void test01()
{
	try
	{
		doWork();
	}
	//抛出的是 throw MyException();  catch (MyException e) 调用拷贝构造函数 效率低
	//抛出的是 throw MyException();  catch (MyException &e)  只调用默认构造函数 效率高 推荐
	//抛出的是 throw &MyException(); catch (MyException *e) 对象会提前释放掉，不能在非法操作
	//抛出的是 new MyException();   catch (MyException *e) 只调用默认构造函数 自己要管理释放
	catch (MyException *e)
	{
		cout << "自定义异常捕获" << endl;
		delete e;
	}

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}
```

# 异常的多态使用

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//异常的基类
class BaseException
{
public:
	virtual void printError() = 0;
};

//空指针异常
class NULLPointerException :public BaseException
{
public:
	virtual void printError()
	{
		cout << "空指针异常" << endl;
	}
};

//越界异常
class OutOfRangeException :public BaseException
{
public:
	virtual void printError()
	{
		cout << "越界异常" << endl;
	}

};

void doWork()
{
	//throw NULLPointerException();
	throw OutOfRangeException();
}

void test01()
{
	try
	{
		doWork();
	}
	catch (BaseException & e)
	{
		e.printError();
	}
}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 系统的标准异常

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <stdexcept> //  std 标准  except 异常


class Person
{
public:
	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			throw out_of_range("年龄必须在 0 ~ 150之间");
			//throw length_error("年龄必须在 0 ~ 150之间");
		}
		else
		{
			this->m_Age = age;
		}
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p(151);
	}
	//catch ( out_of_range &e)
	catch ( exception &e)
	{
		cout << e.what() << endl;
	}

}

int main(){
	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 编写自定义异常类

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyOutOfRangeException:public exception
{
public:

	MyOutOfRangeException( const char * str)
	{
		//const char * 可以隐式类型转换为 string  反之不可以
		this->m_errorInfo = str;
	}

	MyOutOfRangeException(string str)
	{
		this->m_errorInfo = str;
	}

	virtual const char *  what() const
	{
		//将string 转为 const char * 
		return m_errorInfo.c_str();
	}

	string m_errorInfo;
};

class Person
{
public:
	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			throw MyOutOfRangeException( string( "年龄必须在0到150之间"));
		}
		else
		{
			this->m_Age = age;
		}
	}

	int m_Age;
};


void test01()
{
	try
	{
		Person p(1000);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 标准输入流

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
cin.get() //一次只能读取一个字符
cin.get(一个参数) //读一个字符
cin.get(两个参数) //可以读字符串
cin.getline()
cin.ignore()
cin.peek()
cin.putback()
*/
void test01()
{
	//输入  a  s     第一次 a  第二次  s  第三次 换行  第四次 等待下次输入
	char c = cin.get();

	cout << "c = " << c << endl;

	c = cin.get();
	
	cout << "c = " << c << endl;

	c = cin.get();

	cout << "c = " << c << endl;


	c = cin.get();

	cout << "c = " << c << endl;
}


void test02()
{
	char buf[1024] = { 0 };
	cin.get(buf, 1024);

	char c = cin.get();
	//利用cin.get获取字符串时候，换行符遗留在缓冲区中
	if (  c== '\n')
	{
		cout << "换行符遗留在缓冲区" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区" << endl;
	}
	cout << buf << endl;

}

void test03()
{
	char buf[1024] = { 0 };

	//利用cin.getline获取字符串时候，换行符不会被取走，也不在缓冲区中，而是直接扔掉
	cin.getline(buf, 1024);

	char c = cin.get();
	if (c == '\n')
	{
		cout << "换行符遗留在缓冲区" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区" << endl;
	}
	cout << buf << endl;

}

//cin.ignore() 忽略 默认忽略1个字符， 如果填入参数X，代表忽略X个字符
void test04()
{
	cin.ignore(2);
	char c = cin.get();
	cout << "c = " << c << endl;
}

//cin.peek() 偷窥
void test05()
{
	char c = cin.peek();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

}

//cin.putback() 放回
void test06()
{
	char c = cin.get();
	cin.putback(c);

	char buf[1024] = { 0 };

	cin.getline(buf, 1024);
	cout << buf << endl;
}


//案例1、 判断用户输入的内容 是字符串还是数字  12345     abcde
void test07()
{
	cout << "请输入一个字符串或者数字" << endl;
	char c = cin.peek();

	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "您输入的是数字 为：" << num << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;
		cout << "您输入的是字符串 ：" << buf << endl;
	}
}

//案例2、 用户输入 0 ~ 10 之间的数字，如果输入有误，重新输入
void test08()
{
	cout << "请输入 0 ~ 10 之间的数字" << endl;

	int num;

	while (true)
	{
		cin >> num;

		if (num >= 0 && num <= 10)
		{
			cout << "输入正确，输入值为：" << num << endl;
			break;
		}
		
		//清空缓冲区 重置标志位 
		cin.clear();
		cin.sync();
		//cin.ignore();//vs2013以上版本加入 
		//如果标志位为 0  代表缓冲区正常    如果标志位为1   缓冲区异常
		//cout << " cin.fail()  = " << cin.fail() << endl;
		
		cout << "输入有误，请重新输入： " << endl;
	}

}

```

标准输出流

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <iomanip> //控制符格式化输出  头文件

/*
cout.put() //向缓冲区写字符
cout.write() //从buffer中写num个字节到当前输出流中。
*/
void test01()
{
	//cout.put('h').put('e');

	char buf[] = "hello world";
	cout.write(buf, strlen(buf));

	cout << "hello world" << endl;

}

//1、通过 流成员函数 格式化输出
void test02()
{
	int number = 99;
	cout.width(20); //指定宽度为20
	cout.fill('*'); //填充
	cout.setf(ios::left);  //左对齐
	cout.unsetf(ios::dec); //卸载十进制
	cout.setf(ios::hex);  //安装十六进制
	cout.setf(ios::showbase);  //显示基数
	cout.unsetf(ios::hex);  //卸载十六进制
	cout.setf(ios::oct);   //安装八进制
	cout << number << endl;
}

//2、使用控制符 格式化输出
void test03()
{
	int number = 99;
	cout << setw(20)     //设置宽度
		<< setfill('~')  //设置填充
		<< setiosflags(ios::showbase)  //显示基数
		<< setiosflags(ios::left)  //设置左对齐
		<< hex   //显示十六进制
		<< number
		<< endl;


}

int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 文件读写

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <fstream> //文件流
#include <string>

void test01()
{
	//写文件  o --  输出    
	ofstream  ofs("./test.txt", ios::out | ios::trunc);

	//ofs.open("./test.txt", ios::out | ios::trunc);  设置打开方式 以及路径

	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	ofs << "姓名：孙悟空" << endl;
	ofs << "年龄：999" << endl;
	ofs << "性别：男" << endl;

	//关闭文件
	ofs.close();

}


void test02()
{
	//读文件   i  -- 输入
	ifstream  ifs;
	ifs.open("./test.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };

	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}


	//第二种方式
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

	//第三种方式
	//string buf;
	//while ( getline(ifs,buf) )
	//{
	//	cout << buf << endl;
	//}


	//第四种方式
	char  c;
	while ( (c = ifs.get()) != EOF )
	{
		cout << c;
	}

	ifs.close();
}

int main(){

	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}
```

