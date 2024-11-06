#include <stdint.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>
#define SIZE 1024
int main(int argc, char *argv[])
{
    int shmid;
    char *shmaddr;
    struct shmid_ds buf;
    int flag = 0;
    int pid;

    // 添加代码，使用shmget函数创建共享内存
    shmid =

        if (shmid < 0)
    {
        perror("get shm  ipc_id error");
        return -1;
    }
    pid = fork();
    if (pid == 0)
    {
        // 添加代码，使用shmat函数使子进程连接共享内存
        shmaddr =

            if ((uintptr_t)shmaddr == (uintptr_t)-1)
        {
            perror("shmat addr error");
            return -1;
        }
        strcpy(shmaddr, argv[1]);
        printf("this is child.\nwrite argv[1] to shm.\nyour input string is \'%s\'\n", shmaddr);

        // 添加代码，使用shmdt函数分离共享内存

        return 0;
    }
    else if (pid > 0)
    {
        wait(NULL);

        // 添加代码，使用shmctl获取共享内存信息
        flag =

        if (flag == -1)
        {
            perror("shmctl shm error");
            return -1;
        }
        printf("\nthis is parent.\n");
        printf("the size of shared memory is %d bytes\n", buf.shm_segsz);
        printf("parent pid is %d\n", getpid());
        printf("chlid pid is %d\n", pid);
        shmaddr = (char *)shmat(shmid, NULL, 0);
        if ((uintptr_t)shmaddr == (uintptr_t)-1)
        {
            perror("shmat addr error");
            return -1;
        }
        printf("your input string is \'%s\'\n", shmaddr);

        shmdt(shmaddr);
        // 添加代码，使用shmctl函数删除共享内存
    }
    else
    {
        perror("fork error");
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
