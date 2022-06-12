[toc]

# 静态联编和动态联编

==静态多态和动态多态的区别就是函数地址是早绑定(静态联编)还是晚绑定(动态联编)。==

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	//虚函数
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}

	virtual void eat(int a )
	{
		cout << "动物在吃饭" << endl;
	}
};

class Cat :public Animal
{
public:
	void speak()
	{
		cout << "小猫在说话" << endl;
	}

	void eat(int a)
	{
		cout << "小猫在吃饭" << endl;
	}
};

class Dog :public Animal
{
public:
	void speak()
	{
		cout << "小狗在说话" << endl;
	}
};


//动态多态产生条件：
//先有继承关系
//父类中有虚函数，子类重写父类中的虚函数
//父类的指针或引用  指向子类的对象

//对于有父子关系的两个类  指针或者引用 是可以直接转换的
void doSpeak(Animal & animal) //Animal & animal = cat;
{
	//如果地址早就绑定好了，地址早绑定，属于静态联编
	//如果想调用小猫说话，这个时候函数的地址就不能早就绑定好，而是在运行阶段再去绑定函数地址，属于地址晚绑定，叫动态联编
	animal.speak(); 

}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}




void test02()
{
	//cout << "sizeof  Animal = " << sizeof (Animal) << endl;

	Animal * animal = new Cat;
	//animal->speak();
	// *(int *)animal 解引用到虚函数表中
	// *(int *)*(int *)animal 解引用到函数speak地址

	//调用猫说话
	((void(*)()) (*(int *)*(int *)animal)) ();


	//C/C++默认调用惯例  __cdecl
	//用下列调用时候 真实调用惯例  是 __stdcall
	//调用猫吃饭
	typedef void( __stdcall *FUNPOINT)(int);

	(FUNPOINT (*((int*)*(int*)animal + 1)))(10);
}

```

## 虚函数的本质

>vfptr - 虚函数指针 指向 虚函数表(vftable) 
>
>v - virtual
>
>f - function
>
>ptr - poniter

重新：子类重写父类的虚函数，函数返回值、函数名称、参数列表相同

# 多态案例-计算器实现

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//class calculator
//{
//public:
//
//	int getResult( string oper)
//	{
//		if (oper == "+")
//		{
//			return m_A + m_B;
//		}
//		else if (oper == "-")
//		{
//			return m_A - m_B;
//		}
//		else if (oper == "*")
//		{
//			return m_A * m_B;
//		}
//		
//	}
//
//	int m_A;
//	int m_B;
//};

//设计原则 ： 开闭原则
// 对扩展进行开放  对修改进行关闭

//利用多态实现计算器
class AbstractCalculator
{
public:

	//纯虚函数
	//如果一个类中包含了纯虚函数，那么这个类就无法实例化对象了,这个类通常我们称为 抽象类
	//抽象类的子类 必须要重写 父类中的纯虚函数，否则也属于抽象类
	virtual int getResult() = 0;

	//virtual int getResult()
	//{
	//	return 0;
	//}

	int m_A;
	int m_B;
};
//加法计算器
class AddCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return m_A + m_B;
	}
};

//减法计算器
class SubCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return m_A - m_B;
	}
};

//乘法计算器
class MulCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return m_A * m_B;
	}
};

class Test :public AbstractCalculator
{
	int getResult(){ return 0; };
};

void test01()
{
	//calculator c;
	//c.m_A = 10;
	//c.m_B = 10;
	//cout << c.getResult("+") << endl;


	AbstractCalculator * calculator = new AddCalculator;

	calculator->m_A = 100;
	calculator->m_B = 200;

	cout << calculator->getResult() << endl;

	delete calculator;

	calculator = new SubCalculator;
	calculator->m_A = 100;
	calculator->m_B = 200;

	cout << calculator->getResult() << endl;

}

```

