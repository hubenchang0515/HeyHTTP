#include "HttpParser.h"
#include <iostream>
#include <cstdio>

namespace heyhttp
{

bool HttpParser::parse(const string& httpString, bool isDebug)
{
    size_t pos = httpString.find("\n\n");
    if(pos != string::npos)
    {
        this->parseHeader(httpString.substr(0, pos+2), isDebug);
        this->parseBody(httpString.substr(pos+2), isDebug);
    }
    else
    {
        this->parseHeader(httpString, isDebug);
    }
}

/* Parse HTTP header */
bool HttpParser::parseHeader(const string& httpString, bool isDebug)
{
    string line;
    size_t pos = 0;
    size_t count = 0;

    /* Parse the first line */
    line = httpString.substr(pos, httpString.find('\n'));
    count = line.find(' ');
    this->_method = line.substr(0, count);
    pos = line.rfind(' ');
    this->_http_version = line.substr(pos + 1);
    this->_url = line.substr(count + 1, pos - count - 1);

    if(this->_http_version != "HTTP/1.1")
    {
        logError("Only support HTTP/1.1 (%s).\n", line.c_str());
    }
    
    /* Parse the header */
    pos = httpString.find('\n');
    while(pos != string::npos)
    {
        pos += 1;
        count = httpString.find('\n', pos) - pos;
        line = httpString.substr(pos, count);
        if(line.find_first_not_of(" \t\r\n") == string::npos) break;
        size_t pos_of_colon = line.find(':');
        if(pos_of_colon == string::npos)
        {
            logWarning("Malformed header line (%s).\n", line.c_str());
        }
        string key = line.substr(0, pos_of_colon);
        string value = line.substr(pos_of_colon + 1);
        this->_header[key] = value;
        pos = httpString.find('\n', pos);
    }


    /* DEBUG print */
    if(isDebug)
    {
        std::cout << this->_method << " " << this->_url << " " << this->_http_version << std::endl;
        for(auto& pair : this->_header)
        {
            std::cout << std::get<0>(pair) << " : " << std::get<1>(pair) << std::endl;
        }
    }

    return true;
}


/* Parse HTTP body */
bool HttpParser::parseBody(const string& httpString, bool isDebug)
{
    this->_body = httpString;

    if(isDebug)
    {
        std::cout << this->_body << std::endl;
    }
}

}