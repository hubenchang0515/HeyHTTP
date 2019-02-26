#ifndef HEY_HTTP_HTTP_RESPONSE
#define HEY_HTTP_HTTP_RESPONSE

#include "HttpParser.h"

namespace heyhttp
{

using std::string;
using std::map;

class HttpResponse : public HttpParser
{
public:
    virtual bool parseFirstLine(const string& httpRequest, bool isDebug=true);

    virtual string getVersion();
    virtual string getState();
    virtual string getInfo();

    virtual void setVersion(const string& version);
    virtual void setState(const string& state);
    virtual void setInfo(const string& info);

    virtual string dumpFirstLine();

private:
    string _version = "HTTP/1.1";
    string _state = "200";
    string _info = "OK";
};

};

#endif