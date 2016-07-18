#include <openssl/des.h>
#include <stdio.h>
#include <string.h>
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
char* base64_encode(const char* data, int data_len); 
char *base64_decode(const char* data, int data_len); 



/* */ 
char *base64_encode(const char* data, int data_len) 
{ 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
      
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            //printf("tmp = %d\n", tmp); 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            //printf("%.2X", changed[i]); 
            f++; 
        } 
    } 
    *f = '\0'; 
      
    return ret; 
      
} 
/* */ 
static char find_pos(char ch)   
{ 
    char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
    return (ptr - base); 
} 
/* */ 
char *base64_decode(const char *data, int data_len) 
{ 
    int ret_len = (data_len / 4) * 3; 
    int equal_count = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    int temp = 0; 
    char need[3]; 
    int prepare = 0; 
    int i = 0; 
    if (*(data + data_len - 1) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 2) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 3) == '=') 
    {//seems impossible 
        equal_count += 1; 
    } 
    switch (equal_count) 
    { 
    case 0: 
        ret_len += 4;//3 + 1 [1 for NULL] 
        break; 
    case 1: 
        ret_len += 4;//Ceil((6*3)/8)+1 
        break; 
    case 2: 
        ret_len += 3;//Ceil((6*2)/8)+1 
        break; 
    case 3: 
        ret_len += 2;//Ceil((6*1)/8)+1 
        break; 
    } 
    ret = (char *)malloc(ret_len); 
    if (ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < (data_len - equal_count)) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(need, 0, 4); 
        while (temp < 4) 
        { 
            if (tmp >= (data_len - equal_count)) 
            { 
                break; 
            } 
            prepare = (prepare << 6) | (find_pos(data[tmp])); 
            temp++; 
            tmp++; 
        } 
        prepare = prepare << ((4-temp) * 6); 
        for (i=0; i<3 ;i++ ) 
        { 
            if (i == temp) 
            { 
                break; 
            } 
            *f = (char)((prepare>>((2-i)*8)) & 0xFF); 
            f++; 
        } 
    } 
    *f = '\0'; 
    return ret; 
}


int main(int argc, char** argv)
{
      unsigned char *keystring = "abcdefg";
      DES_cblock key;
      DES_key_schedule key_schedule;

      //生成一个 key
      DES_string_to_key(keystring, &key);
      if (DES_set_key_checked(&key, &key_schedule) != 0) {
          printf("convert to key_schedule failed.\n");
          return -1;
      }
      //IV
      DES_cblock ivec;
      unsigned char *output = malloc(200+1);
/**
      //需要加密的字符串
      unsigned char input[] = "uid=802779641&token=T2a362a4e84d86d3&owner=1084046&version=7.3.8.1&session=712289";

      printf("%s\n",input);
      size_t len = (sizeof(input)+7)/8 * 8;  
      printf("the len is %d\n\n",len);
  
      

      //IV设置为0x0000000000000000
      memset((char*)&ivec, 0, sizeof(ivec));
      memcpy((char*)&ivec,"456",sizeof("456"));
      int j;
      for(j = 0;j < len/8;j+=8)
      {
          //memcpy(input,data_hex+i*8,8);
          DES_ncbc_encrypt((input+j), output, sizeof(input),&key_schedule,&ivec,DES_ENCRYPT);
          //memcpy(temp+i*8,output,8);
      }

      //加密
     // DES_ncbc_encrypt(input, output, sizeof(input), &key_schedule, &ivec, DES_ENCRYPT);
      char *enc = base64_encode((char*)output, len); 
      //printf（"the len is %d\n", sizeof(enc));
     printf("Encrypt complete:%s\n",enc);
      //printf("des encode:%s\n", output);
      //输出加密以后的内容
      int i;
      for (i = 0; i < len; ++i)
        printf("%c", output[i]);
      printf("\n");

      
      */

      //解密
      memset((char*)&ivec, 0, sizeof(ivec));
      memcpy((char*)&ivec,"456",sizeof("456"));

      char* input="1zVTMxuj7F2KTpw9kNVCtzET2NV4dWZ2UyRY1012r4YvubRtNp6bFwrB3xd6NflHA_5ltNzG3HXe87ie7ReCbipP_DpWGOLFA_iIefGZ2zCC3fc-A5f2Pg";
      size_t len = (sizeof(input)+7)/8 * 8; 
      DES_ncbc_encrypt(&output, &input, len, &key_schedule, &ivec, DES_DECRYPT);
      
      printf("%s\n", input);

      free(output);
      return EXIT_SUCCESS;
}