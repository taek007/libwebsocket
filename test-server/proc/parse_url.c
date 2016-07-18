#include "parse_url.h"

int parse_url(const char *encodeUrl){
	unsigned char *keystring = "newtv.beijing!";
	DES_cblock key;
	DES_key_schedule key_schedule;
	//IV
    DES_cblock ivec;

	memset((char*)&ivec, 0, sizeof(ivec));
    memcpy((char*)&ivec,"12345678",sizeof("12345678"));

	// DES_string_to_key(keystring, &key);

	// if (DES_set_key_checked(&key, &key_schedule) != 0) {
	// 	printf("convert to key_schedule failed.\n");
	// 	return -1;
	// }

	memcpy(key, keystring, 8);  
      DES_set_key_unchecked(&key, &key_schedule); 

	
	printf("the url is %s\n", encodeUrl);
	char  *decode = base64_decode((char*)encodeUrl, strlen(encodeUrl)); 
	printf("the decode is %s, the length is %d\n",decode, strlen(decode));

	//解密
	char in[1000];
	DES_ncbc_encrypt(decode, in, strlen(decode), &key_schedule, &ivec, 0);

	printf("%s\n", in);


}