#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include "basic.h"
#include "socketComm.h"

#define BACKLOG 200

/*����һ��socket������pscAddr��port��Ӧ��ip�Ͷ˿� */
int createSocketListen(int port, char *pscAddr)
{
    int ret;
    int sockfd;
    struct sockaddr_in my_addr;

    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    ret = inet_pton(AF_INET, pscAddr, &(my_addr.sin_addr.s_addr)); /*��ip�ַ���ת��stuct in_addr���� */
    exit_if(ret < 0);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(sockfd < 0);
    ret = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    exit_if(ret < 0);
    ret = listen(sockfd,BACKLOG);
    exit_if(ret < 0);
    return sockfd;
}

/*��fd����uiBufLen���ֽڵ�pscBuf�У�����ղ���uiBufLen���ֽڣ�����fd������Ϊ���������ᱨ�� */
void socketRecv(int fd, char *pscBuf, int uiBufLen)
{
    int recvedLen = 0;
    int leftLen;
    int recvTempLen;
    int bufLen = (int)uiBufLen;

    do {
        leftLen = bufLen - recvedLen;
        do {
            recvTempLen = recv(fd, pscBuf+recvedLen, lenLeft, 0);
        } while ((recvTempLen == -1) && (errno == EINTR));
        exit_if(recvTempLen == -1);
        if(recvTempLen == 0) {
            printf("The fd has been closed");
            return;
        }
        recvedLen += recvTempLen;
    } while (recvedLen != bufLen);

}