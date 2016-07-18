#include "hand_url.h"

char* decode_url( char *encodeUrl){
	//密钥
	unsigned char *keyString = "abcdefg";
	DES_cblock key;
	DES_key_schedule keySchedule;
	//IV
    DES_cblock ivec;

	memset((char*)&ivec, 0, sizeof(ivec));
    memcpy((char*)&ivec,"456",sizeof("456"));

    /**
     *不起作用*/
	// DES_string_to_key(keyString, &key);
	// if (DES_set_key_checked(&key, &keySchedule) != 0) {
	// 	printf("convert to keySchedule failed.\n");
	// 	return -1;
	// }
	

	memcpy(key, keyString, 8);  
    DES_set_key_unchecked(&key, &keySchedule); 

	
	zlog_info(zc, "解码前的url:%s",encodeUrl);

	char  *decode = base64_decode((char*)encodeUrl, strlen(encodeUrl)); 
	zlog_info(zc, "解码后的url:%s",decode);

	//解密
	char *out=malloc(100);
	DES_ncbc_encrypt(decode, out, strlen(decode), &keySchedule, &ivec, 0);
	zlog_info(zc, "解密后的url:%s",out);
	free(decode);
	return out;
}


GHashTable* parse_url(char *url){

	GHashTable* hashTable = g_hash_table_new(g_str_hash,g_str_equal);
    if(hashTable == NULL){
        fprintf(stderr, "create hash table failed\n");
        return NULL;
    }

    char *find="?param";
    char *pos= strstr(url, find);
    if(!pos){
        return NULL;
    }
    printf("the url is %s\n", url);
    gchar **string1 = NULL;
    char i;

    string1 = g_strsplit (url, "?", -1);

    gchar **encodeUrl=NULL;
    encodeUrl = g_strsplit (string1[1], "=", -1);
	printf("the = is %s\n",encodeUrl[1]);

    //解码+解密
    char* decodeUrl = decode_url(encodeUrl[1]);

    //取出各个字段

    gchar **params=NULL;
   
    params = g_strsplit (decodeUrl, "&", -1);

    for (i = 0; params && params[i]; i++){
    	gchar **kv=NULL;
    	kv = g_strsplit (params[i], "=", -1);
        if(kv[0]!= "version"){
            //https://developer.gnome.org/glib/stable/glib-Type-Conversion-Macros.html
            g_hash_table_insert(hashTable, kv[0], GINT_TO_POINTER(atoi(kv[1])));
        }else{
            g_hash_table_insert(hashTable, kv[0], kv[1]);
        }
    	
    	printf("the key is %s,the value is %s\n", kv[0], kv[1]);
    	free(kv);
    }
    //http://blog.csdn.net/szwpc/article/details/538025
    // char* age="12";
    // g_hash_table_insert(hashTable, "age", atoi(age));

    /**
     *GPOINTER_TO_INT gpointer转为int
     */
    int userid=GPOINTER_TO_INT(g_hash_table_lookup(hashTable, "uid"));
    int ownerid = GPOINTER_TO_INT(g_hash_table_lookup(hashTable, "ownerid"));
    int sessionid = GPOINTER_TO_INT(g_hash_table_lookup(hashTable, "sessionid"));
    printf("find the userid %d\n", userid);
    free(params);
    free(decodeUrl);
    
    return NULL;


}


int check_token(const char* userId, const char *token){
	redisContext *rconn = NULL;
	redisReply *reply;
	gchar *command = NULL;

  	

    /* Set a key */
    //char *key = join1("set token:uid:", token );


    //详见https://developer.gnome.org/glib/stable/glib-String-Utility-Functions.html#g-strconcat
    printf("check_token address is %x\n", pClass);
    char *msg= (char*)pClass->get(pClass, "name");
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