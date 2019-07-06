#ifndef __SOCKETCOMM_H__
#define __SOCKETCOMM_H__

int createSocketListen(int port, char *pscAddr);
void socketRecv(int fd, char *pscBuf, int uiBufLen);

void socketSend(int siFd, char *pscMsgBuf, uint32 uiBufLen);

#endif