# 纯虚函数和抽象类/虚析构和纯虚析构

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	Animal()
	{
		cout << "Animal的构造函数调用" << endl;
	}
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
	//如果子类中有指向堆区的属性，那么要利用虚析构技术 在delete的时候 调用子类的析构函数
	//virtual ~Animal()
	//{
	//	cout << "Animal的析构函数调用" << endl;
	//}

	//纯虚析构 需要有声明 也需要有实现
	//如果一个类中 有了 纯虚析构函数，那么这个类也属于抽象类，无法实例化对象了
	virtual ~Animal() = 0;

};

Animal::~Animal()
{
	cout << "Animal的纯虚析构函数调用" << endl;
}


class Cat :public Animal
{
public:
	Cat(char * name)
	{
		cout << "Cat的构造函数调用" << endl;
		this->m_Name = new char[strlen(name) + 1];
		strcpy(this->m_Name, name);
	}

	virtual void speak()
	{
		cout << this->m_Name <<" 小猫在说话" << endl;
	}

	~Cat()
	{
		if (this->m_Name)
		{
			cout << "Cat的析构函数调用" << endl;
			delete[] this->m_Name;
			this->m_Name = NULL;
		}
	}
	char * m_Name;
};

void test01()
{
	Animal * animal = new Cat("Tom");
	animal->speak();

	delete animal;
}

```

# 多态案例-电脑组装

```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//CPU基类
class CPU
{
public:
	virtual void calculate() = 0;
};
//显卡基类
class VideoCard
{
public:
	virtual void display() = 0;
};
//内存基类
class Memory
{
public:
	virtual void storage() = 0;
};


//电脑类
class computer
{
public:

	computer(CPU * cpu, VideoCard * vc, Memory * mem)
	{
		cout << "电脑构造调用" << endl;
		this->m_Cpu = cpu;
		this->m_Vc = vc;
		this->m_Mem = mem;
	}

	void doWork()
	{
		this->m_Cpu->calculate();
		this->m_Vc->display();
		this->m_Mem->storage();
	}

	~computer()
	{
		cout << "电脑析构调用" << endl;
		if (this->m_Cpu)
		{
			delete this->m_Cpu;
			this->m_Cpu = NULL;
		}
		if (this->m_Vc)
		{
			delete this->m_Vc;
			this->m_Vc = NULL;
		}
		if (this->m_Mem)
		{
			delete this->m_Mem;
			this->m_Mem = NULL;
		}
	}

	CPU * m_Cpu;
	VideoCard * m_Vc;
	Memory * m_Mem;
};


//inter厂商
class intelCPU :public CPU
{
public:
	void calculate()
	{
		cout << "intelCPU开始计算了" << endl;
	}
};

class intelVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "intel 显卡开始显示了" << endl;
	}

};
class intelMemory :public Memory
{
public:
	void storage()
	{
		cout << "intel 内存条开始存储了" << endl;
	}
};


//Lenovo 厂商
class LenovoCPU :public CPU
{
public:
	void calculate()
	{
		cout << "Lenovo CPU开始计算了" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "Lenovo 显卡开始显示了" << endl;
	}

};
class LenovoMemory :public Memory
{
public:
	void storage()
	{
		cout << "Lenovo 内存条开始存储了" << endl;
	}
};


void test01()
{
	cout << "第一台电脑组成：" << endl;

	CPU * intelCpu = new intelCPU;
	VideoCard * lenovoVC = new LenovoVideoCard;
	Memory * lenovoMem = new LenovoMemory;

	computer c1(intelCpu, lenovoVC, lenovoMem);

	c1.doWork();

	cout << "第二台电脑组成：" << endl;

	CPU * intelCpu2 = new LenovoCPU;
	VideoCard * lenovoVC2 = new intelVideoCard;
	Memory * lenovoMem2 = new intelMemory;

	computer c2(intelCpu2, lenovoVC2, lenovoMem2);

	c2.doWork();


}

```

