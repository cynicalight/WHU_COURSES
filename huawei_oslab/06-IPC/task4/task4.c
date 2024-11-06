#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define SIZE 128

int main() {
  int fd[2];
  pid_t pid;
  char szout[SIZE];
  char szin[SIZE];
  printf("input str:\n");
  fgets(szin, 100, stdin);

  //请添加代码，使用pipe创建无名管道
  
  while ((pid = fork()) < 0);
  if (pid == 0) {
    //请添加代码，在子进程中关闭写端
    
    read(fd[0], szout, SIZE);
    fprintf(stdout, "I am child,out:%s\n", szout);
    exit(0);
  } else {

    close(fd[0]);
    //请添加代码，在父进程中关闭将数据写入写端

    printf("I am parent,in:%s\n", szin);
    sleep(1);
  }
  
  return 0;
}
