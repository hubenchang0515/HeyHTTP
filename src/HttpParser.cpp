#include "HttpParser.h"
#include <iostream>
#include <cstdio>

namespace heyhttp
{

bool HttpParser::parse(const string& httpString, bool isDebug)
{
    bool ret = true;
    size_t pos1 = httpString.find('\n');
    ret = ret && this->parseFirstLine(httpString.substr(0, pos1));

    size_t pos2 = httpString.find("\n\n");
    if(pos2 != string::npos)
    {
        ret = ret && this->parseHeader(httpString.substr(pos1+1, pos2-pos1), isDebug);
        ret = ret && this->parseBody(httpString.substr(pos2+2), isDebug);
    }
    else
    {
        ret = ret && this->parseHeader(httpString, isDebug);
    }

    return ret;
}

/* Parse HTTP header */
bool HttpParser::parseHeader(const string& httpString, bool isDebug)
{
    string line;
    size_t pos = 0;
    size_t count = 0;
    
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

    return true;
}

/* Get HTTP header */
string HttpParser::getHeader(const string& key)
{
    return this->_header[key];
}

/* Get HTTP Body */
string HttpParser::getBody()
{
    return this->_body;
}

/* Set HTTP header */
void HttpParser::setHeader(const string& key, const string& value)
{
    this->_header[key] = value;
}

/* Set HTTP body */
void HttpParser::setBody(const string& bodyData)
{
    this->_body = bodyData;
}

/* Dump to string */
string HttpParser::dump()
{
    return this->dumpFirstLine() + this->dumpHeader() + "\n" + this->dumpBody();
}

/* Dump header to string */
string HttpParser::dumpHeader()
{
    string ret = "";
    for(auto& pair : this->_header)
    {
        ret += std::get<0>(pair);
        ret += ": ";
        ret += std::get<1>(pair);
        ret += "\n";
    }

    return ret;
}

string HttpParser::dumpBody()
{
    return this->_body;
}

};