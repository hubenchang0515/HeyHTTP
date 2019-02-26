#include "HttpRequest.h"
#include "HttpResponse.h"
#include <iostream>

using namespace heyhttp;

int main()
{
    HttpRequest request;
    request.parse("GET /index.php?id=10&gcc=7.8 HTTP/1.1\n"
                    "Host: www.kurukurumi.com\n"
                    "Connection: keep-alive\n"
                    "Cache-Control: max-age=0\n"
                    "Upgrade-Insecure-Requests: 1\n"
                    "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.109 Safari/537.36\n"
                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\n"
                    "Accept-Encoding: gzip, deflate, br\n"
                    "Accept-Language: zh-CN,zh;q=0.9\n");
    std::cout << request.dump() << std::endl;

    HttpResponse response;
    std::cout << response.dump() << std::endl;

    return 0;
}