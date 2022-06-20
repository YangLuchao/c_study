[toc]

# 员工分组案例

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <map>
#include <ctime>
/*
//公司今天招聘了5个员工，5名员工进入公司之后，需要指派员工在那个部门工作
//人员信息有: 姓名 年龄 电话 工资等组成
//通过Multimap进行信息的插入 保存 显示
//分部门显示员工信息 显示全部员工信息
*/

enum{ CAIWU,RENLI,YANFA};

class Worker
{
public:
	string m_Name;
	int m_Money;
};

void createWorker(vector<Worker>&v)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5;i++)
	{
		Worker worker;
		worker.m_Name = "员工";
		worker.m_Name += nameSeed[i];

		worker.m_Money = rand() % 10000 + 10000; // 10000 ~ 19999

		v.push_back(worker);
	}
}


void setGroup(vector<Worker>&v, multimap<int,Worker>&m)
{
	for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
	{
		//随机产生部门编号   0  1  2
		int dId = rand() % 3;
		m.insert(make_pair(dId, *it));
	}
}

void showWorker(multimap<int,Worker>&m)
{
	cout << "财务部门员工信息如下：" << endl;

	//  0  A  0  B  1 C   2 D  2 E

	multimap<int,Worker>::iterator pos = m.find(CAIWU);

	int num = m.count(CAIWU);
	int index = 0;
	for (; pos != m.end(), index<num; pos++,index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}


	cout << "人力部门员工信息如下：" << endl;
	pos = m.find(RENLI);

	num = m.count(RENLI);
	index = 0;
	for (; pos != m.end(), index < num; pos++, index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}


	cout << "研发部门员工信息如下：" << endl;
	pos = m.find(YANFA);

	num = m.count(YANFA);
	index = 0;
	for (; pos != m.end(), index < num; pos++, index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}


}

