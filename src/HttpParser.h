#ifndef HeyHTTP_HTTP_PARSER_H
#define HeyHTTP_HTTP_PARSER_H

#include <string>
#include <map>
#include <cstdarg>

namespace heyhttp
{

using std::string;
using std::map;

class HttpParser
{
public:
    // HttpParser();
    // ~HttpParser();
    virtual bool parse(const string& httpRequest);
    virtual bool parseFirstLine(const string& httpString)=0;
    virtual bool parseHeader(const string& httpString);
    virtual bool parseBody(const string& httpString);
    virtual bool parseQueryString(const string& httpString);

    virtual string getHeader(const string& key);
    virtual string getBody();
    virtual string getQueryParameter(const string& key);

    virtual void setHeader(const string& key, const string& value);
    virtual void setBody(const string& bodyData);
    virtual void setQueryParameter(const string& key, const string& value);

    virtual string dump();
    virtual string dumpFirstLine()=0;
    virtual string dumpHeader();
    virtual string dumpBody();
    virtual string dumpQueryString();

protected:
    static void logError(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "[ERROR] ");
        vfprintf(stderr, fmt, args);
        va_end(args);
    }

    static void logWarning(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        fprintf(stdout, "[WARNING] ");
        vfprintf(stdout, fmt, args);
        va_end(args);
    }

private:
    map< string, string > _header;
    map< string, string > _queryStringParameters;
    string _body;

};

};

#endif