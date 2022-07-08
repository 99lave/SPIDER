#include "spider.h"

//下载回复包体内容
int spider_download(int webfd, char *request_head, url_t node)
{
    int code;
    char recv_buf[8192];
    char response_head[4096];
    bzero(recv_buf, 8192);
    bzero(response_head, 4096);
    size_t recvsize;
    char *pos = NULL;
    int fd;

    // 发送请求头
    send(webfd, request_head, strlen(request_head), 0);
    printf("<STEP 5> Send Request Head...\n");

    //第一次读取
    recvsize = recv(webfd, recv_buf, sizeof(recv_buf), 0);
    //查找分割线地址
    if ((pos = strstr(recv_buf, "\r\n\r\n")) == NULL)
    {
        printf("strstr call failed:not found!\n");
        close(webfd);
        return -1;
    }
    //提取响应头
    snprintf(response_head, pos - recv_buf + 4, "%s", recv_buf);
    printf("<STEP 6> Print Response Head:\n%s\n", response_head);

    //获取响应码
    if ((code = spider_get_statuscode(response_head)) == 200)
    {
        //创建文件
        printf("<STEP ?>STATUS_CODE %d\n", code);
        fd = open(node.file_name, O_RDWR | O_CREAT, 0664);
        //接受第一次响应体数据
        write(fd, pos + 4, recvsize - (pos - recv_buf + 4));
        //循环读取响应，写入文件

        while ((recvsize = recv(webfd, recv_buf, sizeof(recv_buf), 0)) > 0)
        {
            write(fd, recv_buf, recvsize);
            bzero(recv_buf, sizeof(recv_buf));
        }

        close(fd);
        printf("<STEP 7> Download Success...\n");
    }
    else
    {
        printf("<STEP ?>STATUS_CODE %d, Response Error!\n", code);
        close(webfd);
        return -1;
    }
    close(webfd);
    return 0;
}