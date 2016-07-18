#include <openssl/des.h>
#include <stdio.h>
#include <string.h>
#include "tools/base64.h"

int main(int argc, char** argv)
{
      unsigned char *keystring = "abcdefg";
      DES_cblock key;
      DES_key_schedule key_schedule;

      //生成一个 key
      // DES_string_to_key(keystring, &key);
      // if (DES_set_key_checked(&key, &key_schedule) != 0) {
      //     printf("convert to key_schedule failed.\n");
      //     return -1;
      // }

     
      memcpy(key, keystring, 8);  
      DES_set_key_unchecked(&key, &key_schedule); 

      //需要加密的字符串
      unsigned char input[] = "uid=802779641&token=T2a362a4e84d86d3&owner=1084046&version=7.3.8.1&session=712289";
      size_t len = (sizeof(input)+7)/8 * 8;  
      unsigned char *output = malloc(len+1);
      //IV
      DES_cblock ivec;

      //IV设置为0x0000000000000000
      memset((char*)&ivec, 0, sizeof(ivec));
      memcpy((char*)&ivec,"567",sizeof("567"));
      
      //加密
      DES_ncbc_encrypt(input, output, strlen(input), &key_schedule, &ivec, DES_ENCRYPT);
      printf("%s\n",output);

      //base64编码
      char *encode2 = base64_encode((char*)output, strlen(output)); 
      printf("the encode is %s, the length is %d\n",encode2, strlen(encode2));

      //输出加密以后的内容
      int i;
      for (i = 0; i < len; ++i)
         printf("%02x", output[i]);
      printf("\n");

      return EXIT_SUCCESS;
}