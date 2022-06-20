[toc]

# STL初识

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm> //标准算法头文件
#include <string>

//原生指针也是迭代器
void test01()
{
	int arr[5] = { 1, 2, 3, 4, 5 };

	int * p = arr;

	for (int i = 0; i < 5;i++)
	{
		//cout << arr[i] << endl;
		cout << *(p++) << endl;
	}
}

void myPrint(int val)
{
	cout << val << endl;
}

void test02()
{
	vector<int>v; //创建一个vector容器，容器中存放元素类型是int类型
	
	//插入元素
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);

	//遍历元素
	vector<int>::iterator  itBegin = v.begin(); //v.begin() 起始迭代器，指向容器中第一个数据

	vector<int>::iterator  itEnd = v.end(); //v.end()；结束迭代器，指向的是容器中最后一个元素的下一个位置


	//第一种遍历
	//while (itBegin!=itEnd)
	//{
	//	cout << *itBegin << endl;
	//	itBegin++;
	//}



	//第二种遍历
	//for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	cout << *it << endl;
	//}

	//第三种遍历
	for_each(v.begin(), v.end(), myPrint);

}


//自定义数据类型
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


void test03()
{
	vector<Person> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	Person p5("eee", 50);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//每个容器都有自己专属的迭代器
	for (vector<Person>::iterator it = v.begin(); it != v.end();it++)
	{
		// *it  ===  Person
		cout << "姓名： " << (*it).m_Name << " 年龄： " << it->m_Age << endl;
	}
}



//存放自定义数据类型指针
void test04()
{
	vector<Person *> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	Person p5("eee", 50);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);
	v.push_back(&p5);

	for (vector<Person *>::iterator it = v.begin(); it != v.end();it++)
	{
		// *it  ---- Person *
		cout << "姓名： " << (*it)->m_Name << " 年龄： " << (*it)->m_Age << endl;
	}

}


//容器嵌套容器
void test05()
{
	vector<vector<int>>v;

	vector<int>v1;
	vector<int>v2;
	vector<int>v3;

	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i + 1);
		v2.push_back(i + 10);
		v3.push_back(i + 100);
	}

	//将小容器放入到大容器中
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);


	//遍历大容器
	for (vector<vector<int>>::iterator it = v.begin(); it != v.end();it++)
	{
		// *it ==== vector<int>
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end();vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}

}

