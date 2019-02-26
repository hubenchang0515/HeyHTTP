#include "HttpParser.h"
#include <iostream>
#include <cstdio>

namespace heyhttp
{

bool HttpParser::parse(const string& httpString)
{
    if(httpString.length() == 0)
    {
        return false;
    }
    bool ret = true;
    size_t pos1 = httpString.find('\n');
    if(pos1 != string::npos)
    {
        ret = ret && this->parseFirstLine(httpString.substr(0, pos1));
    }
    else
    {
        ret = ret && this->parseFirstLine(httpString);
    }
    

    size_t pos2 = httpString.find("\n\n");
    if(pos2 != string::npos)
    {
        ret = ret && this->parseHeader(httpString.substr(pos1+1, pos2-pos1));
        ret = ret && this->parseBody(httpString.substr(pos2+2));
    }
    else
    {
        ret = ret && this->parseHeader(httpString);
    }

    return ret;
}

/* Parse HTTP header */
bool HttpParser::parseHeader(const string& httpString)
{
    string line;
    size_t pos = 0;
    size_t count = 0;
    
    /* Parse the header */
    string tempString = httpString + "\n"; // simplify loop
    pos = tempString.find('\n');
    while(pos != string::npos)
    {
        pos += 1;
        count = tempString.find('\n', pos) - pos;
        line = tempString.substr(pos, count);
        if(line.find_first_not_of(" \t\r\n") == string::npos)
        {
            pos = tempString.find('\n', pos);
            continue;
        }
        size_t pos_of_colon = line.find(':');
        if(pos_of_colon == string::npos)
        {
            logWarning("Malformed header line (%s).\n", line.c_str());
        }
        else
        {
            string key = clearEnds(line.substr(0, pos_of_colon));
            string value = clearEnds(line.substr(pos_of_colon + 1));
            this->_header[key] = value;
        }
        pos = tempString.find('\n', pos);
    }

    return true;
}

/* Parse HTTP body */
bool HttpParser::parseBody(const string& httpString)
{
    this->_body = httpString;

    return true;
}

/* Parse HTTP query string parameters */
bool HttpParser::parseQueryString(const string& httpString)
{
    size_t pos = 0;
    size_t count = 0;
    // if(httpString[0] == '?')
    // {
    //     pos = 1;
    // }

    string param;
    string tempString = httpString + "&"; // simplify loop
    while(pos != string::npos)
    {
        pos += 1;
        count = tempString.find('&', pos) - pos;
        param = tempString.substr(pos, count);
        if(param.find_first_not_of(" \t\r\n") == string::npos)
        {
            pos = param.find('&', pos);
            continue;
        }
        size_t pos_of_equal = param.find('=');
        if(pos_of_equal == string::npos)
        {
            logWarning("Malformed query string parameter (%s).\n", param.c_str());
        }
        else
        {
            string key = clearEnds(param.substr(0, pos_of_equal));
            string value = clearEnds(param.substr(pos_of_equal+1));
            this->_queryStringParameters[key] = value;
        }
        pos = tempString.find('&', pos);
    }

    return 0;
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

/* Get HTTP query string parameter */
string HttpParser::getQueryParameter(const string& key)
{
    return this->_queryStringParameters[key];
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

/* Set HTTP query string parameter */
void HttpParser::setQueryParameter(const string& key, const string& value)
{
    this->_queryStringParameters[key] = value;
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

/* Dump HTTP body */
string HttpParser::dumpBody()
{
    return this->_body;
}

/* Dump HTTP query string */
string HttpParser::dumpQueryString()
{
    string queryString = "?";
    for(auto& pair : this->_queryStringParameters)
    {
        queryString += std::get<0>(pair);
        queryString += "=";
        queryString += std::get<1>(pair);
        queryString += "&";
    }
    queryString.erase(queryString.length()-1);
    return queryString;
}

};