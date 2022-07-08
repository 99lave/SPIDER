#include <spider.h>

//链接web服务器
int spider_connect_web(url_t *u,int sockfd){
    struct sockaddr_in webaddr;
    bzero(&webaddr,sizeof(webaddr));
    webaddr.sin_family = AF_INET;
    webaddr.sin_port = htons(u->server_port);
    inet_pton(AF_INET,u->server_ip,&webaddr.sin_addr.s_addr);

    if((connect(sockfd,(struct sockaddr*)&webaddr,sizeof(webaddr))) == -1){
        spider_strerror("connect webserver failed",1);
    }
    printf("<step 3>Connect Web success...\n");
    return 0;
} 