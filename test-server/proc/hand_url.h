#ifndef _HAND_URL
#define _HAND_URL 
#include <openssl/des.h>
#include <glib.h>
#include "zlog.h"
#include "hiredis/hiredis.h"
#include "../tools/base64.h"
#include "../tools/redis.h"
//引用main中的全局变量
extern zlog_category_t* zc;
extern Redis* pClass;

char* decode_url( char *url);
int check_token(const char* userid, const char* token);
GHashTable* parse_url(char *url);
#endif