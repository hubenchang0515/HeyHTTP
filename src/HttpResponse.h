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
    virtual string dumpFirstLine();

private:
    string _version;
    string _state;
    string _info;
};

};

#endif