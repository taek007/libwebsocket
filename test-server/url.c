#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "url_parser.h"
#include "glib.h"
//#include "zlog.h"
#include "log.h"
#include "cJSON.h"

/**
https://blog.wu-boy.com/2010/04/cc-c%E8%AA%9E%E8%A8%80%E5%88%87%E5%89%B2%E5%AD%97%E4%B8%B2%E5%87%BD%E5%BC%8F-strsep%EF%BC%8C%E5%88%86%E6%9E%90-url-get-%E5%8F%83%E6%95%B8/

gcc -o url -I/usr/local/include/cjson url.c url_parser.c log.c `pkg-config --cflags --libs glib-2.0`   -lcjson -lm -lzlog  


 vi /etc/ld.so.conf 
 /usr/local/lib  
*/

static void free_data(gpointer hash_data)
{
    g_free(hash_data);
    hash_data = NULL;
}

void iterator(gpointer key, gpointer value ,gpointer user_data)
{
 g_printf(user_data, *(gint*)key, value);
}

int main(){

	char *url="http://www.baidu.com/index.php?name=zm&age=2";
	struct parsed_url *purl;
	purl = malloc(sizeof(struct parsed_url));

	purl= parse_url(url);
    printf("%s",purl->query);

	GHashTable* param_array = parse_params(purl->query);

	char* Bean_score = g_hash_table_lookup(param_array,"name");
	if(Bean_score == NULL)
    {
        fprintf(stderr,"can not found Bean Score\n");
    }

	printf("Bean\'s score = %s\n",(char*)Bean_score);
	g_hash_table_destroy(param_array);

	parsed_url_free(purl);
	//http://blog.sina.com.cn/s/blog_606c49090100esrd.html


	// zlog_category_t* zc = log_init();
		
	// zlog_info(zc, "hello, abc");
	 
	// zlog_fini();


	//http://hahaya.github.io/use-cJSON/
	
	//组JSON
    cJSON *root_json = cJSON_CreateObject();
    cJSON_AddItemToObject(root_json, "name", cJSON_CreateString("EVDI"));
    cJSON *data_json = cJSON_CreateObject();
    cJSON_AddItemToObject(root_json, "data", data_json);
    //添加的另一种方式:cJSON_AddNumberToObject(data_json, "id", 1);通过源码发现仅仅是对cJSON_AddItemToObject的define
    cJSON_AddItemToObject(data_json, "id", cJSON_CreateNumber(1));
    //添加的另一种方式:cJSON_AddStringToObject(data_json, "username", "hahaya");
    cJSON_AddItemToObject(data_json, "username", cJSON_CreateString("hahaya"));
    cJSON_AddItemToObject(data_json, "userpass", cJSON_CreateString("123456"));
    cJSON_AddItemToObject(data_json, "version", cJSON_CreateString("1.0"));
    //打印JSON
    char *out = cJSON_Print(root_json);
    printf("%s\n", out);
    free(out);


	return 0;
}
