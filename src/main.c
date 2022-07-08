#include <spider.h>

int main(){
    const char* url= "http://up.enterdesk.com/photo/2012-3-2/enterdesk.com-B526ECADD33DBD367676A93E051BA1EC.jpg";
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
