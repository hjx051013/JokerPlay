#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>

#define EPOLLSIZE 500
#define MAX_EVENT_NUM 20
#define ACTIVE_EV_NUM 100
#define IP_MAX_LEN    128
#define NAME_MAX_LEN  64
#define PWD_MAX_LEN   32
#define BUF_LEN       256
typedef enum tagMsgType {
	REGISTER = 0,
	LOGIN,
	ROOMIN,
	READY,
	LANDLORDGRAB,
	CARDPLAY
} MSG_TYPE_E;

typedef struct tagMsgHead {
	uint32 type;
	uint32 msgLen;
} MSG_HEAD_S;

typedef struct tagUserInfo {
	char ascName[NAME_MAX_LEN];
	char ascPwd[PWD_MAX_LEN];
} USER_INFO_S;


FILE* userfp = NULL;

/* 在efd对fd进行op操作，其中fd对应的epoll_event的events字段为events */
void updateEvents(int efd, int fd, int events, int op)
{
    struct epoll_event ev;
    int r;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    printf("%s fd %d events read %d write %d\n", op == EPOLL_CTL_MOD ? "mod" : "add", fd, ev.events & EPOLLIN, ev.events & EPOLLOUT);

    r = epoll_ctl(efd, op, fd, &ev);
    exit_if(r < 0);
}


int createEpollListen(int listenfd)
{
    int ret;
    int epollfd;
    struct epoll_event ev;

    epollfd = epoll_create(EPOLLSIZE);
    exit_if(epoll_fd < 0);

   	updateEvents(epoll_fd, listenfd, EPOLLIN, EPOLL_CTL_ADD);

    return epollfd;
}

void handleAccept(int efd, int lfd)
{
    struct sockaddr_in connAddr;

    int connfd = accept(lfd, (struct sockaddr *)&connAddr, sizeof(struct sockaddr_in));
    exit_if(connfd);
    printf("accept a connnection from %s\n", inet_ntoa(connAddr.sin_addr));
    setNonBlock(connfd);
    updateEvents(efd, connfd, EPOLLIN, EPOLL_CTL_ADD);
}

void handleRead(int efd, int fd)
{
    /*先读消息头*/

    /*再读消息体*/

}

int loopOnce(int efd, int lfd, int waitms)
{
    int activeFd;
    int events;
    struct epoll_event activeEvs[MAX_EVENT_NUM];

    int nums = epoll_wait(efd, activeEvs, MAX_EVENT_NUM, waitms);
    for(int i = 0; i < nums; i++) {
        activeFd = activeEvs[i].data.fd;
        events = activeEvs[i].events;
        if(events & (EPOLL_IN | EPOLL_ERR)) {
            if(activeFd == lfd) {
                handleAccept(efd, lfd);
            } else {
                handleRead(efd, fd);
            }
        }
    }
}

void outputHelp()
{
    printf("usage:\n"
            "\t-p, --port        the port listened on\n"
            "\t-i, --ipAllow     the ip allowed connection this server (default 0.0.0.0)\n"
            "\t-h, --help        give this help list\n")
}

int serverInit()
{
	int ret;
	char buf[BUF_LEN];

	userfp = fopen("/tmp/users.txt",a+);
	exit_if(userfp==NULL);



}
int main(int argc, char *argv[])
{
    char *optstr = "hi:p:";
    char ipAllow[128];
    int opt;
    int ret;
    int port = -1;;
    int listenfd;
    int epollfd;
    struct option opts[] = {
        {"ipAllow", 1, NULL, 'i'},
        {"port", 1, NULL, 'p'},
        {"help", 0, NULL, 'h'}
    };

    memset(ipAllow, 0, 128);
    while((opt = getopt_long(argc, argv, optstr, opts, NULL)) != -1) {
        switch(opt) {
            case 'h':
                outputHelp();
                return 0;
            case 'i':
                strncpy(ipAllow, optarg, IP_MAX_LEN);
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case '?':
                if(strchr(optstr, optopt) == NULL){
                    fprintf(stderr, "unknown option '-%c'\n", optopt);
                }else{
                    fprintf(stderr, "option requires an argument '-%c'\n", optopt);
                }
                return 1;
        }
    }
    if(port < 0) port  = PORT;
    if(strlen(ipAllow) == 0) strcpy(ipAllow,"0.0.0.0");
	serverInit();
    listenfd = createSocketListen(port, ipAllow);
    setNonBlock(listenfd);
    epollfd = createEpollListen(listenfd)
    for(;;) {
        loopOnce(epollfd, listenfd, 10000);
    }

    return 0;
}