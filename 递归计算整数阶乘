//  计算从1到任意整数之间的所有整数之积
#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>

unsigned long long factorial(unsigned long long);

int main(void)
{
	unsigned long long number = 0LL;
	printf("输入一个整数值: ");
	scanf_s("%llu", &number);
	printf("%llu 的阶乘为 %llu\n", number, factorial(number));
	return 0;
}

// 递归阶乘的函数
unsigned long long factorial(unsigned long long n)
{
	if(n < 2LL)
		return n;

	return n*factorial(n-1LL);
}
