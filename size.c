/*2017-10-8 此段代码用于检验
 * 1 指针和其指向的地址空间的大小
 * 2 free的作用
 * 3 指针传递以及段错误 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define result  0
struct hehe
{
	char first;   //char为1字节，实际四字节对齐
	int a;
	char *next;
};
struct hehe align={0};

int mycopy(char *buff2)
{
	char* buff3="wolld";
	if(strcpy(buff2,buff3)<0) return -1;
	printf("buff=%s\n",buff2);
	return 0;
}
int main(int argc,const char* argv[])
{
	char buff[128]="hello";
	char* p1=buff;
	char* p2=NULL;
	printf("buff=%s\n",buff);
	printf("size of buff=%d\n",sizeof(buff));  	//128
	printf("strlen of buff=%d\n",strlen(buff)); 	//5

	printf("***************************************************************\n");
	printf("size of pointer=%d\n",sizeof(p1));	//4
	printf("strlen of pointer=%d\n",strlen(p1));	//5

	//函数的值传递和指针结合
	//	mycopy(p2);  //core dump
	//函数传参为值传递，故传递进去的是NULL，往NULL拷贝端错误
	//此处确实使用的是指针，而且网指针中传递值。

	p2=(char*)malloc(sizeof(buff));
	printf("maolloc addr=%p\n",p2);
	printf("buff addr=%p\n",buff);
	strcpy(p2,buff);
	printf("p2=%s\n",p2);
	free(p2);
	printf("free ok!\n");
	printf("p2=%s\n",p2);
	strcpy(p2,"copy something ok!");   
	//可见free后的地址依然可以读写，free只是做了一个标记，具体的释放动作由系统控制
	printf("p2=%s\n",p2);	


	printf("****************************************************************\n");
	printf("struct hehe\n{\n	char first;\n	int a;\n	char* next\n}\n");
	printf("follow is align:\n");
	printf("sizeof struct hehe=%d\n",sizeof(struct hehe));
	printf("sizeof struct var align=%d\n",sizeof(align));
	if(result>=0) printf("macro define compare ok\n");


	printf("****************************************************************\n");
	int buff2[10]={1,2,3,4,5};
	printf("sizeof intbuff2[10]=%d\n",sizeof(buff2));  //4*10=40
	printf("****************************************************************\n");
	printf("sizeof long=%d\n",sizeof(long));
	return result;
}
