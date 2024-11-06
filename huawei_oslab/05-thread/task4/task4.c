#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int tickNo;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void * thread_start(void * arg) {
  for (; tickNo < 30;) {
//请添加代码，使用线程互斥锁加锁
 
    printf("Child Get Tick%d\n", ++tickNo);

//请添加代码，解锁
    

    sleep(1);
  }

  return 0;
}

int main() {
  pthread_t tid;

  pthread_create( & tid, NULL, thread_start, NULL);

  for (; tickNo < 30;) {

 //请添加代码，加锁

    printf("Main Get Tick%d\n", ++tickNo);

 //请添加代码，解锁

    sleep(1);
  }

 //请添加代码，销毁互斥锁
  


  return 0;
}
