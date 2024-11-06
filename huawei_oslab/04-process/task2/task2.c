#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){
	int i=0;
	int data = 0;
	pid_t pid ;
	int choose = 0;
	while((choose = getchar ()) != 'q'){
		switch(choose){
		case '1' :
			pid = fork();
			break;
		case '2':
			//添加代码，使用vfork创建一个子进程

			break;
		default :
			//printf("aaa");
			break;
		}
		if(pid<0){
			printf("Error !\n");
		}
		//请添加代码，子进程对变量data自加操作后退出
		

		printf("process ID:%d\n",getpid());
		//printf("%d",i++);

		//请添加代码，父进程等待子进程结束

		if(pid > 0){
			printf("process ID:%d",getpid());
			printf("data is %d\n", data);
		}
	}
}
