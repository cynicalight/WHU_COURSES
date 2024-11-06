/*
 * cli.c
 * UDP Client
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

void print_usage() {
    printf(
        "usage:\n"
        "\tclient {server_ip} {server_port} {file_path}\n");
}

int main(int argc, char* argv[]) {
    char buf[BUFSIZE], buf2[BUFSIZE];
    struct msg* m;
    char *ip, *port, *file_path, *file_name, *tmp;
    FILE* file;
    int clientsock;
    struct sockaddr_in server_addr;
    int ret = 0;
    int datalen;
    int msglen;
    time_t start_time, end_time;
    int alive = 1;

    if (argc < 4) {
        print_usage();
        return -1;
    }

    ip = argv[1];
    port = argv[2];
    file_path = argv[3];  //文件完整路径
    //从文件完整路径中截取文件名
    tmp = strrchr(file_path, '/');
    file_name = tmp ? (tmp + 1) : file_path;

    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("fopen error=%d\n", errno);
        return -5;
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(atoi(port));

    //请增加代码，使用socket函数完成client请求
    clientsock =   // UDP

    if (clientsock < 0) {
        printf("socket create error=%d\n", errno);
        ret = -2;
        goto exit2;
    }

    start_time = time(NULL);

    //创建并发送MSG_FILENAME
    m = (struct msg*)buf;
    m->type = MSG_FILENAME;
    m->data_len = strlen(file_name);
    memcpy(m->data, file_name, m->data_len);
    msglen = sizeof(struct msg) + m->data_len;
    //请增加代码，使用send函数发送消息
    if (.....) {
        printf("send MSG_FILENAME error=%d\n", errno);
        ret = -4;
        goto exit1;
    }
    //接收回复
    recvfrom(clientsock, buf2, BUFSIZE, 0, NULL, NULL);

    //创建并发送MSG_CONTENT
    m = (struct msg*)buf;
    m->type = MSG_CONTENT;
    while (alive) {
        //读文件
        datalen = fread(m->data, 1, BLKSIZE, file);
        if (datalen <= 0) {
            if (feof(file)) {  //文件结束
                printf("send MSG_DONE\n");
                m->type = MSG_DONE;
                m->data_len = 0;
            } else if (ferror(file)) {  //读文件错误
                printf("fread error=%d\n", errno);
                ret = -6;
                m->type = MSG_EXCEPTION;
                m->data_len = 0;
            }
            alive = 0;
        } else {
            m->data_len = datalen;
        }

        //发送消息
        msglen = sizeof(struct msg) + m->data_len;
        if (sendto(clientsock, buf, msglen, 0, (struct sockaddr*)&server_addr,
                   sizeof(struct sockaddr_in)) < 0) {
            printf("send MSG_CONTENT error=%d\n", errno);
            ret = -4;
            goto exit1;
        }
        
        //请增加代码，使用recvfrom函数接收回复
        
    }

exit0:
    end_time = time(NULL);
    printf("Use time: %ld s\n", end_time - start_time);

exit1:
    close(clientsock);

exit2:
    fclose(file);
    return ret;
}
