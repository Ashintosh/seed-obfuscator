//////////////////////////////////////////////////////////////////////////////////////////
// File: src/curl/curl.h                                                                //
// Copyright: (c) 1996 - 2022, Daniel Stenberg, <daniel@haxx.se>, and many contributors //
// Source: https://github.com/curl/curl                                                 //
// License: (src/curl/LICENSE)                                                          //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef CURL_H
#define CURL_H

#include <iostream>
#include <curl/curl.h>
#include <string.h>


class curl
{
public:
    static std::string url_to_str(std::string url);

private:
    static size_t write_call_back(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // CURL_H
