#ifndef __BASIC_H__
#define __BASIC_H__
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define exit_if(r) \
    if(r) { \
        printf("%s:%d error msg %s\n", __FILE__, __LINE__, strerror(errno)); \
        exit(1); \
    }
#define OP_OK 0
#define OP_ERR -1
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
void setNonBlock(int fd);
#endif