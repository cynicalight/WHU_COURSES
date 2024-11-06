#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"

int main(int argc, char * agrv[]) {
  int pipe_fd;
  int res;
  char buffer[] = "hello world!";
  if (access(FIFO_NAME, F_OK) == -1) {
    res = mkfifo(FIFO_NAME, 0766);
    if (res != 0) {
      fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
      exit(EXIT_FAILURE);
    }
  }
  printf("Process %d opening FIFO O_WRONLY\n", getpid());

  //请添加代码，使用open函数打开有名（FIFO_NAME）管道
  pipe_fd = 

  printf("process write:the file's descriptor is %d\n", pipe_fd);
  if (pipe_fd != -1) {

    //请添加代码，使用write函数对管道进行写操作，写入buffer
    res = 

    if (res == -1) {

      fprintf(stderr, "Write error on pipe\n");
      exit(EXIT_FAILURE);
    }
    printf("Write date is %s, %d bytes is write\n", buffer, res);
    (void) close(pipe_fd);
  } else {
    exit(EXIT_FAILURE);
  }
  printf("Process %d finished\n", getpid());
  exit(EXIT_FAILURE);

  return 0;
}
