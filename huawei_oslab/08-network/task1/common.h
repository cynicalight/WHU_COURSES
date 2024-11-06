// common.h

#ifndef COMMON_H
#define COMMON_H

#define QUESIZE 4
#define BACKLOG 64
#define BLKSIZE 2048
#define BUFSIZE 2056

#define MSG_FILENAME 1
#define MSG_CONTENT 2
#define MSG_ACK 3
#define MSG_DONE 4
#define MSG_EXCEPTION 5

struct msg {
  int32_t type;
  int32_t data_len;
  char data[];
};

#endif // COMMON_H