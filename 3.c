// 单向链表来用升序遍历马儿的结构
#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct Horse Horse;   // 用typedef定义Horse定义等同于struct Horse

struct Horse                  // 结构定义
{
	int age;
	int height;
	char name[20];
	char father[20];
	char mother[20];
	Horse *next;              // 指向下一horse结构的指针
};

int main(void)
{
	Horse *first = NULL;      // 指向第一个 horse 的pointer
	Horse *current = NULL;    // 指向当前 horse 的pointer
	Horse *previous = NULL;   // 指向上一个 horse 的pointer

	char test = '\0';         // 用0字符结束输入的测试值

	for(;;)
	{
		printf_s("Do you want to enter details of a%s horse (Y or N)? ",
			                               first != NULL?"nother" : "" );
		scanf_s(" %c", &test, sizeof(test));
		if(tolower(test) == 'n')
			break;

		// Allocate memory for a Horse structure
		current = (Horse*) malloc(sizeof(Horse));
		if(first == NULL)                     // If 没有第一匹马（的地址）...
			first = current;              // ...把它设为第一匹马（的地址）

		if(previous != NULL)                  // If previous 不为NULL...
			previous->next = current;     // ...设置它的下一个为当前值（的地址）

		printf_s("Enter the name of the horse: ");
		scanf_s(" %s", current->name, sizeof(current->name));

		printf_s("How old is %s? ", current->age);
		scanf_s(" %d", &current->age);

		printf_s("How high is %s ( in gand )? ", current->name);
		scanf_s("%d", &current->height);

		printf_s("Who is %s's father? ", current->name);
		scanf_s("%s", current->father,sizeof(current->father));

		printf_s("Who is %s's mother? ", current->name);
		scanf_s("%s", current->mother,sizeof(current->mother));

		current->next = NULL;         // 如果它是最后一个（的地址），没有下一个（~）了...
		previous = current;           // ...把当前值存储到previous里，作为上一个（~）
	}

	// 现在链表形成，输出已知数据...
	printf_s("\n");
	current = first;                      // 从第一个（~）开始
	while(current != NULL)                // 当 当前值（~）不为NULL时
	{  // Output the data
		printf_s("%s is %d years old, %d hands high,",
			               current->name, current->age, current->height);
		printf_s(" and has %s and %s as parents.\n", current->father,
                                                   current->mother);
		previous = current;           // 保存指针，下一步释放内存
		current = current->next;      // 获取指向下一个的指针
		free(previous);               // 释放上一个的指针的内存
		previous = NULL;
	}
	first = NULL;
	return 0;
}
