#ifndef __SOCKETCOMM_H__
#define __SOCKETCOMM_H__

int createSocketListen(int port, char *pscAddr);
void setNonBlock(int fd);

#endif