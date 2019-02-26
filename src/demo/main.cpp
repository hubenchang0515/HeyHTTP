/* This demo can only work in Linux */

#include "../HttpRequest.h"
#include "../HttpResponse.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace heyhttp;
using std::string;

ssize_t send(int sockFd, const string& data)
{
    return write(sockFd, data.data(), data.length());
}


ssize_t recv(int sockFd, string& data)
{
    char buff[1024];
    data = "";
    ssize_t ret = 0;
    ssize_t current = 1023;
    while(current == 1023)
    {
        current = read(sockFd, buff, 1023);
        buff[current] = 0;
        data.append(buff, current);
        ret += current;
    }

    return ret;
}
int main()
{
    int sock2Listen = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(80);
    if(-1 == bind(sock2Listen,(struct sockaddr*)&addr,sizeof(addr)))
    {
        std::cout << "bind error" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return 1;
    }

    int on = 1;
    setsockopt(sock2Listen, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    on = 1;
    setsockopt(sock2Listen, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    if(-1 == listen(sock2Listen, 10))
    {
        std::cout << "listen error" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return 1;
    }


    HttpRequest request;
    HttpResponse response;
    int sock2Http = 0;
    while(true)
    {
        sock2Http = accept(sock2Listen, nullptr, nullptr);
        if(sock2Http == -1)
        {
            std::cout << "accept error" << std::endl;
            std::cout << strerror(errno) << std::endl;
            close(sock2Listen);
            return 1;
        }

        string data;
        recv(sock2Http, data);
        request.parse(data);
        string url = "." + request.getUrl();
        if(url.back() == '/')
        {
            url += "index.html";
        }
        int fd = open(url.c_str(), O_RDONLY);
        if(fd < 0)
        {
            response.setState("404");
            response.setInfo("Not Found");
        }
        else
        {
            recv(fd, data);
            response.setState("200");
            response.setInfo("OK");
            response.setBody(data);
        }

        send(sock2Http, response.dump());
        close(sock2Http);

        std::cout << request.getMethod() << " " << request.getUrl() << " : " << response.getState() << std::endl;
    }


    return 0;
}