/*
 * svr.c
 * UDP Server
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
        "\tserver {listen_port}\n");
}

int main(int argc, char* argv[]) {
    char buf[BUFSIZE], buf2[BUFSIZE], file_path[256];
    struct msg* m;
    char *ip, *port;
    FILE* file = NULL;
    struct sockaddr_in server_addr, client_addr;
    int serversock;
    int ret = 0;
    int addrlen;
    int msglen;
    time_t start_time, end_time;

    if (argc < 2) {
        print_usage();
        return -1;
    }

    port = argv[1];
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(port));

    serversock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // UDP
    if (serversock < 0) {
        printf("socket create error=%d\n", errno);
        ret = -2;
        goto exit3;
    }
    //请增加代码，使用bind函数进行绑定
    if (.....) {
        printf("bind error=%\n", errno);
        ret = -3;
        goto exit2;
    }

    //创建MSG_ACK消息
    m = (struct msg*)buf2;
    m->type = MSG_ACK;
    m->data_len = 0;

    m = (struct msg*)buf;
    addrlen = sizeof(struct sockaddr_in);
    while (1) {
        //请增加代码，使用recvfrom函数接收消息
        msglen = 

        //请增加代码，使用sendto函数回复MSG_ACK
        

        //处理消息
        if (msglen <= 0) {
            printf("recv error\n");
            goto exit1;
        }

        if (m->type == MSG_FILENAME) {
            start_time = time(NULL);

            //获取文件名
            memcpy(file_path, m->data, m->data_len);
            file_path[m->data_len] = 0;
            //打开文件
            file = fopen(file_path, "w");
            if (file == NULL) {
                printf("fopen error=%d\n", errno);
                ret = -6;
                goto exit2;
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
    }

exit0:
    fflush(file);
    end_time = time(NULL);
    printf("Use time: %ld s\n", end_time - start_time);

exit1:
    fclose(file);

exit2:
    close(serversock);

exit3:
    return ret;
}
