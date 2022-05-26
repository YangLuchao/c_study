//
//  C1.c
//  CStudy
//
//  Created by 杨禄超 on 2022/5/24.
//

#include "C1.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main0501(void)
{
    char ch = 'A';  // 65

    //printf("1 ch = %c\n", ch);
    printf("1 ch = %d\n", ch);

    ch = 'm'; //

    //printf("2 ch = %c\n", ch);
    printf("2 ch = %d\n", ch);

    //ch = 97;
    ch = 'a';    // 97

    //printf("3 ch = %c\n", ch);
    printf("3 ch = %d\n", ch);

    system("pause");
    return EXIT_SUCCESS;
}

/**
 * 指针操作数组元素
 * @return
 */
int  main02()
{
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i = 0;
    int n = sizeof(a) / sizeof(a[0]);

    for (i = 0; i < n; i++)
    {
        printf("%d, ", a[i]);
        printf("%d, ", *(a+i));
    }
    printf("\n");

    int *p = a; 	//定义一个指针变量保存a的地址
    for (i = 0; i < n; i++)
    {
        p[i] = 2 * i;
    }

    for (i = 0; i < n; i++)
    {
        printf("%d, ", *(p + i));
    }
    printf("\n");


    return 0;
}

/**
 * 指针的加减运算
 */
int main03()
{
    int a = 1;
    printf("%d\n", a);
    int *p = &a;
    printf("%d\n", p);
    p += 2;//移动了2个int
    printf("%d\n", p);

    char b = 0;
    char *p1 = &b;
    printf("%d\n", p1);
    p1 += 2;//移动了2个char
    printf("%d\n", p1);

    return 0;
}

int main04()
{
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i = 0;
    int n = sizeof(a) / sizeof(a[0]);

    int *p = a;
    for (i = 0; i < n; i++)
    {
        printf("%d, ", *p);
        p++;
    }
    printf("\n");

    return 0;
}
/**
 * 指针的减法运算
 */
int main05()
{
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int *p2 = &a[2]; //第2个元素地址
    int *p1 = &a[1]; //第1个元素地址
    printf("p1 = %p, p2 = %p\n", p1, p2);

    // p2和p1只差个内存位置
    int n1 = p2 - p1; //n1 = 1
//    int n2 = (int)p2 - (int)p1; //n2 = 4
    printf("n1 = %d, n2 = %d\n", n1, 1);

    return 0;
}

void swap1(int x, int y)
{
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
    printf("x = %d, y = %d\n", x, y);
}

void swap2(int *x, int *y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

/**
 * 值传递与引用传递的最直接代码
 * @return
 */
int main06()
{
    int a = 3;
    int b = 5;
    swap1(a, b); //值传递
    printf("a = %d, b = %d\n", a, b);

    a = 3;
    b = 5;
    swap2(&a, &b); //地址传递
    printf("a2 = %d, b2 = %d\n", a, b);

    return 0;
}