int main(){

	//test01();
	//test02();
	//test03();
	//test04();
	test05();


	system("pause");
	return EXIT_SUCCESS;
}
```

# String容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
#include <vector>
/*
3.1.2.1 string 构造函数
string();//创建一个空的字符串 例如: string str;
string(const string& str);//使用一个string对象初始化另一个string对象
string(const char* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化

3.1.2.2 string基本赋值操作
string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string& operator=(const string &s);//把字符串s赋给当前的字符串
string& operator=(char c);//字符赋值给当前的字符串
string& assign(const char *s);//把字符串s赋给当前的字符串
string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
*/

void test01()
{
	string str;
	string str2(str);

	string str3 = "abc";

	string str4(10, 'a');

	cout << "str3 = " << str3 << endl;

	cout << "str4 = " << str4 << endl;

}
//赋值
void test02()
{
	string  str;
	str = "abc";

	str.assign("abcde", 3);

	cout << str << endl;


	string str2;
	str2.assign(str);
	cout << str2 << endl;

	//string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串

	str2.assign(str, 0, 2);
	cout << str2 << endl;

}

/*
3.1.2.3 string存取字符操作
char& operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符
*/

void test03()
{
	string str = "hello world";

	//for (int i = 0; i < str.size();i++)
	//{
	//	//cout << str[i] << endl;
	//	cout << str.at(i) << endl;
	//}

	//[]和at区别，[]访问越界 直接挂掉 ， at访问越界  抛出out_of_range异常

	try
	{
		//cout << str[100] << endl;
		cout << str.at(100) << endl;
	}
	catch (out_of_range & e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "异常捕获" << endl;
	}

}


/*
3.1.2.4 string拼接操作
string& operator+=(const string& str);//重载+=操作符
string& operator+=(const char* str);//重载+=操作符
string& operator+=(const char c);//重载+=操作符
string& append(const char *s);//把字符串s连接到当前字符串结尾
string& append(const char *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
string& append(const string &s);//同operator+=()
string& append(const string &s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c);//在当前字符串结尾添加n个字符c

3.1.2.5 string查找和替换
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
*/

void test04()
{
	//拼接
	//string str1 = "我";
	//string str2 = "爱北京";

	//str1 += str2;
	//cout << str1 << endl;

	//str1.append("天安门");
	//cout << str1 << endl;

	//查找
	string str = "abcdefgde";

	int pos =  str.find("de");
	//rfind 是从右往左查找
	if (pos == -1)
	{
		cout << "未找到字符串" << endl;
	}
	else
	{
		cout << "找到了字符串，位置为： " << pos << endl;
	}
	
	//替换
	//string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
	str.replace(1, 3, "11111");
	//a11111efgde
	cout << str << endl;
}


/*
3.1.2.6 string比较操作
compare函数在>时返回 1，<时返回 -1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。

int compare(const string &s) const;//与字符串s比较
int compare(const char *s) const;//与字符串s比较
3.1.2.7 string子串
string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串

*/

void test05()
{
	string str1 = "abcde";
	string str2 = "abcdef";

	if (str1.compare(str2) == 0)
	{
		cout << "str1 == str2" << endl;
	}
	else if (str1.compare(str2) > 0)
	{
		cout << "str1 > str2" << endl;
	}
	else
	{
		cout << "str1 < str2" << endl;
	}
}

void test06()
{
	//子串
	//string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串

	//string str = "abcdef";

 //   string subStr =	str.substr(0, 3);

	//cout << subStr << endl;


	string email = "zhangtao@sina.com";

	int pos = email.find("@"); // 8

	string userName = email.substr(0, pos);

	cout << userName << endl;
 
}

//解析字符串
void test07()
{
	string str = "www.itcast.com.cn";

	vector<string> v; //将 www  itcast  com  cn 单词截取到 vector容器中

	int start = 0;
	int pos = -1;

	while (true)
	{
		//www.itcast.com.cn
		pos = str.find(".", start);

		if (pos == -1)
		{
			//将cn截取出来
			string tempStr = str.substr(start,str.size() - start);
			v.push_back(tempStr);
			break;
		}

		string tempStr = str.substr(start, pos - start);

		v.push_back(tempStr);

		start = pos + 1;
	}

	for (vector<string>::iterator it = v.begin(); it != v.end();it++)
	{
		cout << *it << endl;
	}


}
/*
3.1.2.8 string插入和删除操作
string& insert(int pos, const char* s); //插入字符串
string& insert(int pos, const string& str); //插入字符串
string& insert(int pos, int n, char c);//在指定位置插入n个字符c
string& erase(int pos, int n = npos);//删除从Pos开始的n个字符
*/
void test08()
{

	string str = "hello";

	str.insert(1, "111");

	//h111ello 
	cout << str << endl;

	//删除 
	str.erase(1, 3);

	cout << str << endl;
}

void doWork(string str)
{

}

void doWork2(const char* str)
{

}

//3.1.2.9 string和c-style字符串转换
void test09()
{
	const char * str = "abcd";

	//const char * 转为 string
	string s(str);

	//string 转为 const char *
	const char * str2 = s.c_str();

	//const char * 可以隐式类型转换为  string
	doWork(str2);
	//string 不可以隐式类型转换为  const char* 
	//doWork2(s);
}


void test10()
{
	string s = "abcdefg";
	char& a = s[2];
	char& b = s[3];

	a = '1';
	b = '2';

	cout << s << endl;
	cout << (int*)s.c_str() << endl;

	s = "pppppppppppppppppppppppp";

	//a = '1';
	//b = '2';

	cout << s << endl;
	cout << (int*)s.c_str() << endl;

}

/*
写一个函数，函数内部将string字符串中的所有小写字母都变为大写字母。
*/
void test11()
{
	string str = "abcdEFg";

	for (int i = 0; i < str.size();i++)
	{
		//str[i] = toupper(str[i]);

		str[i] = tolower(str[i]);

	}

	cout << str << endl;
}


int main(){

	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	//test08();
	//test10();
	test11();

	system("pause");
	return EXIT_SUCCESS;
}
```

# Vector容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <list>

void test01()
{
	vector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
		cout << v.capacity() << endl;  // v.capacity()容器的容量
	}
}

/*
3.2.4.1 vector构造函数
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

3.2.4.2 vector常用赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector& operator=(const vector  &vec);//重载等号操作符
swap(vec);// 将vec与本身的元素互换。
*/

void printVector(vector<int> & v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end();it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test02()
{
	vector<int>v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);

	vector<int>v2(v1.begin(), v1.end());

	printVector(v2);

	vector<int>v3;
	v3.assign(v1.begin(), v1.end());

	printVector(v3);


	vector<int>v4(10, 100);
	printVector(v4);

	cout << "v3和v4互换后：" << endl;
	v3.swap(v4);

	printVector(v3);
	printVector(v4);
}

/*
3.2.4.3 vector大小操作
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的容量
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。
reverse  翻转
3.2.4.4 vector数据存取操作
at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
operator[];//返回索引idx所指的数据，越界时，运行直接报错
front();//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素
*/

void test03()
{

	vector<int>v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);

	if (v1.empty())
	{
		cout << "v1为空" << endl;
	}
	else
	{
		cout << "v1不为空 ，大小为： " << v1.size() << endl;
	}

	v1.resize(10,100); //第二个参数代表默认填充值

	printVector(v1);

	v1.resize(3);

	printVector(v1);

	cout << "v1的front = " << v1.front() << endl;
	cout << "v1的back  = " << v1.back() << endl;

}


/*
3.2.4.5 vector插入和删除操作
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele.
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素
*/

