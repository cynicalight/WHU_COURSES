#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int glob = 6;
char buf[] = "a write to stdout\n";
int main()
{
    int var;
    pid_t pid;
    var = 88;
    fprintf(stderr, "%s", buf);
    printf("before fork\n");
    //请添加代码，创建一个进程
    //if(( ……   ) < 0 )
    {
        //创建进程失败
        fprintf(stderr, "fork error\n");
    }
   // 请添加代码，补充子进程的处理
   // else if(…… )
    {
       //
       //请添加代码，对两个变量glob和var,进行加1操作     
       
        printf("child process\n");
        printf("pid = %d, father pid = %d, glob = %d, var = %d\n", getpid(), getppid(), glob, var);
        exit(0);
    }
    else
    {
        //请添加代码，让父进程休眠一段时间。
        
        printf("father process\n");
        printf("pid = %d, father pid = %d, glob = %d, var = %d\n", getpid(), getppid(), glob, var);
    }
    return 0;
}
