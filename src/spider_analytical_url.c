#include <spider.h>

//解析url

int spider_analytical_url(url_t *node)
{
    int flag;     //遍历下标
    int j = 0;        //存储下标
    int start;    //起始下标
    int filesize = 0; //记录文件名长度   不初始化报错

    // 初始化node
    bzero(node->domain,sizeof(node->domain));
    bzero(node->file_name,sizeof(node->file_name));
    bzero(node->save_path,sizeof(node->save_path));
    bzero(node->server_ip,sizeof(node->server_ip));

    const char *http_array[] = {"http://", "https://", NULL};
    /*辨别http协议类型*/
    if (strncmp(node->origin_url, http_array[0], strlen(http_array[0])) == 0)
    {
        node->http_type = 0;
        node->server_port = HTTP;
        start = strlen(http_array[0]);
    }
    else
    {
        node->http_type = 1;
        node->server_port = HTTPS;
        start = strlen(http_array[1]);
    }

    /*获取域名*/
    for (flag = start; node->origin_url[flag] != '/'; flag++)
    {
        node->domain[j] = node->origin_url[flag];
        j++;
    }
    j = 0;
  
    /*获取文件名长度*/
    for (flag = strlen(node->origin_url); node->origin_url[flag] != '/'; flag--, filesize++);
 
    /*获取文件名*/
    for (flag = strlen(node->origin_url) - filesize + 1; node->origin_url[flag] != '\0'; flag++)
    {
        node->file_name[j] = node->origin_url[flag];
        j++;
    }
    j = 0;

    /*获取存储路径*/
    for (flag = start + strlen(node->domain); flag < strlen(node->origin_url) - filesize + 1; flag++)
    {
        node->save_path[j] = node->origin_url[flag];
        j++;
    }

    /*获取公网IP*/
    struct hostent* ent = NULL;
    if ((ent = gethostbyname(node->domain)) != NULL)
    {
        inet_ntop(AF_INET, ent->h_addr_list[0], node->server_ip, IPSIZE);
    }

    printf("<step 2> Analytical OriginURL[%s] SUCCESS!\nDomain:%s\nFile:%s\nType:%d\nPath:%s\nIP:%s\nPort:%d\n"
    ,node->origin_url,node->domain,node->file_name,node->http_type,node->save_path,node->server_ip,node->server_port);
    return 0;
}