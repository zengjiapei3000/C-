// 字符排序的功能（用冒泡排序来实现）

#define __STDC_WANT_LIB_EXT1__ 1          // C11可选字符串函数的支持
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define BUF_LEN 256                       // 输入字符串的最大长度
#define INIT_NSTR 2                       // 初始的字符串个数
#define NSTR_INCR 2                       // 增加的字符串个数

char* str_in();                           // 用于读取字符串的函数
void str_sort(const char**, size_t);      // 用于按升序来排序、存储字符串的函数
void swap(const char**, const char**);    // 交换两个指针（冒泡排序）
void str_out(const char* const*,size_t);  // 输出字符串的函数
void free_memory(char**, size_t);         // 释放所有堆上的内存

// 主函数 - 开始执行的地方
int main(void)
{
	size_t pS_size = INIT_NSTR;                  // 初始化pS的大小
	char **pS = calloc(pS_size, sizeof(char*));  // 在堆上创建内存给pS
	if(!pS)
	{
		printf("无法为字符串指针分配内存.\n");
		exit(1);
	}
	char **pTemp = NULL;                         // 临时的pointer
	size_t str_count = 0;                        // 读取的字符串计数器
	char *pStr = NULL;                           // 字符的pointer
	printf("每行输入一个字符串。按Enter键结束:\n");
	while((pStr = str_in()) != NULL)
	{
		if(str_count == pS_size)
		{
			pS_size += NSTR_INCR;
			if(!(pTemp = realloc(pS, pS_size*sizeof(char*))))
			{
				printf("字符串数组的内存分配失败.\n");
				return 2;
			}
			pS = pTemp;
		}
		pS[str_count++] = pStr;
	}

	str_sort(pS, str_count);         // 字符串排序
	str_out(pS, str_count);          // 输出排序后字符串
	free_memory(pS, str_count);      // 释放堆上内存
	return 0;
}

char* str_in(void)
{
	char buf[BUF_LEN];               // 用于存储输入字符串的空间
	if(!gets_s(buf, BUF_LEN))        // if 接收到的返回值为NULL...
	{                                // ...终止操作
		printf("\n读取字符串出错.\n");
		return NULL;
	}

	if(buf[0] == '\0')               // if 读取到空字符...
		return NULL;             // ...终止操作

	size_t str_len = strnlen_s(buf, BUF_LEN) + 1;
	char *pString = malloc(str_len);
	
	if(!pString)                     // if 没有分配好内存...
	{
		printf("内存分配失败.\n");
		return NULL;             // ...终止操作
	}

	strcpy_s(pString, str_len, buf); // 复制字符读入到pString里
	return pString;
}

void str_sort(const char **p, size_t n)
{
	bool sorted = false;                      // 字符串排序指标bool值
	while(!sorted)                            // 循环，直到没有交换时结束
	{
		sorted = true;                    // 初始化，来表示没有互换
		for(int i = 0; i < n - 1; ++i)
		{
			if(strcmp(p[i],p[i + 1]) > 0)     // 比较p[i]p和[i+1]的大小
			{
				sorted = false;           // 表示一次排序结束
				swap(&p[i], &p[i + 1]);   // 交换字符串地址
			}
		}
	}
}

void swap(const char** p1, const char** p2)
{
	const char *pT = *p1;
	*p1 = *p2;
	*p2 = pT;
}

void str_out(const char* const* pStr, size_t n)
{
	printf("排序后的字符串为:\n");
	for(size_t i = 0; i < n; ++i)
		printf("%s\n", pStr[i]);         // 展示一个字符
}

void free_memory(char **pS, size_t n)
{
	for(size_t i = 0; i < n; ++i)
	{
		free(pS[i]);
		pS[i] = NULL;
	}
	free(pS);
	pS = NULL;
}
