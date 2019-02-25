#ifndef HEY_HTTP_HTTP_REQUEST
#define HEY_HTTP_HTTP_REQUEST

#include "HttpParser.h"

namespace heyhttp
{

using std::string;
using std::map;

class HttpRequest : public HttpParser
{
public:
    virtual bool parseFirstLine(const string& httpRequest, bool isDebug=true);

    virtual string getMethod();
    virtual string getUrl();

    virtual void setMethod(const string& method);
    virtual void setUrl(const string& url);
    //virtual void setVersion(const string& version);

    virtual string dumpFirstLine();

private:
    string _method;
    string _url;
    string _version = "HTTP/1.1";
};

};

#endif