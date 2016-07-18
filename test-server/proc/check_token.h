#ifndef _CHECK_TOKEN
#define _CHECK_TOKEN 
#include "hiredis/hiredis.h"
#include "../tools/redis.h"
#include "glib.h"
#define TOKENPREFIX  "token:uid:"
extern Redis* pClass;
int check_token(const char* userid, const char* token);
#endif