#include "encode_url.h"
/**
 *gcc -o des10 des10.c proc/decode_url.c tools/base64.c  -lcrypto 
 */


char* encode_url(const char *url){
	//密钥
	unsigned char *keyString = "abcdefg";
	DES_cblock key;
	DES_key_schedule keySchedule;
	//IV
    DES_cblock ivec;

	memset((char*)&ivec, 0, sizeof(ivec));
    memcpy((char*)&ivec,"456",sizeof("456"));


    size_t len = (strlen(url)+7)/8 * 8;  
    unsigned char *output = malloc(len+1);
    /**
     *不起作用
	DES_string_to_key(keyString, &key);
	if (DES_set_key_checked(&key, &key_schedule) != 0) {
		printf("convert to key_schedule failed.\n");
		return -1;
	}
	*/

	memcpy(key, keyString, 8);  
    DES_set_key_unchecked(&key, &keySchedule); 

	zlog_info(zc, "输入的url:%s",url);


	//加密
	DES_ncbc_encrypt(url, output, strlen(url), &keySchedule, &ivec, DES_ENCRYPT);

	//编码
	char  *encode = base64_encode((char*)output, strlen(output));
	zlog_info(zc, "url被base64编码:%s",encode); 
	//printf("the encode is %s, the length is %d\n",encode, strlen(encode));

	free(output);
	return encode;

}