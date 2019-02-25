#include "HttpRequest.h"
#include <iostream>

namespace heyhttp
{

using std::string;
using std::map;

/* Parse the HTTP request first line */
bool HttpRequest::parseFirstLine(const string& httpString, bool isDebug)
{
    size_t pos1 = httpString.find(' ');
    size_t pos2 = httpString.rfind(' ');
    
    this->_method = httpString.substr(0, pos1);
    this->_version = httpString.substr(pos2 + 1);
    this->_url = httpString.substr(pos1 + 1, pos2 - pos1 - 1);

    if(this->_version != "HTTP/1.1")
    {
        logError("Only support HTTP/1.1 (%s).\n", httpString.c_str());
    }

    if(isDebug)
    {
        std::cout << this->_method << " " 
                    << this->_url << " " 
                    << this->_version 
                    << std::endl;
    }
}

/* Get request method */
string HttpRequest::getMethod()
{
    return this->_method;
}

/* Get request url */
string HttpRequest::getUrl()
{
    return this->_url;
}

/* Set request method */
void HttpRequest::setMethod(const string& method)
{
    this->_method = method;
}

/* Set request url */
void HttpRequest::setUrl(const string& url)
{
    this->_url = url;
}

string HttpRequest::dumpFirstLine()
{
    return this->_method + " " + this->_url + " " + this->_version + "\n";
}

};