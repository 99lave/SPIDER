#include <spider.h>

//网络初始化
int spider_net_init(void)
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        spider_strerror("sockfd create error", 1);
    }
    struct sockaddr_in myaddr;
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = MYPORT;
    inet_pton(AF_INET, MYIP, &myaddr.sin_addr.s_addr);
    // 绑定
    // if(bind(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr)) == -1)
    //     spider_strerror("bind call failed",1);

    printf("spider running...\n<step 1>net init success...\n");
    
    return sockfd;
}