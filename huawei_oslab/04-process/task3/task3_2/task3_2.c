#include"stdio.h"
#include <stdlib.h>
#include <unistd.h>
int main() {
        int child;
        int i = 1;

	//请添加代码，创建子进程
        if(  ) {
                //子进程
                for(i = 0; i < 20; i++) {
                       //请添加代码，输出子进程的pid和自加变量i的值

                }
		exit(0);

        } else {
                //父进程
                printf("This is father, his count is: %d, his pid is: %d\n", i, getpid());
        }
}
