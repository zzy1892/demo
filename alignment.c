/*2017-10-24 该代码验证了结构体中各成员的对齐方式和结果*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct test
{ 
	char x1; // 成员x1为char型(其起始地址必须1字节对界)，其偏移地址为0 
	char x2; // 成员x2为char型(其起始地址必须1字节对界，其偏移地址为1 
	float x3; // 成员x3为float型(其起始地址必须4字节对界)，编译器在x2和x3之间填充了两个空字节，其偏移地址为4 
	char buff[2];
	char x4; // 成员x4为char型(其起始地址必须1字节对界)，其偏移地址为8 
//采用默认对齐方式时:整体对齐方式为4字节对齐，占用字节1100 1111 1000，length=12
//定义#pragam pack(2)时，按照两者中的小的对齐，占用字节11 1111 10,length=8
}test_a;
struct length1
{
  int aa1; //4个字节对齐 1111
  char bb1;//1个字节对齐 1
  short cc1;//2个字节对齐 011
  char dd1; //1个字节对齐 1
};
struct length2
{
  char bb2;//1个字节对齐 1
  int aa2; //4个字节对齐 0001111
  short cc2;//2个字节对齐 11
  char dd2; //1个字节对齐 1
};
struct length3
{
  char bb3; //1个字节对齐 1
  char dd3; //1个字节对齐 1
  int aa3; //4个字节对齐 001111
  short cc23;//2个字节对齐 11
};
struct length4
{
  char bb4; //1个字节对齐 1
  char dd4; //1个字节对齐 1
  short cc4;//2个字节对齐 11
  int aa4; //4个字节对齐 1111
};

#pragma pack(8)
struct s1{
short a;
long b;
};

struct s2{
char c;
struct s1 d;
double e;
};
#pragma pack()

int main(int argc,const char* argv[])
{
	test_a=(struct test){0};
	printf("struct test\n{\nchar x1;\nchar x2;\nfloat x3;\nchar buff[2];\nchar x4;\n}\n");
	printf("sizeof test=%d\n",sizeof(struct test));
	printf("sizeof test_a=%d\n",sizeof(test_a));
	strcpy(test_a.buff,"DD");
	printf("copyed \"DD\" to test_a.buff,sizeof test_a=%d\n",sizeof(test_a));
	//4个字节对齐，占用字节1100 1111 1000，length=12
	printf("****************************************************************\n");

	printf("struct length1\n{\nint aa1;\nchar bb1;\nshort cc1;\nchar dd1;\n}\n");
	printf("sizeof length1=%d\n",sizeof(struct length1));
	//4个字节对齐，占用字节1111 1011 1000,length = 12
	printf("****************************************************************\n");

	printf("struct length2\n{\nchar bb2;\nint aa2;\nshort cc2;\nchar dd2\n}\n");
	printf("sizeof length2=%d\n",sizeof(struct length2));
	//4个字节对齐，占用字节1000 1111 1110,length = 12
	printf("****************************************************************\n");

	printf("struct length3\n{\nchar bb3;\nchar dd3;\nint aa3;\nshort cc23;\n}\n");
	printf("sizeof length3=%d\n",sizeof(struct length3));
	//4个字节对齐，占用字节1100 1111 1100,length = 12
	printf("****************************************************************\n");

	printf("struct length4\n{\nchar bb4;\nchar dd4;\nshort cc4;\nint aa4;\n}\n");
	printf("sizeof lentgh4=%d\n",sizeof(struct length4));
	//4个字节对齐，占用字节1111 1111,length = 8
	printf("****************************************************************\n");
	printf("struct s1\n{\nshort a;\nlong b;\n};\n");
	printf("struct s2\n{\nchar c;\nstruct s1 d;\ndouble e;\n};\n");
	printf("sizeof s1=%d\nsizeof s2=%d\n",sizeof(struct s1),sizeof(struct s2));
	//sizeof(s2)的结果一般来说应为24。S1的内存布局为1100 1111，S2的内存布局为1000 1100 1111 0000 1111 1111。
	//但是这还要和系统默认的对齐方式做比较，大于默认的对齐方式时按默认的处理，故此处最终为20
	printf("****************************************************************\n");
	printf("sizeof double=%d\n",sizeof(double));
	return 0;
}
