#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int variable;
int do_something() {
	variable = 42;
	printf("in child process\n");
	return 0;
}
int main(int argc, char *argv[]) {
	void *child_stack;
	char tempch;
	variable = 9;

	child_stack = (void *)malloc(16384);
	printf("The variable was %d\n",variable);

	//请添加代码，使用clone函数创建子进程do_something，使用CLONE_VM |CLONE_FILES

	sleep(3);  

	printf("The variable is now %d\n",variable);
	return 0;
}
