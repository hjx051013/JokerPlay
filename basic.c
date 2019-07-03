#include"basic.h"
#include<unistd.h>
#include<fcntl.h>

/*����fd��Ӧ���ļ�������״̬Ϊ������ */
void setNonBlock(int fd)
{
    int r;
    int flags = fcntl(fd, F_GETFL, 0);
    exit_if(flags < 0);
    r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    exit_if(r < 0);
}