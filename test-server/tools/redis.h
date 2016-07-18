#ifndef _REDIS
#define _REDIS
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include "glib.h"
#include <sys/time.h>
#include <unistd.h>
typedef struct Redis
{
	struct Redis* this;
	int m_nNum;
	char *p;
	
	void (*MyFunction)(struct Redis* this,int Num);
	int (*set)(struct Redis *this,char* key, char* val);
	void* (*get)(struct Redis *this, char* key);
	int (*sadd)(struct Redis *this, char* key, char* val);
	int (*zadd)(struct Redis *this, char* key, int score, char* val);
    redisContext * instance;
}Redis;

Redis * RedisCtor(Redis *this);
#endif