[toc]

# 评委打分案例

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>
/*
有5名选手：选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
//1. 创建五名选手，放到vector中
//2. 遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
//3. sort算法对deque容器中分数排序，pop_back pop_front去除最高和最低分
//4. deque容器遍历一遍，累加分数，累加分数/d.size()
//5. person.score = 平均分
*/

class Player
{
public:
	Player(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}

	string m_Name;  //姓名
	int m_Score; //平均分
};


void createPlayer(vector<Player>&v)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5;i++)
	{
		string name = "选手";
		name += nameSeed[i];

		int score = 0;

		Player player(name, score);

		v.push_back(player);
	}
}


void setScore(vector<Player>&v)
{
	for (vector<Player>::iterator it = v.begin(); it != v.end();it++)
	{
		deque<int>d; //存放评委打分的容器
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60; // 60 ~  100
			d.push_back(score);
		}

		//cout << it->m_Name << "打分情况：" << endl;
		//for (deque<int>::iterator dit = d.begin(); dit != d.end();dit++)
		//{
		//	cout << *dit << " ";
		//}
		//cout << endl;

		//排序
		sort(d.begin(), d.end());

		//去除最高最低分
		d.pop_back();  // 最高分
		d.pop_front(); // 最低分

		//总分
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit;
		}
		//平均分
		int avg = sum / d.size();

		it->m_Score = avg;
	}
}

void showScore(vector<Player>&v)
{
	for (vector<Player>::iterator it = v.begin(); it != v.end();it++)
	{
		cout << "姓名： " << (*it).m_Name << " 平均分数： " << it->m_Score << endl;
	}
}

