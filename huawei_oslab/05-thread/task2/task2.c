#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

//请添加代码，创立用于线程间同步的标志变量flag

void * thread_function(void * arg);

int main() {
  int res;

  pthread_t a_thread;

  void * thread_result;

  int count = 1;

//请添加代码，使用pthread_create函数创建新线程
  res = 

  if (res != 0) {

    perror("Thread creation failed");

    exit(EXIT_FAILURE);

  }

  while (count++ <= 20) {

//请添加代码，检查flag变量的值
    if (...) {

      printf("1");

      flag = 2;

    } else {

      sleep(1);

    }

  }

  printf("\nWaiting for thread to finish...\n");

//请添加代码，使用pthread_join函数等待新线程结束
  res = 

  if (res != 0) {

    perror("Thread join failed");

    exit(EXIT_FAILURE);

  }

  exit(EXIT_SUCCESS);

}

void * thread_function(void * arg) {
  int count = 1;

  while (count++ <= 20) {

    if (flag == 2) {

      printf("2");

      flag = 1;

    } else {

      sleep(1);

    }

  }
}
