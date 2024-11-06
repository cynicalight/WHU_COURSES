// hello.c
#include <stdio.h>
#include "hello.h"
void printHello()
{
	printf("hello world!\n");
}
// main.c
#include <stdio.h>
#include "hello.h"
int main()
{
	printHello();
	return 0;
}
// hello.h
// 仅包含函数声明
#ifndef _HELLO_
#define _HELLO_
void printHello();
#endif
