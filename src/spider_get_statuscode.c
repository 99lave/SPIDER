#include "spider.h"

//获取回复状态码
int spider_get_statuscode(char *response_head)
{
    int code;
    char status_code[100];
    bzero(status_code, 100);

    // HTTP/1.1 200 ok
    regex_t reg;
    regmatch_t match[2];

    regcomp(&reg, "HTTP/1.1 \\([^\r\n]\\+\\?\r\n\\)", 0);
    if ((regexec(&reg, response_head, 2, match, 0)) == 0)
    {
        snprintf(status_code, match[1].rm_eo - match->rm_so + 1, "%s", response_head + match[1].rm_so);

        sscanf(status_code,"%d ",&code);
        regfree(&reg);
        return code;
    }
    regfree(&reg);
    return -1;
}