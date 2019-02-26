#include "HttpResponse.h"
#include <iostream>

namespace heyhttp
{

using std::string;
using std::map;

/* Parse the HTTP response first line */
bool HttpResponse::parseFirstLine(const string& httpString)
{
    size_t pos1 = httpString.find(' ');
    size_t pos2 = httpString.rfind(' ');

    this->_version = httpString.substr(0, pos1);
    this->_state = httpString.substr(pos1+1, pos2-pos1-1);
    this->_info = httpString.substr(pos2+1);

    if(this->_version != "HTTP/1.1")
    {
        logWarning("Only support HTTP/1.1 (%s).\n", httpString.c_str());
    }

    return true;
}

/* Get HTTP version */
string HttpResponse::getVersion()
{
    return this->_version;
}

/* Get response state */
string HttpResponse::getState()
{
    return this->_state;
}

/* Get response info */
string HttpResponse::getInfo()
{
    return this->_info;
}

/* Set HTTP version */
void HttpResponse::setVersion(const string& version)
{
    if(version != "HTTP/1.1")
    {
        logWarning("Only support HTTP/1.1 (%s).\n", version.c_str());
    }

    this->_version = version;
}

/* Set response state */
void HttpResponse::setState(const string& state)
{
    this->_state = state;
}

/* Set response info */
void HttpResponse::setInfo(const string& info)
{
    this->_info = info;
}

/* Dump first line to string */
string HttpResponse::dumpFirstLine()
{
    return this->_version + " " + this->_state + " " + this->_info + "\n";
}

};