void test04()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	v.insert(v.begin(), 100);

	printVector(v);

	v.push_back(1000);

	printVector(v);

	v.pop_back();

	printVector(v);


	v.erase(v.begin());
	printVector(v);

	//v.erase(v.begin(), v.end()); 等价于  v.clear();
	v.clear();
	//v.erase(v.begin(), v.end());
	printVector(v);

}


//案例1  巧用swap收缩内存
void test05()
{
	vector<int>v;
	for (int i = 0; i < 100000;i++)
	{
		v.push_back(i);
	}
	cout << "v.capacity = " << v.capacity() << endl;
	cout << "v.size = " << v.size() << endl;

	v.resize(3);

	cout << "v.capacity = " << v.capacity() << endl;
	cout << "v.size = " << v.size() << endl;

	//巧用swap收缩内存
	vector<int>(v).swap(v);

	cout << "v.capacity = " << v.capacity() << endl;
	cout << "v.size = " << v.size() << endl;
}

//案例2  巧用 reserve 预留空间
void test06()
{
	
	vector<int>v;
	v.reserve(100000);
	int * p = NULL;
	int num = 0;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
		if (p != &v[0])
		{
			p = &v[0];
			num++;
		}
	}

	cout << "num = " << num << endl;

}

void test07()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	//逆序遍历
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend();it++)
	{
		cout << *it << endl;
	}

	//vector的迭代器是随机访问迭代器，支持跳跃访问

	vector<int>::iterator itBegin = v.begin();
	itBegin = itBegin + 3;


	list<int>L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	list<int>::iterator itBegin2 = L.begin();
	//itBegin2 = itBegin2 + 1;//list容器的迭代器是不支持随机访问的

	cout << *itBegin << endl;


}


int main(){

//	test01();
//	test02();
//	test03();
//	test04();
//	test05();
//	test06();
	test07();

	system("pause");
	return EXIT_SUCCESS;
}
```

# deque容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <deque>
#include <algorithm>
/*
3.3.3.1 deque构造函数
deque<T> deqT;//默认构造形式
deque(beg, end);//构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n, elem);//构造函数将n个elem拷贝给本身。
deque(const deque &deq);//拷贝构造函数。

3.3.3.2 deque赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
deque& operator=(const deque &deq); //重载等号操作符
swap(deq);// 将deq与本身的元素互换

3.3.3.3 deque大小操作
deque.size();//返回容器中元素的个数
deque.empty();//判断容器是否为空
deque.resize(num);//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num, elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除。
*/

void printDeque( const deque<int>&d)
{
	//iterator普通迭代器
	//reverse_iterator 反转迭代器
	//const_iterator  只读迭代器

	for (deque<int>::const_iterator it = d.begin(); it != d.end();it++)
	{
		//*it = 1000;
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int>d;

	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_back(40);


	deque<int>d2;
	d2 = d;

	printDeque(d2);


	if (d2.empty())
	{
		cout << "d2为空" << endl;
	}
	else
	{
		cout << "d2不为空 size = " << d2.size() << endl;
	}
}


/*
3.3.3.4 deque双端插入和删除操作
push_back(elem);//在容器尾部添加一个数据
push_front(elem);//在容器头部插入一个数据
pop_back();//删除容器最后一个数据
pop_front();//删除容器第一个数据

3.3.3.5 deque数据存取
at(idx);//返回索引idx所指的数据，如果idx越界，抛出out_of_range。
operator[];//返回索引idx所指的数据，如果idx越界，不抛出异常，直接出错。
front();//返回第一个数据。
back();//返回最后一个数据
*/

void test02()
{
	deque<int>d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_front(100);
	d.push_front(200);
	d.push_front(300);
	//  300 200 100 10 20 30
	printDeque(d);

	d.pop_back(); //尾删
	d.pop_front(); //头删
	// 200 100 10 20
	printDeque(d);

	cout << "第一个元素为： " << d.front() << endl;
	cout << "最后一个元素为：" << d.back() << endl;
}

/*
3.3.3.6 deque插入操作
insert(pos,elem);//在pos位置插入一个elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
3.3.3.7 deque删除操作
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
*/

void test03()
{
	deque<int>d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_front(100);
	d.push_front(200);
	d.push_front(300);

	//插入 insert
	d.insert(++d.begin(),2, 1000);
	//  300 1000 1000  200 100 10 20 30
	printDeque(d);

	//删除erase
	//d.erase(++d.begin());
	//d.erase(++d.begin());
	deque<int>::iterator it1 = d.begin();
	it1 = it1 + 1;

	deque<int>::iterator it2 = d.begin();
	it2 = it2 + 3;

	d.erase(it1, it2);
	printDeque(d);

	//清空
	d.clear();
	printDeque(d);
}


bool myCompare(int v1,int v2)
{
	return v1 < v2;
}

void test04()
{
	deque<int>d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_front(100);
	d.push_front(200);
	d.push_front(300);

	//默认排序从小到大
	//sort(d.begin(), d.end());
	
	sort(d.begin(), d.end(), myCompare);

	printDeque(d);

}

int main(){
	//test01();
	//test02();
	//test03();
	test04();

	system("pause");
	return EXIT_SUCCESS;
}
```

