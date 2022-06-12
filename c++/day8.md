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

