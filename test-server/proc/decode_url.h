#ifndef _DECODE_URL
#define _DECODE_URL 
#include "../tools/base64.h"
#include <openssl/des.h>
#include "zlog.h"
//引用main中的全局变量
extern zlog_category_t* zc;
char* decode_url(const char *url);
#endif