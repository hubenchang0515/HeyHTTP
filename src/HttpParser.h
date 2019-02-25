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
    bool parse(const string& httpRequest, bool isDebug=true);
    bool parseHeader(const string& httpString, bool isDebug=true);
    bool parseBody(const string& httpString, bool isDebug=true);

private:
    string _method;
    string _url;
    string _http_version;
    map< string, string > _header;
    string _body;

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

};

};

#endif