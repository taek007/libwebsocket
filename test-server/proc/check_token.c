#include "check_token.h"
int check_token(const char* userId, const char *token){
	redisContext *rconn = NULL;
	redisReply *reply;
	gchar *command = NULL;

  	

    /* Set a key */
    //char *key = join1("set token:uid:", token );


    //详见https://developer.gnome.org/glib/stable/glib-String-Utility-Functions.html#g-strconcat
    printf("check_token address is %x\n", pClass);
    char *msg= pClass->get(pClass, "name");
    printf("the msg is %s\n", msg);
    free(msg);

    /*
    command = g_strconcat ("set token:uid:", userId, "long", NULL);
    printf("the key is %s\n",command);
    

    reply = redisCommand(rconn, command);
    printf("SET: %s, %s\n", reply->str);
    freeReplyObject(reply);
    g_free(command);


    command = malloc(strlen("get") + strlen(TOKENPREFIX)+1);
    sprintf(command,"%s","get token:uid:");
    reply = (redisReply*)redisCommand(rconn, command);  
      
    if ( reply->type != REDIS_REPLY_STRING)  
    {  
       // printf("Failed to execute command[%s]\n",command3);  
        freeReplyObject(reply);  
        redisFree(rconn);  
        return -1;  
    }  

    printf("The value of 'stest1' is %s\n", reply->str);  
    freeReplyObject(reply);  
    free(command);

    if(strcmp(reply->str, token) == 0 ){
    	//验证通过
    	return 0;
    }else{
    	return -1;
    }
    */
    
    //printf("Succeed to execute command[%s]\n");  
}