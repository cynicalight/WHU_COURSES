#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define SIZE 1024

typedef struct {
  char no[8];
  char name[8];
  double price;
} book;

int main(int argc, char ** argv) 
{
  int shm_id, i;
  key_t key;
  char temp[8];
  book * shmaddr;
  char pathname[30];
  book bookInfo[2];
  strcpy(bookInfo[0].no, "01");
  strcpy(bookInfo[0].name, "book1");
  strcpy(bookInfo[1].no, "02");
  strcpy(bookInfo[1].name, "book2");
  bookInfo[0].price = 10;
  bookInfo[1].price = 20;

  strcpy(pathname, "/tmp");

  key = ftok(pathname, 0x03);

  if (key == -1) {
    perror("ftok error");
    return -1;
  }

  printf("key=%d\n", key);

//请添加代码，使用shmget函数创建共享内存
  shm_id = 

  if (shm_id == -1) {
    perror("shmget error");
    return -1;
  }

  printf("shm_id=%d\n", shm_id);

//请添加代码，使用shmat函数将共享内存映射到进程地址空间
  shmaddr = 

  for (i = 0; i < 2; i++) {
    strncpy((shmaddr + i) -> no, bookInfo[i].no, sizeof(bookInfo[i].no));
    strncpy((shmaddr + i) -> name, bookInfo[i].name, sizeof(bookInfo[i].name));
    (shmaddr + i) -> price = bookInfo[i].price;
  }

//请添加代码，使用shmdt函数分离共享内存

  return 0;
}
