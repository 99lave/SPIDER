#include <spider.h>

int main(){
    const char* url= "http://i0.hdslb.com/bfs/article/1f3dac966c2d14382cea72c7bed522f61e0c6f4f.jpg";
    int webfd;
    char reqhead[4096];
    url_t node;
    //bzero(&node,sizeof(node));
    strcpy(node.origin_url,url);
    webfd = spider_net_init();
    spider_analytical_url(&node);
    spider_connect_web(&node,webfd);
    spider_create_requesthead(reqhead,node);
    spider_download(webfd,reqhead,node);
    
    return 0;
}
