#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  char no[8];
  char name[8];
  double price;
} book;

int main(int argc, char ** argv) 
{
  int shm_id, i;
  key_t key;
  book * shmaddr;
  char pathname[30];
  strcpy(pathname, "/tmp");
  key = ftok(pathname, 0x03);

  if (key == -1) {
    perror("ftok error");
    return -1;
  }

  printf("key=%d\n", key);

//添加代码，使用 shmget函数创建共享内存段，在这里key使用ftok创建的
  shm_id = 

  if (shm_id == -1) {
    perror("shmget error");
    return -1;
  }

  printf("shm_id=%d\n", shm_id);

//请添加代码，使用 shmat函数将共享内存映射到进程地址空间
  shmaddr =

  printf("Book Information:\n");

  for (i = 0; i < 2; i++) {
    printf("no:%s", ( * (shmaddr + i)).no);
    printf("   name:%s", ( * (shmaddr + i)).name);
    printf("   price:%f\n", ( * (shmaddr + i)).price);
  }

  if (shmdt(shmaddr) == -1) {
    perror("detach error");
    return -1;
  }
  
  if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
    perror("shmctl error");
    return -1;
  }

  return 0;
}
