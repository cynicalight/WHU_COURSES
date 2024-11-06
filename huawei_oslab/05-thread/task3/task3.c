#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <semaphore.h>

#define SIZE 1024

void * thread_function(void * arg);

char buffer[SIZE];
sem_t sem;

int main() {
  int res;
  pthread_t a_thread;
  void * thread_result;

//请添加代码，使用sem_init函数初始化信号量sem，这里初始化为0，在进程的所有线程间共享
  res = 

  if (res != 0) {
    perror("Sem init failed");
    exit(EXIT_FAILURE);
  }

//请添加代码，使用pthread_create函数创建新线程
  res = 

  if (res != 0) {
    perror("Thread create failed");
    exit(EXIT_FAILURE);
  }

  printf("Input some text. Enter 'end' to finish\n");
    
  //请添加代码，主线程循环接收输入到buffer，通过信号量sem实现父子线程合作

  while (scanf("%s", buffer)) {

    if (strncmp("end", buffer, 3) == 0)
      break;
  }

  printf("\nWaiting for thread to finish...\n");

  //请添加代码，主线程等待子线程完成

  res =
  if (res != 0) {
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }

  printf("Thread join\n");

//请添加代码，主线程销毁信号量sem


  exit(EXIT_SUCCESS);
}

void * thread_function(void * arg) {
  //请添加代码，线程与主线程通过信号量sem，合作访问buffer，判断buffer是否为end，是则退出线程

  while (strncmp("end", buffer, 3) != 0) {
    printf("You input %d characters\n", strlen(buffer));
    
  }
  pthread_exit(NULL);
}