int main(){

	//随机数种子
	srand((unsigned int)time(NULL));

	vector<Worker>v;
	//1、创建5名员工
	createWorker(v);

	//2、员工分组
	multimap<int, Worker> m;
	setGroup(v, m);

	//3、分部门显示员工
	showWorker(m);


	//测试
	//for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
	//{
	//	cout << "姓名： " << it->m_Name << " 工资： " << it->m_Money << endl;
	//}

	system("pause");
	return EXIT_SUCCESS;
}
```

# 函数对象

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyPrint
{
public:
	void operator()(int num)
	{
		cout << num << endl;
		m_Count++;
	}

	int m_Count = 0;
};

void myPrint02(int num)
{
	cout << num << endl;
}

void test01()
{
	MyPrint myPrint;
	myPrint(100); //本质是一个类的对象，因此称为函数对象，也叫仿函数

	myPrint02(100);
}


void test02()
{
	//函数对象 超出了普通函数的概念，可以拥有自己状态

	MyPrint myPrint;
	myPrint(100);
	myPrint(100);
	myPrint(100);
	myPrint(100);

	cout << "调用次数为： " << myPrint.m_Count << endl;
}


//函数对象可以作为函数参数
void doPrint(MyPrint myPrint , int num)
{
	myPrint(num);
}

void test03()
{
	doPrint(MyPrint(), 1000);
}

int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 内建函数对象

>6个算数类函数对象,除了negate是一元运算，其他都是二元运算。
>
>template<class T> T plus<T>//加法仿函数template<class T> T minus<T>//减法仿函数template<class T> T multiplies<T>//乘法仿函数template<class T> T divides<T>//除法仿函数template<class T> T modulus<T>//取模仿函数template<class T> T negate<T>//取反仿函数
>
> 6个关系运算类函数对象,每一种都是二元运算。
>
>template<class T> bool equal_to<T>//等于template<class T> bool not_equal_to<T>//不等于template<class T> bool greater<T>//大于template<class T> bool greater_equal<T>//大于等于template<class T> bool less<T>//小于template<class T> bool less_equal<T>//小于等于
>
> 逻辑运算类运算函数,not为一元运算，其余为二元运算。
>
>template<class T> bool logical_and<T>//逻辑与template<class T> bool logical_or<T>//逻辑或template<class T> bool logical_not<T>//逻辑非

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <functional>  //内建函数对象  头文件
#include <vector>
#include <algorithm>
/*
template<class T> T negate<T>//取反仿函数  一元运算
*/

void test01()
{
	negate<int>n;

	cout << n(10) << endl;

}
//template<class T> T plus<T>//加法仿函数
void test02()
{
	plus<int> p;

	cout << p(10, 10) << endl;

}

//template<class T> bool greater<T>//大于
void test03()
{
	vector<int>v;
	v.push_back(20);
	v.push_back(50);
	v.push_back(10);
	v.push_back(30);
	v.push_back(40);

	//从大到小排序
	sort(v.begin(), v.end(), greater<int>());


	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	cout << endl;
}

int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 适配器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

class MyPrint :public binary_function<int,int,void>
{
public:
	void operator()(int val , int start)const 
	{
		cout << "val = " << val << " start = " << start <<  " sum = " <<val +  start << endl;
	}
};
//1、函数对象适配器
void test01()
{
	vector<int>v;

	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}
	cout << "请输入起始累加值： " << endl;
	int num;
	cin >> num;

	for_each(v.begin(), v.end(), bind2nd( MyPrint(), num ) );
	//for_each(v.begin(), v.end(), bind1st(MyPrint(), num));
}

//1、利用bind2nd 进行绑定
//2、继承 public binary_function<参数1 类型,参数2类型,返回值类型>
//3、加const


//2、取反适配器
class GreaterThanFive:public unary_function<int,bool>
{
public:
	bool operator()(int val) const
	{
		return val > 5;
	}
};
void test02()
{
	vector<int>v;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}

	//一元取反
	//vector<int>::iterator pos = find_if(v.begin(), v.end(), not1( GreaterThanFive()));

	vector<int>::iterator pos = find_if(v.begin(), v.end(), not1( bind2nd( greater<int>() , 5 )));

	if (pos != v.end())
	{
		cout << "找到小于5的值为： " << *pos << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}


	//二元取反
	sort(v.begin(), v.end(),  not2 (less<int>()));
	for_each(v.begin(), v.end(), [](int val){cout << val << endl; });
}

//1、利用not1进行取反
//2、继承 public unary_function<int,bool>
//3、加const


void myPrint3( int val , int start) 
{
	cout << val + start << endl;
}
//3、 函数适配器
void test03()
{
	vector<int>v;

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//将函数指针 适配成函数对象  ptr_fun
	for_each(v.begin(), v.end(), bind2nd(ptr_fun(myPrint3), 1000));
}


//4、成员函数适配器
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "成员函数----姓名： " << this->m_Name << " 年龄： " << this->m_Age << endl;
	}

	void addAge()
	{
		this->m_Age += 100;
	}

	string m_Name;
	int m_Age;
};

//void myPrint4( Person & p)
//{
//	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
//}

void test04()
{
	vector< Person > v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	//利用 mem_fun_ref
	for_each(v.begin(), v.end(),  mem_fun_ref(&Person::showPerson));
	for_each(v.begin(), v.end(), mem_fun_ref(&Person::addAge));
	for_each(v.begin(), v.end(), mem_fun_ref(&Person::showPerson));
}

int main(){

//	test01();
//	test02();
//	test03();
	test04();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用遍历算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>

class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << endl;
		m_Count++;
	}

	int m_Count = 0;
};

//for_each  用于遍历
//有返回值的
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}

	MyPrint print = for_each(v.begin(), v.end(), MyPrint());

	cout << "print.count = " << print.m_Count << endl;

}

//for_each可以绑定参数输出
class MyPrint2 :public binary_function<int,int,void>
{
public:
	void operator()(int val , int start) const
	{
		cout << val << endl;
		
	}

};

void test02()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(),  bind2nd( MyPrint2(), 1000));

}


//transform算法 将指定容器区间元素搬运到另一容器中
class MyTransform
{
public:
	int operator()(int val)
	{	
		return val + 10000;
	}
};
void test03()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}



	vector<int>v2;
	v2.resize(v.size());

	transform(v.begin(), v.end(), v2.begin(), MyTransform());

	for_each(v2.begin(), v2.end(), [](int val){cout << val << " "; });

}

int main(){
	//test01();
	//test02();
	test03();


	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用的查找算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
/*
find算法 查找元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value 查找的元素
@return 返回查找元素的位置


find_if算法 条件查找
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  callback 回调函数或者谓词(返回bool类型的函数对象)
@return bool 查找返回true 否则false

*/



void test01()
{
	vector<int>v;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}
	
	vector<int>::iterator pos = find(v.begin(), v.end(), 5);

	if (pos != v.end())
	{
		cout << "找到了元素：" << *pos << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	bool operator==(const Person & p)
	{
		return this->m_Name == p.m_Name && this->m_Age == p.m_Age;
	}

	string m_Name;
	int m_Age;
};

void test02()
{
	vector<Person> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

 
	vector<Person>::iterator pos = find(v.begin(), v.end(), p2);
	if (pos != v.end())
	{
		cout << "找到了元素  姓名： " << (*pos).m_Name << " 年龄： " << (*pos).m_Age << endl;
	}

}

class MyComparePerson :public binary_function< Person *, Person *, bool>
{
public:
	bool operator()(  Person * p1 ,  Person *p2 ) const
	{
		return p1->m_Name == p2->m_Name  && p1->m_Age == p2->m_Age; 
	}
};

void test03()
{
	vector<Person *> v;

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);

	Person * p = new Person("bbb", 20);

	vector<Person *>::iterator pos = find_if(v.begin(), v.end(), bind2nd( MyComparePerson() ,p)  );

	if (pos != v.end())
	{
		cout << "找到了元素--- 姓名： " << (*pos)->m_Name << " 年龄： " << (*pos)->m_Age << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}


//adjacent_find算法 查找相邻重复元素
void test04()
{
	vector<int>v;

	v.push_back(3);
	v.push_back(2);
	v.push_back(300);
	v.push_back(300);
	v.push_back(6);
	v.push_back(3);

	vector<int>::iterator ret = adjacent_find(v.begin(), v.end());

	if (ret != v.end())
	{
		cout << "找到了相邻的重复元素： " << *ret << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

}


/*
binary_search算法 二分查找法
注意: 在无序序列中不可用
*/

void test05()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//v.push_back(4);  必须是有序序列，如果无效 结果未知

   bool ret=binary_search(v.begin(), v.end(), 2);
   if (ret)
   {
	   cout << "查到了数据2" << endl;
   }
   else
   {
	   cout << "未找到数据2" << endl;
   }

}

/*
count算法 统计元素出现次数
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  value回调函数或者谓词(返回bool类型的函数对象)
@return int返回元素个数
*/
class GreaterThan3
{
public:
	bool operator()(int val)
	{
		return val >= 3;
	}
};

void test06()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	v.push_back(3);
	v.push_back(3);
	v.push_back(3);

	int num = count(v.begin(), v.end(), 3);

	cout << "3的个数为： " << num << endl;


	//统计大于等于3的个数
	num = count_if(v.begin(), v.end(), GreaterThan3());
	// 0 1 2 3 4 5 6 7 8 9 3 3 3 
	cout << "大于等于3的个数为： " << num << endl;

}


int main(){
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	test06();


	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用排序算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
/*
merge算法 容器元素合并，并存储到另一容器中
注意 : 两个容器必须是有序的,顺序要一致
*/

void test01()
{
	vector<int>v1;
	vector<int>v2;

	for (int i = 0; i < 10;i++)
	{
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	vector<int>vTarget; //目标容器
	vTarget.resize(v1.size() + v2.size());

	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	for_each(vTarget.begin(), vTarget.end(), [](int val){cout << val << " "; });

}

//sort
void test02()
{
	vector<int>v;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}

	//降序排序

	sort(v.begin(), v.end(), greater<int>());
	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	cout << endl;
}


//random_shuffle算法 对指定范围内的元素随机调整次序
void test03()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	random_shuffle(v.begin(), v.end());
	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	cout << endl;
}

//reverse算法 反转指定范围的元素
void test04()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	cout << "反转前打印：" << endl;
	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	cout << endl;


	reverse(v.begin(), v.end());

	cout << "反转后打印： " << endl;
	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	
	cout << endl;
}

int main(){

	srand((unsigned int)time(NULL));

	//test01();
	//test02();
	//test03();
	test04();


	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用的拷贝和替换算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <iterator>
//copy算法 将容器内指定范围的元素拷贝到另一容器中
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10;i++)
	{
		v.push_back(i);
	}

	vector<int>v2;
	v2.resize(v.size());
	copy(v.begin(), v.end(), v2.begin());

	//for_each(v2.begin(), v2.end(), [](int val){cout << val << " "; });
	//cout << endl;

	copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

//replace算法 将容器内指定范围的旧元素修改为新元素
//replace_if(iterator beg, iterator end, _callback, newvalue) 按条件替换

class MyReplace
{
public:
	bool operator()(int val)
	{
		return val > 3;
	}
};
void test02()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	//将容器中的3替换为 3000
	replace(v.begin(), v.end(), 3, 3000);

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;



	//将容器中所有大于3的都替换为 30000;
	replace_if(v.begin(), v.end(), MyReplace() , 30000);
	// 0 1 2 30000 ...
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}


//swap交换
void test03()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	vector<int>v2(10, 100);

	cout << "交换数据前：" << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;


	cout << "交换数据后：" << endl;
	swap(v, v2);

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

}

int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用算数生成算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric> //accumulate算法头文件


//accumulate算法 计算容器元素累计总和
void test01()
{
	vector<int>v;
	for (int i = 0; i <= 100;i++)
	{
		v.push_back(i);
	}

	int num = accumulate(v.begin(), v.end(),1000); // 参数3代表 累加起始值

	cout << "num = " << num << endl;
}

//fill算法 向容器中添加元素
void test02()
{
	vector<int>v;
	v.resize(10);

	fill(v.begin(), v.end(), 100);

	for_each(v.begin(), v.end(), [](int val){cout << val << " "; });
	cout << endl;

}


int main(){

	//test01();
	test02();


	system("pause");
	return EXIT_SUCCESS;
}
```

# 常用集合算法

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>

/*
set_intersection算法 求两个set集合的交集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/
void test01()
{
	vector<int>v1;
	vector<int>v2;

	for (int i = 0; i < 10;i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int>vTarget;

	vTarget.resize(min(v1.size(), v2.size()));

	vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	for_each(vTarget.begin(), itEnd, [](int val){cout << val << " "; });
	cout << endl;
}


/*
set_union算法 求两个set集合的并集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/

void test02()
{
	vector<int>v1;
	vector<int>v2;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int>vTarget;
	vTarget.resize(v1.size() + v2.size());
	vector<int>::iterator itEnd  = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	for_each(vTarget.begin(), itEnd , [](int val){cout << val << " "; });
	cout << endl;
}

/*
set_difference算法 求两个set集合的差集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/

void test03()
{
	vector<int>v1;
	vector<int>v2;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int>vTarget;
	vTarget.resize( max(v1.size(),v2.size()) );

	// A 与 B 差集
	//vector<int>::iterator itEnd  = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

	// B 与 A 差集
	vector<int>::iterator itEnd = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), vTarget.begin());


	for_each(vTarget.begin(), itEnd, [](int val){cout << val << " "; });
	cout << endl;

}


int main(){
	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}
```

