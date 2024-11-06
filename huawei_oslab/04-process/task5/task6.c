#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()

{

       int status;

       pid_t pc,pr;

       
        pc=fork();

        if(pc<0) /* 如果出错 */

               printf("error ocurred!\n");

        else if(pc==0){ /* 子进程 */

               printf("This is child process with pid of %d.\n",getpid());

               //请添加代码，使子进程返回3.


        }

        else{ /* 父进程 */

              //请添加代码，等待子进程结束，并读取返回的状态值status


              // 请添加代码，通过宏判定status返回值 

               if(……){ 
                     /*  如果正常返回 */

                       printf("the child process %d exit normally.\n",pr);

                       printf("the return code is %d.\n",WEXITSTATUS(status));

               }else /* 如果不正常返回 */

                   printf("the child process %d exit abnormally.\n",pr);

        }

}
