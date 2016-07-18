#include "redis.h"

/**
 *
#define REDIS_REPLY_STRING 1
#define REDIS_REPLY_ARRAY 2
#define REDIS_REPLY_INTEGER 3
#define REDIS_REPLY_NIL 4
#define REDIS_REPLY_STATUS 5
#define REDIS_REPLY_ERROR 6  
 */

void MyFunction(struct Redis* this,int Num)
{
     //具体操作
    printf("MyFunction num is %d\n", Num);
    printf("%d\n",this->m_nNum);
}

void* get(struct Redis *this, char* key){
    char *result=NULL;
    char *command = (char*)malloc(strlen("get") + strlen(key) +1);
    redisReply *reply;
    sprintf (command, "get %s ", key);
    //printf("%s\n",command );
    reply = redisCommand(this->instance, command);
    result = (char*)malloc(strlen(reply->str)+1);
    memcpy(result, reply->str, strlen(reply->str));

    //printf("GET: %s\n", reply->str);
    freeReplyObject(reply);
    free(command);
    return result;
}


int set(struct Redis *this, char* key, char* val){
    char *command = (char*)malloc(strlen("set token:uid:") + strlen(key) + strlen(val) +1);
    redisReply *reply;
    sprintf (command, "set %s %s", key, val);
    printf("the command is %s\n", command);
    reply = redisCommand(this->instance, command);
    printf("SET: %s, %s\n", reply->str);
    freeReplyObject(reply);
    free(command);
    return 0;
}

int sadd(struct Redis *this, char* key, char* val){
    char *command = (char*)malloc(strlen("sadd") + strlen(key) + strlen(val) +1);
    redisReply *reply;
    sprintf (command, "sadd %s %s", key, val);
    
    reply = redisCommand(this->instance, command);
    if (!(reply->type == REDIS_REPLY_INTEGER ))  
    {  
        printf("Failed to execute command[%s]\n");  
        freeReplyObject(reply);  
        redisFree(this->instance);  
        return -1;  
    }  
    printf("sadd: %d, %d\n", reply->type,reply->integer);
    freeReplyObject(reply);
    free(command);
    return 0;
}

int zadd(struct Redis *this, char* key, int score, char* val){
    char *command = (char*)malloc(strlen("zadd") + 4  + strlen(val) +1);
    redisReply *reply;
    sprintf (command, "zadd %s %d %s", key, score, val);
    reply = redisCommand(this->instance, command);
    if (!(reply->type == REDIS_REPLY_INTEGER ))  
    {  
        printf("Failed to execute command[%s]\n");  
        freeReplyObject(reply);  
        redisFree(this->instance);  
        return -1;  
    }  
    printf("zadd: %d, %d\n", reply->type,reply->integer);
    freeReplyObject(reply);
    free(command);
    return 0;
}

//http://blog.csdn.net/hmsiwtv/article/details/32383887
Redis * RedisCtor(Redis *this)
{
    this->m_nNum = 12;
    //memcpy(this->p, "a", strlen("a"));
    this->MyFunction = MyFunction;
    this->set = set;
    this->get = get;
    this->sadd = sadd;
    this->zadd = zadd;
    this->instance = NULL;

    if (NULL == this->instance) { 
        struct timeval timeout = {5, 500000}; // 5.5 seconds 
        redisContext *redisConn = redisConnectWithTimeout("127.0.0.1", 6379,timeout);
        if (redisConn == NULL || redisConn->err) {
            printf("redisConnectWithTimeout error : %s\n", (redisConn ? redisConn->errstr : "redisConn is NULL"));
            if (redisConn != NULL) redisFree(redisConn);
            return NULL;
        }
        this->instance = redisConn; 
        printf("实例化redis的地址为:%x\n", redisConn);

    }else{
        printf("取出已经实例化的redis的地址为:%x\n", this->instance);
    }
    return this;
}
     
