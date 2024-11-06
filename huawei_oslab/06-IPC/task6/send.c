#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX_TEXT 512

struct msg_st {
  long int msg_type;
  char text[MAX_TEXT];
};

int main() {
  int running = 1;
  struct msg_st data;
  char buffer[BUFSIZ];
  int msgid = -1;

  //请添加代码，使用msgget建立消息队列
  msgid = 

  if (msgid == -1) {
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  //向消息队列中写消息，直到写入end
  while (running) {
    //输入数据
    printf("Enter some text: ");
    fgets(buffer, BUFSIZ, stdin);
    data.msg_type = 1; //注意2
    strcpy(data.text, buffer);
    //请添加代码，使用msgsnd函数向队列发送数据
    if (msgsnd(....) == -1) {
      
      fprintf(stderr, "msgsnd failed\n");
      exit(EXIT_FAILURE);
    }
    //输入end结束输入
    if (strncmp(buffer, "end", 3) == 0)
      running = 0;
    sleep(1);
  }
  exit(EXIT_SUCCESS);
}
