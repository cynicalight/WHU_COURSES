#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define REPEATS (5) /* count of production/consumption */
#define MAX_BUFFER_SIZE (3)

typedef struct {
  int bottom;
  int top;

  int data[MAX_BUFFER_SIZE];
}
STRUCT_BUFFER;

STRUCT_BUFFER * pBuffer = NULL;

/* Define speed of consumer/producer, change them as u like */
#define PRODUCER_SPEED (1) /* 1/sec */
#define CONSUMER_SPEED (5) /* 1/2sec */

int sem_consume; /* consumer sem */
int sem_produce; /* producer sem */
int shm_buffer; /* shared buffer */

#define FLAG (IPC_CREAT | S_IRWXU)

/* Init semphores & shared buffer */
void init() {
  union semun {
    int val;
    struct semid_ds * buf;
    unsigned short * array;
  }
  arg;

//请添加代码，使用shmget函数创建共享内存段，编号为0x1111
  shm_buffer = 
  pBuffer = shmat(shm_buffer, 0, 0);
  memset(pBuffer, 0, sizeof(STRUCT_BUFFER));

//请添加代码，使用semget函数创建消费者者信号量，编号为0x2222
  sem_consume = 

  arg.val = 0;
  if (semctl(sem_consume, 0, SETVAL, arg) < 0) {
    perror("Consumer");
    exit(1);
  }

  //请添加代码，使用semget函数创建生产者者信号量,编号为0x3333
  sem_produce =

  arg.val = MAX_BUFFER_SIZE;
  if (semctl(sem_produce, 0, SETVAL, arg) < 0) {
    perror("Producer");
    exit(1);

  }
}

/* destroy semphores & shared buffer */
void deinit() {
  shmctl(shm_buffer, IPC_RMID, NULL);
  semctl(sem_consume, 0, IPC_RMID);
  semctl(sem_produce, 0, IPC_RMID);
}

int main() {
  int pid, i;
  struct sembuf sbuf;

  init();

  pid = fork();

  if (pid > 0) {
    /* parent process, consumer */
    for (i = 0; i < REPEATS; i++) {
      /* Try decrementing 1 from consumer */
      sbuf.sem_num = 0;
      sbuf.sem_op = -1;
      sbuf.sem_flg = 0;
      //请添加代码，使用semop函数改变消费者信号量的值


      /* OK */
      system("date |awk  '{print $5}' ");
      printf("Consumer get %6d,pos=%d\n", pBuffer -> data[pBuffer -> bottom], pBuffer -> bottom);
      pBuffer -> bottom = (pBuffer -> bottom + 1) % MAX_BUFFER_SIZE;

      /* Try incrementing 1 to producer */
      sbuf.sem_op = 1;
      semop(sem_produce, & sbuf, 1);

      sleep(CONSUMER_SPEED);
    }
    wait(0);
    shmdt(pBuffer);
  } else if (pid == 0) {
    //srand(time(NULL));
    //printf("time is %ld\n",time(NULL));
    /* child process, producer */
    for (i = 0; i < REPEATS; i++) {
      /* Try decrementing 1 from producer */
      sbuf.sem_num = 0;
      sbuf.sem_op = -1;
      sbuf.sem_flg = 0;
      //请添加代码，使用semop函数改变生产者信号量的值

      /* OK */
      pBuffer -> data[pBuffer -> top] = (rand() % 100) + i + 1;
      system("date |awk  '{print $5}' ");
      printf("Producer put %6d,pos=%d\n", pBuffer -> data[pBuffer -> top], pBuffer -> top);
      pBuffer -> top = (pBuffer -> top + 1) % MAX_BUFFER_SIZE;

      /* Try incrementing 1 to consumer */
      sbuf.sem_op = 1;
      semop(sem_consume, & sbuf, 1);

      sleep(PRODUCER_SPEED);
    }
    shmdt(pBuffer);
    exit(0);
  }

  deinit();
  return 0;
}
