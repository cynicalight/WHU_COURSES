/*
 * svr.c
 * TCP Server
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"

char* bufs[QUESIZE];
volatile int head;
volatile int rear;
sem_t count, empty_count;

void* work(void* args) {
    struct msg* m;
    char file_path[256];
    FILE* file = NULL;
    time_t start_time, end_time;

    while (1) {
        sem_wait(&count);

        m = (struct msg*)bufs[head];  //获得缓冲区

        //处理消息
        if (m->type == MSG_FILENAME) {
            start_time = time(NULL);

            //获取文件名
            memcpy(file_path, m->data, m->data_len);
            file_path[m->data_len] = 0;
            //打开文件
            file = fopen(file_path, "w");
            if (file == NULL) {
                printf("fopen error=%d\n", errno);
                return NULL;
            }
        } else if (m->type == MSG_CONTENT) {
            fwrite(m->data, 1, m->data_len, file);
        } else if (m->type == MSG_DONE) {
            printf("MSG_DONE\n");
            goto exit0;
        } else if (m->type == MSG_EXCEPTION) {
            printf("MSG_EXCEPTION\n");
            goto exit0;
        }

        //更新队列状态
        head = (head + 1) % QUESIZE;
        sem_post(&empty_count);
    }
exit0:
    fflush(file);
    end_time = time(NULL);
    printf("Use time: %ld s\n", end_time - start_time);
    fclose(file);
}

void print_usage() {
    printf(
        "usage:\n"
        "\tserver {listen_port}\n");
}

int main(int argc, char* argv[]) {
    char buf[BUFSIZE];
    char *ip, *port;
    struct msg* m;
    struct sockaddr_in server_addr, client_addr;
    int listensock, clientsock;
    int ret = 0;
    int addrlen;
    int datalen;
    int headlen;
    int i = 0;
    pthread_t worker;
    int alive = 1;

    if (argc < 2) {
        print_usage();
        return -1;
    }

    port = argv[1];

    head = 0;
    rear = 0;

    //申请缓冲区
    for (i = 0; i < QUESIZE; i++) {
        bufs[i] = malloc(BUFSIZE);
        if (bufs[i] == NULL) {
            printf("malloc failed\n");
        }
    }

    sem_init(&count, 0, 0);
    sem_init(&empty_count, 0, QUESIZE);

    ret = pthread_create(&worker, NULL, work, NULL);
    if (ret != 0) {
        printf("pthread_create error=%d\n", ret);
        ret = -8;
        goto exit3;
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(port));

    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listensock < 0) {
        printf("socket create error=%d\n", errno);
        ret = -2;
        goto exit3;
    }
    //请增加代码，使用bind函数绑定套接字
    if (...) {

        printf("bind error=%\n", errno);
        ret = -3;
        goto exit2;
    }

    //请增加代码，使用listen函数监听
    if (...) {
        printf("listen error=%d\n", errno);
        ret = -4;
        goto exit2;
    }

    addrlen = sizeof(struct sockaddr_in);
    clientsock = accept(listensock, (struct sockaddr*)&client_addr, &addrlen);
    if (clientsock < 0) {
        printf("accept error=%d\n", errno);
        ret = -5;
        goto exit2;
    }

    printf("--%s:%d--\n", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    //接收消息
    while (alive) {
        sem_wait(&empty_count);

        m = (struct msg*)bufs[rear];  //获得空闲缓冲区

        //请增加此处代码，使用 recv函数接收消息头
        headlen = recv(....);
        if (headlen <= 0) {
            goto exit1;
        }

        //接收消息数据
        if (m->data_len > 0) {
            datalen = 0;
            while (datalen < m->data_len) {
                //请增加此处代码，使用 recv函数接收消息
                datalen += recv(....);
            }
        }

        //更新队列状态
        rear = (rear + 1) % QUESIZE;
        sem_post(&count);
    }

    pthread_join(worker, NULL);

exit1:
    close(clientsock);

exit2:
    close(listensock);

exit3:
    sem_destroy(&count);
    sem_destroy(&empty_count);

    //释放缓冲区
    for (i = 0; i < QUESIZE; i++) {
        free(bufs[i]);
    }

    return ret;
}
