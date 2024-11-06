#include<pthread.h>
#include <unistd.h>
#include<stdio.h>

#include<errno.h>

#include<stdlib.h>

#include<string.h>

void * thread_start(void * arg) {
  printf("子线程在运行\n");
  return 0;
}
int main() {
  pthread_attr_t attr;
  pthread_t thread;

  //请添加代码，设置新创建的线程为PTHREAD_CREATE_DETACHED，若失败则退出
  if (                      ||
                            ||
  
  ) {
    fprintf(stderr, "fault!\n");
    return 1;
  }

  if (pthread_join(thread, 0)) {
    fprintf(stderr, "成功返回\n%s\n", strerror(errno));
  } else {
    fprintf(stderr, "返回失败\n");
    return 2;
  }
  sleep(1);

  return 0;
}
