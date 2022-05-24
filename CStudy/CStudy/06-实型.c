#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main0601(void)
{
	float m = 3.145;
	double n = 4.566545;

	printf("m = %08.2f\n", m);
	printf("n = %08.3lf\n", n);

	system("pause");
	return EXIT_SUCCESS;
}
