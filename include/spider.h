#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h> //dns, gethostbyname
#include <string.h>
#include <regex.h> //正则表达式

#define MYIP ""
#define MYPORT 8080
#define TRUE 1
#define FALSE 0
#define BUFSIZE 1500
#define IPSIZE 16
#define HTTPS 443
#define HTTP 80

typedef struct
{
    char origin_url[8192];  //原始url
    char domain[1024];      //域名
    char save_path[1024];   //资源存储路径
    char file_name[1024];   //资源名称
    char server_ip[IPSIZE]; //公网ip
    int http_type;          //协议类型 0(http) 1(https)
    int server_port;        // 80 or 443
} url_t;

int spider_strerror(const char *errstr, int exitcode); //错误处理

int spider_net_init(void); //网络初始化

int spider_analytical_url(url_t *u); //解析url

int spider_connect_web(url_t *u,int sockfd); //链接web服务器

int spider_create_requesthead(char* request_head, url_t node); //创建请求头

int spider_get_statuscode(char* response_head); //获取回复状态码

int spider_download(int webfd, char* request_head, url_t node); //下载回复包体内容