/*
 * cli.c
 * TCP Client
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
    char *file_path, *file_name, *tmp;
    FILE* file;
    int alive = 1;
    int datalen;

    file_path = (char*)args;
    //从文件完整路径中截取文件名
    tmp = strrchr(file_path, '/');
    file_name = tmp ? (tmp + 1) : file_path;

    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("fopen error=%d\n", errno);
    }

    //创建MSG_FILENAME
    sem_wait(&empty_count);
    m = (struct msg*)bufs[rear];  //获得空闲缓冲区
    m->data_len = strlen(file_name);
    m->type = MSG_FILENAME;
    memcpy(m->data, file_name, m->data_len);
    //更新队列状态
    rear = (rear + 1) % QUESIZE;
    sem_post(&count);

    while (alive) {
        sem_wait(&empty_count);

        m = (struct msg*)bufs[rear];  //获得空闲缓冲区

        //读文件
        datalen = fread(m->data, 1, BLKSIZE, file);
        if (datalen <= 0) {
            m->data_len = 0;
            if (feof(file)) {  //文件结束
                m->type = MSG_DONE;
            } else if (ferror(file)) {  //读文件错误
                printf("fread error=%d\n", errno);
                m->type = MSG_EXCEPTION;
            }
            alive = 0;
        } else {
            m->data_len = datalen;
            m->type = MSG_CONTENT;
        }
        //更新队列状态
        rear = (rear + 1) % QUESIZE;
        sem_post(&count);
    }

    fclose(file);
}

void print_usage() {
    printf(
        "usage:\n"
        "\tclient {server_ip} {server_port} {file_path}\n");
}

int main(int argc, char* argv[]) {
    struct msg* m;
    char *ip, *port, *file_path;
    int clientsock;
    struct sockaddr_in server_addr;
    int ret = 0;
    int msglen;
    time_t start_time, end_time;
    int i = 0;
    pthread_t worker;

    if (argc < 4) {
        print_usage();
        return -1;
    }

    ip = argv[1];
    port = argv[2];
    file_path = argv[3];  //文件完整路径

    head = 0;
    rear = 0;

    for (i = 0; i < QUESIZE; i++) {
        bufs[i] = malloc(BUFSIZE);
        if (bufs[i] == NULL) {
            printf("malloc failed\n");
        }
    }

    sem_init(&count, 0, 0);
    sem_init(&empty_count, 0, QUESIZE);

    ret = pthread_create(&worker, NULL, work, file_path);
    if (ret != 0) {
        printf("pthread_create error=%d\n", ret);
        ret = -8;
        goto exit2;
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(atoi(port));

    //请增加此处代码，使用socket函数完成client请求
    clientsock= 
    if (clientsock < 0) {
        printf("socket create error=%d\n", errno);
        ret = -2;
        goto exit2;
    }
    //请增加此处代码，使用connect函数完成连接
    if (...) {
        printf("connect error=%d\n", errno);
        ret = -3;
        goto exit1;
    }

    start_time = time(NULL);

    while (1) {
        sem_wait(&count);

        m = (struct msg*)bufs[head];  //获得缓冲区
        //发送消息
        msglen = sizeof(struct msg) + m->data_len;
        
        //请增加此处代码，使用send函数完成发送消息
        if (...) {

            printf("send error=%d\n", errno);
            ret = -4;
            goto exit1;
        }
        if (m->type == MSG_DONE || m->type == MSG_EXCEPTION) {
            printf("send MSG_DONE\n");
            goto exit0;
        }

        //更新队列状态
        head = (head + 1) % QUESIZE;
        sem_post(&empty_count);
    }

exit0:
    end_time = time(NULL);
    printf("Use time: %ld s\n", end_time - start_time);

exit1:
    close(clientsock);

exit2:
    sem_destroy(&count);
    sem_destroy(&empty_count);

    //释放缓冲区
    for (i = 0; i < QUESIZE; i++) {
        free(bufs[i]);
    }

    return ret;
}