int main(){

	//设置随机数种子
	srand((unsigned int)time(NULL));

	//1、创建5名选手
	vector<Player> v;
	createPlayer(v);

	//2、打分
	setScore(v);

	//3、显示平均分
	showScore(v);

	/*for (vector<Player>::iterator it = v.begin(); it != v.end();it++)
	{
		cout << "姓名： " << (*it).m_Name << " 分数： " << it->m_Score << endl;
	}*/


	system("pause");
	return EXIT_SUCCESS;
}
```



# 栈容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <stack>

/*
3.4.3.1 stack构造函数
stack<T> stkT;//stack采用模板类实现， stack对象的默认构造形式：
stack(const stack &stk);//拷贝构造函数
3.4.3.2 stack赋值操作
stack& operator=(const stack &stk);//重载等号操作符
3.4.3.3 stack数据存取操作
push(elem);//向栈顶添加元素
pop();//从栈顶移除第一个元素
top();//返回栈顶元素
3.4.3.4 stack大小操作
empty();//判断堆栈是否为空
size();//返回堆栈的大小
*/

void test01()
{
	stack<int>S;
	//入栈
	S.push(10);
	S.push(20);
	S.push(30);
	S.push(40);

	cout << "size  = " << S.size() << endl;

	while (!S.empty())
	{
		//访问栈顶元素
		cout << S.top() << endl;
		//出栈
		S.pop();
	}
	cout << "size  = " << S.size() << endl;

}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# 队列容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <queue>
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

void test01()
{
	queue<Person> Q; //队列容器

	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);


	//入队
	Q.push(p1);
	Q.push(p2);
	Q.push(p3);
	Q.push(p4);

	cout << "size = " << Q.size() << endl;

	while ( !Q.empty())
	{
		cout << "队头元素--- 姓名：  " << Q.front().m_Name << " 年龄： " << Q.front().m_Age << endl;
		cout << "队尾元素--- 姓名：  " << Q.back().m_Name << " 年龄： " << Q.back().m_Age << endl;

		//出队
		Q.pop();
	}

	cout << "size = " << Q.size() << endl;

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

# list容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <list>
#include <algorithm>
#include <string>
void test01()
{

	list<int> myList;
	for (int i = 0; i < 10; i++){
		myList.push_back(i);
	}

	list<int>::_Nodeptr node = myList._Myhead->_Next;

	for (int i = 0; i < myList._Mysize * 2; i++){
		cout << "Node:" << node->_Myval << endl;
		node = node->_Next;
		if (node == myList._Myhead){
			node = node->_Next;
			//node = node->_Prev
		}
	}


}

/*
3.6.4.1 list构造函数
list<T> lstT;//list采用采用模板类实现,对象的默认构造形式：
list(beg,end);//构造函数将[beg, end)区间中的元素拷贝给本身。
list(n,elem);//构造函数将n个elem拷贝给本身。
list(const list &lst);//拷贝构造函数。
3.6.4.2 list数据元素插入和删除操作
push_back(elem);//在容器尾部加入一个元素
pop_back();//删除容器中最后一个元素
push_front(elem);//在容器开头插入一个元素
pop_front();//从容器开头移除第一个元素
insert(pos,elem);//在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
remove(elem);//删除容器中所有与elem值匹配的元素。
*/

//遍历链表
void printList(const list<int> & L)
{
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test02()
{
	list<int> L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);

	//正序遍历
	//for (list<int>::iterator it = L1.begin(); it != L1.end();it++)
	//{
	//	cout << *it << endl;
	//}
	//逆序遍历
	for (list<int>::reverse_iterator it = L1.rbegin(); it != L1.rend();it++)
	{
		cout << *it << endl;
	}

	//list迭代器是不是支持随机访问 ,答案：不支持，是一个双向迭代器
	list<int>::iterator itBegin = L1.begin();
	//itBegin = itBegin + 1;
}

void test03()
{
	list<int>L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_front(100);
	L.push_front(200);
	L.push_front(300);

	printList(L);

	L.pop_back(); //尾删
	L.pop_front(); //头删
	// 200 100 10 20
	printList(L);


	//插入
	L.insert(L.begin(), 10000);
	// 10000 200 100 10 20
	printList(L);

	L.erase(L.begin());
	// 200 100 10 20 
	printList(L);

	//remove 删除容器中所有与elem值匹配的元素。
	L.push_back(100);
	L.push_back(100);
	L.remove(100);
	printList(L);

}

/*
3.6.4.3 list大小操作
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(num);//重新指定容器的长度为num，
若容器变长，则以默认值填充新位置。
如果容器变短，则末尾超出容器长度的元素被删除。
resize(num, elem);//重新指定容器的长度为num，
若容器变长，则以elem值填充新位置。
如果容器变短，则末尾超出容器长度的元素被删除。

3.6.4.4 list赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
list& operator=(const list &lst);//重载等号操作符
swap(lst);//将lst与本身的元素互换。
3.6.4.5 list数据的存取
front();//返回第一个元素。
back();//返回最后一个元素。
*/
void test04()
{
	list<int>L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_front(100);
	L.push_front(200);
	L.push_front(300);

	list<int>L2;
	L2.assign(10, 100);

	L.swap(L2);

	printList(L);

}


/*
3.6.4.6 list反转排序
reverse();//反转链表，比如lst包含1,3,5元素，运行此方法后，lst就包含5,3,1元素。
sort(); //list排序
*/
bool myCompare(int v1 ,int v2)
{
	return v1 > v2;
}

void test05()
{
	list<int>L;
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	L.push_front(100);
	L.push_front(200);
	L.push_front(300);

	//反转
	L.reverse();

	printList(L);

	//排序  
	//如果容器的迭代器支持随机访问，可以使用系统提供的标志算法
	//不支持随机访问的迭代器的容器，内部会提供对应的算法接口
	//sort(L.begin(), L.end());
	/*L.sort(myCompare);
	printList(L);*/
}


class Person
{
public:
	Person(string name, int age , int height)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = height;
	}

	bool operator==( const Person & p )
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age && this->m_Height == p.m_Height)
		{
			return true;
		}
		return false;
	}

	string m_Name;
	int m_Age;
	int m_Height;
};

bool myComparePerson( Person &p1, Person &p2)
{
	if (p1.m_Age == p2.m_Age )
	{
		return p1.m_Height < p2.m_Height;
	}

	return  p1.m_Age > p2.m_Age;
}

void test06()
{
	list<Person> L;

	Person p1("亚瑟", 40 ,  180);
	Person p2("赵云", 20 , 160);
	Person p3("妲己", 30 , 120);
	Person p4("孙悟空", 50 , 200);
	Person p5("关羽", 10 ,  170 );
	Person p6("刘备", 10  , 165);
	Person p7("张飞", 10 , 185);

	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);
	L.push_back(p7);

	//按照年龄进行降序   从大到下 , 如果年龄相等，按照身高进行升序 
	//对于自定义数据类型，必须要指定排序规则
	L.sort(myComparePerson);

	for (list<Person>::iterator it = L.begin(); it != L.end();it++)
	{
		cout << "姓名： " << (*it).m_Name << " 年龄： " << it->m_Age << " 身高： "<< it->m_Height <<endl;
	}

	//删除孙悟空
	L.remove(p4);

	cout << "删除孙悟空后：" << endl;
	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名： " << (*it).m_Name << " 年龄： " << it->m_Age << " 身高： " << it->m_Height << endl;
	}

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

# set容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <set>
#include <string>

/*
3.7.2.1 set构造函数
set<T> st;//set默认构造函数：
mulitset<T> mst; //multiset默认构造函数:
set(const set &st);//拷贝构造函数
3.7.2.2 set赋值操作
set& operator=(const set &st);//重载等号操作符
swap(st);//交换两个集合容器
3.7.2.3 set大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空

3.7.2.4 set插入和删除操作
insert(elem);//在容器中插入元素。
clear();//清除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg, end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(elem);//删除容器中值为elem的元素。
*/

void printSet(set<int>&s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	set<int>s;

	s.insert(10);
	s.insert(50);
	s.insert(30);
	s.insert(20);
	s.insert(40);

	printSet(s);


	if (s.empty())
	{
		cout << "set容器为空" << endl;
	}
	else
	{
		cout << "set容器不为空  大小为： " << s.size() << endl;
	}

	s.erase(30);

	printSet(s);
}


/*
3.7.2.5 set查找操作
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
count(key);//查找键key的元素个数
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
*/

void test02()
{
	set<int>s;

	s.insert(10);
	s.insert(50);
	s.insert(30);
	s.insert(20);
	s.insert(40);

	set<int>::iterator pos = s.find(30);
	if (pos != s.end())
	{
		cout << "找到了元素：" << *pos << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

	//对于set而言，count的结果  要么是0  要么是1
	int num = s.count(40);

	cout << "key为40的个数为：" << num << endl;

	//lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
	set<int>::iterator pos2 = s.lower_bound(30);

	if (pos2 != s.end())
	{
		cout << "lower_bound的值为：" << *pos2 << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}


	//upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
	pos2 = s.upper_bound(30);
	if (pos2 != s.end())
	{
		cout << "upper_bound的值为：" << *pos2 << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}


	//equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

	pair< set<int>::iterator, set<int>::iterator>  ret = s.equal_range(30);

	if (ret.first != s.end())
	{
		cout << "equal_range中的lower_bound的值为：" << *ret.first << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}


	if (ret.second != s.end())
	{
		cout << "equal_range中的upper_bound的值为：" << *ret.second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

}

//pair创建
void test03()
{
	pair<string, int> p("Tom", 10);

	cout << "姓名： " << p.first <<  " 年龄： "<< p.second << endl;


	pair<string, int> p2 = make_pair("Jerry", 18);
	cout << "姓名： " << p2.first << " 年龄： " << p.second << endl;
}


void test04()
{
	set<int>s;
	pair<set<int>::iterator, bool> ret = s.insert(10);
	
	if (ret.second)
	{
		cout << "第一次插入成功" << endl;
	}
	else
	{
		cout << "第一次插入失败" << endl;
	}
	
	
	ret = s.insert(10);
	if (ret.second)
	{
		cout << "第二次插入成功" << endl;
	}
	else
	{
		cout << "第二次插入失败" << endl;
	}


	printSet(s);

	//允许插入重复的key值
	multiset<int> ms;
	ms.insert(10);
	ms.insert(10);
	cout << "---------" << endl;
	for (multiset<int>::iterator it = ms.begin(); it != ms.end();it++)
	{
		cout << (*it) << endl;
	}

}


class myCompareInt
{
public:
	bool operator()(int v1 , int v2)
	{
		return v1 > v2;
	}
};

void test05()
{
	//set容器的排序规则要在插入之前指定
	set<int, myCompareInt >s;

	s.insert(10);
	s.insert(50);
	s.insert(30);
	s.insert(20);
	s.insert(40);

	//printSet(s);

	for (set<int, myCompareInt>::iterator it = s.begin(); it != s.end();it++)
	{
		cout << *it << endl;
	}
}

//对于自定义数据类型
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

class myComparePerson
{
public:
	bool operator()( const Person & p1 , const Person & p2)
	{
		//按照年龄 升序  从小到大
		return p1.m_Age < p2.m_Age;
	}
};

void test06()
{
	//利用仿函数  指定出自定义数据类型的排序规则
	set<Person,myComparePerson> s;

	Person p1("aaa", 10);
	Person p2("bbb", 40);
	Person p3("ccc", 20);
	Person p4("ddd", 30);
	Person p5("eee", 50);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	s.insert(p5);

	for (set<Person, myComparePerson>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "姓名： " << (*it).m_Name << " 年龄： " << (*it).m_Age << endl;
	}

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

# map容器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <map>
/*
3.8.2.1 map构造函数
map<T1, T2> mapTT;//map默认构造函数:
map(const map &mp);//拷贝构造函数
3.8.2.2 map赋值操作
map& operator=(const map &mp);//重载等号操作符
swap(mp);//交换两个集合容器

3.8.2.3 map大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空
3.8.2.4 map插入数据元素操作
map.insert(...); //往容器插入元素，返回pair<iterator,bool>
map<int, string> mapStu;
// 第一种 通过pair的方式插入对象
mapStu.insert(pair<int, string>(3, "小张"));
// 第二种 通过pair的方式插入对象
mapStu.inset(make_pair(-1, "校长"));
// 第三种 通过value_type的方式插入对象
mapStu.insert(map<int, string>::value_type(1, "小李"));
// 第四种 通过数组的方式插入值
mapStu[3] = "小刘";
mapStu[5] = "小王";
*/

void test01()
{
	map<int, int> m;

	//第一种插入方式
	m.insert(pair<int, int>(1,10));

	//第二种插入方式  推荐
	m.insert(make_pair(2, 20));

	//第三种插入方式
	m.insert(map<int, int>::value_type(3, 30));

	//第四种
	m[4] = 40;

	//cout << m[10] << endl; //如果利用第四种 使用未指定的key，生成一个key为为指定的值，value为0的数据插入到容器中

	for (map<int, int>::iterator it = m.begin(); it != m.end();it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}

}

/*
3.8.2.5 map删除操作
clear();//删除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg,end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(keyElem);//删除容器中key为keyElem的对组。
*/
void test02()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;

	m.erase(3); //删除传入key值

	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}

}

/*
3.8.2.6 map查找操作
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
*/

void test03()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;

	map<int,int>::iterator ret = m.find(3);
	if (ret != m.end())
	{
		cout << "找到了 key为 " << ret->first << " value = " << ret->second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

	//统计  count 
	int num =  m.count(4);
	cout << "key为4的对组个数为： " << num << endl;

	//lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
	map<int,int>::iterator pos = m.lower_bound(3);

	if (pos != m.end())
	{
		cout << "找到了lower_bound key: " << pos->first << " value: " << pos->second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

	//upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
	pos = m.upper_bound(3);
	if (pos != m.end())
	{
		cout << "找到了upper_bound key: " << pos->first << " value: " << pos->second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}


	//equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
	pair<map<int, int>::iterator, map<int, int>::iterator>  ret2 = m.equal_range(3);

	if ( ret2.first != m.end() )
	{
		cout << "找到了equal_range中的 lower_bound的 key =  " << ret2.first->first << " value = " << ret2.first->second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

	if (ret2.second != m.end())
	{
		cout << "找到了equal_range中的 upper_bound的 key =  " << ret2.second->first << " value = " << ret2.second->second << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}

}


class myCompareInt
{
public:
	bool operator()(int v1,int v2)
	{
		return v1 > v2;
	}
};
void test04()
{
	map<int, int, myCompareInt> m;

	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;

	for (map<int, int, myCompareInt>::iterator it = m.begin(); it != m.end();it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}

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

