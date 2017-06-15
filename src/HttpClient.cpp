#include "HttpClient.h"
#include "stdio.h"

HttpClient * HttpClient::m_HttpClient;

HttpClient::HttpClient()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

HttpClient * HttpClient::getInstence() 
{
    if (m_HttpClient == NULL) {
        m_HttpClient = new HttpClient();
    }

    if (m_HttpClient->curl)
        return m_HttpClient;
    else {
        delete m_HttpClient;
        m_HttpClient = NULL;
        return NULL;
    }

}

int HttpClient::GET(const char * url, const char * body)
{
    url_data_t headerdata, bodydata;
    headerdata.size = 0;
    headerdata.data= NULL;
    bodydata.size = 0;
    bodydata.data= NULL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bodydata);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerdata);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("post: %s\n", curl_easy_strerror(res));
    }

    if (headerdata.size > 0)
    {
        printf("res header:%s\n", headerdata.data);
    }

    if (bodydata.size > 0)
    {
        printf("res:%s\n", bodydata.data);
    }
    return res;
}

int HttpClient::POST(const char * url, const char * body) 
{
    url_data_t headerdata, bodydata;
    headerdata.size = 0;
    headerdata.data= NULL;
    bodydata.size = 0;
    bodydata.data= NULL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(body));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bodydata);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerdata);

    res = curl_easy_perform(curl);
    
    if (res != CURLE_OK) {
        printf("post: %s\n", curl_easy_strerror(res));
    }

    if (headerdata.size > 0)
    {
        printf("res header:%s\n", headerdata.data);
    }

    if (bodydata.size > 0)
    {
        printf("res body:%s\n", bodydata.data);
    }

    return res;
}

size_t HttpClient::WriteData(void * ptr, size_t size, size_t nmemb, url_data_t * data)
{
    size_t index = data->size;
    size_t n = size * nmemb;
    char * tmp;

    data->size += (size * nmemb);

    tmp = (char *)realloc((void *)data->data, data->size + 1);
    if (tmp) {
        data->data = tmp;
    } 
    else {
        if (data->data) {
            free(data->data);
        }
        return 0;
    }
    memcpy(data->data + index, ptr, n);
    data->data[data->size] = '\0';

    return n;
}
