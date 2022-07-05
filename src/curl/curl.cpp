//////////////////////////////////////////////////////////////////////////////////////////
// File: src/curl/curl.cpp                                                              //
// Copyright: (c) 1996 - 2022, Daniel Stenberg, <daniel@haxx.se>, and many contributors //
// Source: https://github.com/curl/curl                                                 //
// License: (src/curl/LICENSE)                                                          //
//////////////////////////////////////////////////////////////////////////////////////////

#include "curl.h"


size_t curl::write_call_back(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string curl::url_to_str(std::string url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_call_back);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        if (res != CURLE_OK)  return "null";
        // std::cout << readBuffer.c_str() << std::endl;
        return readBuffer;
    }
    return "null";
}
