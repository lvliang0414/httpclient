#include "HttpClient.h"
#include <unistd.h>
#include <stdio.h>

int main() 
{
    HttpClient * httpClient = HttpClient::getInstence();
    if (httpClient == NULL) {
        perror("httpClient");
        return -1;
    }

    while (1) {
        httpClient->POST("http://35.189.161.10:3000/param", "test");
        sleep(10);
    }
}

