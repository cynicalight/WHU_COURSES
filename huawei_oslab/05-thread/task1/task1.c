#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void * thread_function(void * arg);
char message[] = "Hello World";
int main() {
  int res;

  pthread_t a_thread;

  void * thread_result;

//请添加代码，使用pthread_create创建新线程a_thread，线程函数为thread_function，参数为message
  res =

  if (res != 0) {
    perror("Thread creation failed!");

    exit(EXIT_FAILURE);

  }
  printf("Waiting for thread to finish...\n");

 //请添加代码，使用pthread_join等待新线程结束

  if (res != 0) {
    perror("Thread join failed!\n");

    exit(EXIT_FAILURE);

  }
  printf("Thread joined, it returned %s\n", (char * ) thread_result);

  printf("Message is now %s\n", message);

  exit(EXIT_FAILURE);

}
void * thread_function(void * arg) {
  printf("thread_function is running. Argument was %s\n", (char * ) arg);

  sleep(3);

  strcpy(message, "Bye!");


  //请添加代码，使用pthread_exit退出线程
  

}
