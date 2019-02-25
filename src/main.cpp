#include "HttpRequest.h"
#include "HttpResponse.h"
#include <iostream>

using namespace heyhttp;

int main()
{
    HttpRequest request;
    request.setMethod("GET");
    request.setUrl("/");
    request.setHeader("User-Agent", "Plan C's HTTP Parser");
    request.setHeader("Host", "www.404.com");
    request.setBody("?name=bug&sex=unisex");
    std::cout << request.dump() << std::endl;

    HttpResponse response;
    std::cout << response.dump() << std::endl;

    return 0;
}