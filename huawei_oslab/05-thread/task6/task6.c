#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

void * thread_function(void * arg);

int main() {
  int res;
  pthread_t a_thread;
  void * thread_result;

  res = pthread_create( & a_thread, NULL, thread_function, NULL);
  if (res != 0) {
    perror("Thread create failed!");
    exit(EXIT_FAILURE);
  }

  sleep(4);
  printf("Canceling thread...\n");

  //请添加代码，取消所创建的子线程a_thread

  res =
  if (res != 0) {
    perror("Thread cancel failed!");
    exit(EXIT_FAILURE);
  }

  printf("Waiting for thread to finished...\n");

  res = pthread_join(a_thread, & thread_result);
  if (res != 0) {
    perror("Thread join failed!");
    exit(EXIT_FAILURE);
  }

  printf("Thread canceled!");

  exit(EXIT_FAILURE);
}

void * thread_function(void * arg) {
  int i;
  int res;

  //请添加代码，设置本线程的可取消状态，为允许线程接收取消请求
  res = 
  if (res != 0) {
    perror("Thread setcancelstate failed!");
    exit(EXIT_FAILURE);
  }

//请添加代码，设置本线程的取消类型，设置为使得在接收到取消请求后，一直等待直到线程执行了一些函数后才采取行动
  res = 

  if (res != 0) {
    perror("Thread setcanceltype failed!");
    exit(EXIT_FAILURE);
  }

  printf("thread_function is running...\n");

  for (i = 0; i < 10; i++) {
    printf("Thread is still running (%d)...\n", i);
    sleep(1);
  }
  pthread_exit(0);
}
