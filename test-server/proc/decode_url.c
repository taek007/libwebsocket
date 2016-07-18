#include "decode_url.h"

/**
 *gcc -o des10 des10.c proc/decode_url.c tools/base64.c  -lcrypto 
 */
char* decode_url(const char *encodeUrl){
	//密钥
	unsigned char *keyString = "abcdefg";
	DES_cblock key;
	DES_key_schedule keySchedule;
	//IV
    DES_cblock ivec;

	memset((char*)&ivec, 0, sizeof(ivec));
    memcpy((char*)&ivec,"456",sizeof("456"));

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