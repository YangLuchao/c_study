[toc]

# 函数

## 分类

函数可分为系统函数和用户定义函数两种：

-   系统函数，即库函数：这是由编译系统提供的，用户不必自己定义这些函数，可以直接使用它们，如我们常用的打印函数printf()。

-   用户定义函数：用以解决用户的专门需要。

## 函数调用：产生随机数

```c
#include <time.h>
time_t time(time_t *t);
// 功能：获取当前系统时间
// 参数：常设置为NULL
// 返回值：当前系统时间, time_t 相当于long类型，单位为毫秒

#include <stdlib.h>
void srand(unsigned int seed);
// 功能：用来设置rand()产生随机数时的随机种子
// 参数：如果每次seed相等，rand()产生随机数相等
// 返回值：无

#include <stdlib.h>
int rand(void);
// 功能：返回一个随机数值
// 参数：无
// 返回值：随机数

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	time_t tm = time(NULL);//得到系统时间
	srand((unsigned int)tm);//随机种子只需要设置一次即可

	int r = rand();
	printf("r = %d\n", r);

	return 0;
}
```

# 函数的定义

>   返回类型 函数名(形式参数列表)
>
>   ​	{
>
>   ​		数据定义部分;
>
>   ​		执行语句部分;
>
>   }

![函数的定义](https://github.com/YangLuchao/c_study/blob/main/%E5%9B%BE/%E5%87%BD%E6%95%B0%E7%9A%84%E5%AE%9A%E4%B9%89.png?raw=true)

## 函数名字、形参、函数体、返回值

### 形参

在定义函数时指定的形参，==在未出现函数调用时，它们并不占内存中的存储单元==，因此称它们是形式参数或虚拟参数，简称形参，表示它们并不是实际存在的数据，所以，形参里的变量不能赋值。

在定义函数时指定的形参，可有可无，根据函数的需要来设计，==如果没有形参，圆括号内容为空，或写一个void关键字==：

```c
/ 没形参， 圆括号内容为空
void max()
{
}

// 没形参， 圆括号内容为void关键字
void max(void)
{
}
```



