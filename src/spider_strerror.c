#include <spider.h>

//错误处理
int spider_strerror(const char *errstr, int exitcode)
{
    perror(errstr);
    exit(exitcode);
}