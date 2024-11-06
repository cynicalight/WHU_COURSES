#include <stdlib.h>
#include <unistd.h>
#include"stdio.h"

int main() {
        int i = 1;
        int child;

	//请添加代码，创建一个子进程，返回值给child
        if(  ) {
                //子进程过程
                for(i = 0; i < 20; i++) {
			//请添加代码，使子进程睡眠1秒

                        printf("This is son, his count is: %d. and his pid is: %d\n", i, getpid());
                }
		//请添加代码，使子进程退出

        } else {
		//请添加代码，使父进程睡眠3秒

                printf("This is father, his count is: %d, his pid is: %d\n", i, getpid());
        }
}
