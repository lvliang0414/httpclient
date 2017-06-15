#ifndef _YCTH_CLIENT_HTTP_CLIENT_H_
#define _YCTH_CLIENT_HTTP_CLIENT_H_

#include "curl/curl.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    char * data;

}url_data_t;

class HttpClient {

public:
    static HttpClient * getInstence();

    int GET(const char * url, const char * body);
    int POST(const char * url, const char * body);

private:
    static HttpClient  * m_HttpClient;
    HttpClient();

    CURL * curl;
    CURLcode   res;

    static size_t WriteData(void * ptr, size_t size, size_t nmemb, url_data_t * data);

};

#endif

