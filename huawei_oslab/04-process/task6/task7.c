#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
        pid_t pc, pr;
        pc=fork();
        if(pc<0) /* 如果fork出错 */
               printf("Error occured on forking./n");
        else if(pc==0){ /* 如果是子进程 */
              sleep(10); /* 睡眠10秒 */
              exit(0);
        }
        /* 如果是父进程 */
       do{
              //请添加代码，让父进程等待子进程，如果没有子进程退出，立即返回。


              /* 请补充代码，如果没有收集到已经退出的子进程的处理过程 */
               if(.... ){ 
                  printf("No child exited\n");
                   sleep(1);
               }
               
	//请添加代码，补充while中的内容，如果没有收集到子进程退出，就回去继续尝试
        }while(...); 


        if(pr==pc)
               printf("successfully get child %d\n", pr);
        else
               printf("some error occured\n");
}
