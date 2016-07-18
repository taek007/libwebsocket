#include <openssl/des.h>
#include <stdio.h>
#include <string.h>
#include "proc/hand_url.h"
#include "tools/ini_log.h"
#include "tools/redis.h"
#include "glib.h"
/**
 *  gcc -o des10 des10.c proc/decode_url.c proc/encode_url.c  proc/check_token.c  tools/base64.c tools/ini_log.c tools/function.c tools/redis.c  tools/url_parser.c -lcrypto  -lzlog -lpthread  -lhiredis  -I/usr/local/include  `pkg-config --cflags --libs glib-2.0`  


 gcc -o des10 des10.c proc/hand_url.c   tools/base64.c tools/ini_log.c tools/function.c tools/redis.c   -lcrypto  -lzlog -lpthread  -lhiredis  -I/usr/local/include  `pkg-config --cflags --libs glib-2.0`   


-I/usr/local/include  //用于指定hiredis.h路径

 http://blog.csdn.net/shuilan0066/article/details/6924251/

 http://blog.csdn.net/kwongfung/article/details/8067266

 http://blogs.360.cn/360apps/2013/03/19/%E5%B0%8F%E5%BF%83c%E8%AF%AD%E8%A8%80%E7%9A%84%E5%AE%9A%E4%B9%89%E4%B8%8E%E5%A3%B0%E6%98%8E/
 http://blogs.360.cn/360apps/

 http://blog.sina.com.cn/s/blog_6a4c492f0100onx2.html

 http://www.amghost.cc/echo-server-based-on-libev/
 http://webcache.googleusercontent.com/search?q=cache:idrUNZ05LJ4J:blog.codingnow.com/2012/04/mread.html+&cd=5&hl=zh-CN&ct=clnk&gl=cn
 http://blog.csdn.net/pkueecser/article/details/18662271


 http://blog.csdn.net/l1902090/article/details/38583663

 http://blog.csdn.net/pkueecser/article/details/18662271

 http://yaocoder.blog.51cto.com/2668309/1297031


 http://www.phpxs.com/code/1004231/

 http://www.thinksaas.cn/topics/0/246/246714.html

 http://blog.csdn.net/p0x1307/article/details/40115567


 http://blog.csdn.net/wfung_kwok/article/details/7766427


 http://hais1992.lofter.com/post/2d8697_1a6b937 


 http://www.leoox.com/?p=316

 http://blog.csdn.net/hj19870806/article/details/8724907
 */

zlog_category_t* zc=NULL;
Redis* pClass=NULL;
int main(int argc, char** argv)
{
	zc= log_init();
		
	zlog_info(zc, "hello, abc");
	 
	/**
	 *这里不能使用栈来分配内在,因为pClass还要在tools/redis.c中使用,
	 *要在堆上分配内存
	 *
	 *Redis objClass; //不可以
	 */

	Redis *objClass=(Redis *)malloc(sizeof(Redis));	//定义一指针、一结构体变量
	pClass = RedisCtor(objClass);	//调用构造函数

	// const char *url ="uid=802779641&token=T2a362a4e84d86d3&owner=1084046&version=7.3.8.1&session=712289";
	// char *encodeUrl = encode_url(url);
	// printf("the encode url is %s\n", encodeUrl);

	char *url="http://?param=1zVTMxuj7F2KTpw9kNVCtzET2NV4dWZ2UyRY1012r4YvubRtNp6bFwrB3xd6NflHA/5ltNzG3HXe87ie7ReCbipP/DpWGOLFA/iIefGZ2zDwiec9PywoYA==";

	GHashTable* hashTable = parse_url(url);

/**
	const char* encodeUrl2 = "1zVTMxuj7F2KTpw9kNVCtzET2NV4dWZ2UyRY1012r4YvubRtNp6bFwrB3xd6NflHA/5ltNzG3HXe87ie7ReCbipP/DpWGOLFA/iIefGZ2zDwiec9PywoYA==";

	char *decodeUrl = decode_url(encodeUrl2);
	printf("now decode url is %s\n", decodeUrl);

	//查看是否有param字段
	char* str="ws://api-ali-yd.changbalive.com:5587?param=1zVTMxuj7F2KTpw9kNVCtzET2NV4dWZ2UyRY1012r4YvubRtNp6bFwrB3xd6NflHA_5ltNzG3HXe87ie7ReCbipP_DpWGOLFA_iIefGZ2zCC3fc-A5f2Pg";
	GHashTable* hashTable = parse_params(str);
//printf("%x\n", hashTable);

	char* state = NULL;
	char* capital = NULL;
	char** key_ptr = &state;
	char** value_ptr = &capital;

	gboolean result = g_hash_table_lookup_extended(hashTable, "Ohio", (gpointer*)key_ptr, (gpointer*)value_ptr);
if (result)
  {
  g_printf("Found that the capital of %s is %s\n", capital, state);
 }



	

	


	int res=check_token("123","aaa");
	printf("redis result is %d\n", res);
*/
	zlog_fini();

	return 0;

}