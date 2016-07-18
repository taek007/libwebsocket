#include "string.h" 
#include "stdio.h" 
#include "time.h" 
#include "stdlib.h" 

#define PLAIN_FILE_OPEN_ERROR -1 
#define KEY_FILE_OPEN_ERROR -2 
#define CIPHER_FILE_OPEN_ERROR -3 
#define OK 1; 

const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

int IP_Table[64] = { 57,49,41,33,25,17,9,1, 
	59,51,43,35,27,19,11,3, 
	61,53,45,37,29,21,13,5, 
	63,55,47,39,31,23,15,7, 
	56,48,40,32,24,16,8,0, 
	58,50,42,34,26,18,10,2, 
	60,52,44,36,28,20,12,4, 
	62,54,46,38,30,22,14,6}; 

int IP_1_Table[64] = {39,7,47,15,55,23,63,31, 
	38,6,46,14,54,22,62,30, 
	37,5,45,13,53,21,61,29, 
	36,4,44,12,52,20,60,28, 
	35,3,43,11,51,19,59,27, 
	34,2,42,10,50,18,58,26, 
	33,1,41,9,49,17,57,25, 
	32,0,40,8,48,16,56,24}; 


int E_Table[48] = {31, 0, 1, 2, 3, 4, 
	3, 4, 5, 6, 7, 8, 
	7, 8,9,10,11,12, 
	11,12,13,14,15,16, 
	15,16,17,18,19,20, 
	19,20,21,22,23,24, 
	23,24,25,26,27,28, 
	27,28,29,30,31, 0}; 

int P_Table[32] = {15,6,19,20,28,11,27,16, 
	0,14,22,25,4,17,30,9, 
	1,7,23,13,31,26,2,8, 
	18,12,29,5,21,10,3,24}; 

int S[8][4][16] = 
	/* S1 */ 
{{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, 
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, 
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}}, 
/* S2 */ 
{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, 
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, 
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}}, 
/* S3 */ 
{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, 
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, 
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, 
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}}, 
/* S4 */ 
{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, 
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, 
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, 
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}}, 
/* S5 */ 
{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, 
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, 
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, 
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}}, 
/* S6 */ 
{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, 
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, 
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, 
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}}, 
/* S7 */ 
{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, 
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, 
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, 
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}}, 
/* S8 */ 
{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, 
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, 
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, 
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}}; 


int PC_1[56] = {56,48,40,32,24,16,8, 
	0,57,49,41,33,25,17, 
	9,1,58,50,42,34,26, 
	18,10,2,59,51,43,35, 
	62,54,46,38,30,22,14, 
	6,61,53,45,37,29,21, 
	13,5,60,52,44,36,28, 
	20,12,4,27,19,11,3}; 

int PC_2[48] = {13,16,10,23,0,4,2,27, 
	14,5,20,9,22,18,11,3, 
	25,7,15,6,26,19,12,1, 
	40,51,30,36,46,54,29,39, 
	50,44,32,46,43,48,38,55, 
	33,52,45,41,49,35,28,31}; 

int MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1}; 
int ByteToBit(char ch,char bit[8]); 
int BitToByte(char bit[8],char *ch); 
int Char8ToBit64(char ch[8],char bit[64]); 
int Bit64ToChar8(char bit[64],char ch[8]); 
int DES_MakeSubKeys(char key[64],char subKeys[16][48]); 
int DES_PC1_Transform(char key[64], char tempbts[56]); 
int DES_PC2_Transform(char key[56], char tempbts[48]); 
int DES_ROL(char data[56], int time); 
int DES_IP_Transform(char data[64]); 
int DES_IP_1_Transform(char data[64]); 
int DES_E_Transform(char data[48]); 
int DES_P_Transform(char data[32]); 
int DES_SBOX(char data[48]); 
int DES_XOR(char R[48], char L[48],int count); 
int DES_Swap(char left[32],char right[32]); 
int DES_EncryptBlock(char plainBlock[8], char subKeys[16][48], char cipherBlock[8]); 
int DES_DecryptBlock(char cipherBlock[8], char subKeys[16][48], char plainBlock[8]); 
char* DES_Encrypt(char *sourceData, int sourceSize, char *keyStr, int *resultSize); 
char* DES_Decrypt(char *sourceData, int sourceSize, char *keyStr, int* resultSize); 

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
int ByteToBit(char ch, char bit[8]){ 
	int cnt; 
	for(cnt = 0;cnt < 8; cnt++){ 
		*(bit+cnt) = (ch>>cnt)&1; 
	} 
	return 0; 
} 

int BitToByte(char bit[8],char *ch){ 
	int cnt; 
	for(cnt = 0;cnt < 8; cnt++){ 
		*ch |= *(bit + cnt)<<cnt; 
	} 
	return 0; 
} 

int Char8ToBit64(char ch[8],char bit[64]){ 
	int cnt; 
	for(cnt = 0; cnt < 8; cnt++){ 
		ByteToBit(*(ch+cnt),bit+(cnt<<3)); 
	} 
	return 0; 
} 


int Bit64ToChar8(char bit[64],char ch[8]){ 
	int cnt; 
	memset(ch,0,8); 
	for(cnt = 0; cnt < 8; cnt++){ 
		BitToByte(bit+(cnt<<3),ch+cnt); 
	} 
	return 0; 
} 

int DES_MakeSubKeys(char key[64],char subKeys[16][48]){ 
	char temp[56]; 
	int cnt; 
	DES_PC1_Transform(key,temp);
	for(cnt = 0; cnt < 16; cnt++){
		DES_ROL(temp,MOVE_TIMES[cnt]);
		DES_PC2_Transform(temp,subKeys[cnt]);
	} 
	return 0; 
} 

int DES_PC1_Transform(char key[64], char tempbts[56]){ 
	int cnt; 
	for(cnt = 0; cnt < 56; cnt++){ 
		tempbts[cnt] = key[PC_1[cnt]]; 
	} 
	return 0; 
} 

int DES_PC2_Transform(char key[56], char tempbts[48]){ 
	int cnt; 
	for(cnt = 0; cnt < 48; cnt++){ 
		tempbts[cnt] = key[PC_2[cnt]]; 
	} 
	return 0; 
} 

int DES_ROL(char data[56], int time){ 
	char temp[56]; 
	memcpy(temp,data,time); 
	memcpy(temp+time,data+28,time); 
	memcpy(data,data+time,28-time); 
	memcpy(data+28-time,temp,time); 
	memcpy(data+28,data+28+time,28-time); 
	memcpy(data+56-time,temp+time,time); 
	return 0; 
} 

int DES_IP_Transform(char data[64]){ 
	int cnt; 
	char temp[64]; 
	for(cnt = 0; cnt < 64; cnt++){ 
		temp[cnt] = data[IP_Table[cnt]]; 
	} 
	memcpy(data,temp,64); 
	return 0; 
} 

int DES_IP_1_Transform(char data[64]){ 
	int cnt; 
	char temp[64]; 
	for(cnt = 0; cnt < 64; cnt++){ 
		temp[cnt] = data[IP_1_Table[cnt]]; 
	} 
	memcpy(data,temp,64); 
	return 0; 
}


int DES_E_Transform(char data[48]){ 
	int cnt; 
	char temp[48]; 
	for(cnt = 0; cnt < 48; cnt++){ 
		temp[cnt] = data[E_Table[cnt]]; 
	} 
	memcpy(data,temp,48); 
	return 0; 
} 

int DES_P_Transform(char data[32]){ 
	int cnt; 
	char temp[32]; 
	for(cnt = 0; cnt < 32; cnt++){ 
		temp[cnt] = data[P_Table[cnt]]; 
	} 
	memcpy(data,temp,32); 
	return 0; 
} 

int DES_XOR(char R[48], char L[48] ,int count){ 
	int cnt; 
	for(cnt = 0; cnt < count; cnt++){ 
		R[cnt] ^= L[cnt]; 
	} 
	return 0; 
} 

int DES_SBOX(char data[48]){ 
	int cnt; 
	int line,row,output; 
	int cur1,cur2; 
	for(cnt = 0; cnt < 8; cnt++){ 
		cur1 = cnt*6; 
		cur2 = cnt<<2; 

		line = (data[cur1]<<1) + data[cur1+5]; 
		row = (data[cur1+1]<<3) + (data[cur1+2]<<2) 
			+ (data[cur1+3]<<1) + data[cur1+4]; 
		output = S[cnt][line][row]; 

		data[cur2] = (output&0X08)>>3; 
		data[cur2+1] = (output&0X04)>>2; 
		data[cur2+2] = (output&0X02)>>1; 
		data[cur2+3] = output&0x01; 
	} 
	return 0; 
} 

int DES_Swap(char left[32], char right[32]){ 
	char temp[32]; 
	memcpy(temp,left,32); 
	memcpy(left,right,32); 
	memcpy(right,temp,32); 
	return 0; 
} 

int DES_EncryptBlock(char plainBlock[8], char subKeys[16][48], char cipherBlock[8]){ 
	char plainBits[64]; 
	char copyRight[48]; 
	int cnt; 
	Char8ToBit64(plainBlock,plainBits); 

	DES_IP_Transform(plainBits); 
	for(cnt = 0; cnt < 16; cnt++){ 
		memcpy(copyRight,plainBits+32,32); 
		DES_E_Transform(copyRight); 
		DES_XOR(copyRight,subKeys[cnt],48); 
		DES_SBOX(copyRight); 
		DES_P_Transform(copyRight); 
		DES_XOR(plainBits,copyRight,32); 
		if(cnt != 15){ 
			DES_Swap(plainBits,plainBits+32); 
		} 
	} 
	DES_IP_1_Transform(plainBits); 
	Bit64ToChar8(plainBits,cipherBlock); 
	return 0; 
} 


int DES_DecryptBlock(char cipherBlock[8], char subKeys[16][48],char plainBlock[8]){ 
	char cipherBits[64]; 
	char copyRight[48]; 
	int cnt; 
	Char8ToBit64(cipherBlock,cipherBits); 
	DES_IP_Transform(cipherBits); 
	for(cnt = 15; cnt >= 0; cnt--){ 
		memcpy(copyRight,cipherBits+32,32); 
		DES_E_Transform(copyRight); 
		DES_XOR(copyRight,subKeys[cnt],48); 
		DES_SBOX(copyRight); 
		DES_P_Transform(copyRight); 
		DES_XOR(cipherBits,copyRight,32); 
		if(cnt != 0){ 
			DES_Swap(cipherBits,cipherBits+32); 
		} 
	} 

	DES_IP_1_Transform(cipherBits); 
	Bit64ToChar8(cipherBits,plainBlock); 
	return 0; 

}

/* 加密 */ 
char* DES_Encrypt(char *sourceData, int sourceSize, char *keyStr, int *resultSize){
	
	char *destData = 0;
	int destSize = sourceSize;
	if(destSize % 8 != 0)
		destSize += (8 - (destSize % 8));
	destData = (char*)malloc(destSize);
	*resultSize = destSize;
	
	int count; 
	char sourceBlock[8], destBlock[8], keyBlock[8]; 
	char bKey[64]; 
	char subKeys[16][48];
	
	memcpy(keyBlock, keyStr, 8);
	Char8ToBit64(keyBlock,bKey); 
	DES_MakeSubKeys(bKey,subKeys);
	int p = 0;
	while(p + 8 <= sourceSize){
		memcpy(sourceBlock, sourceData + p, sizeof(sourceBlock));
		DES_EncryptBlock(sourceBlock, subKeys, destBlock);
		memcpy(destData + p, destBlock, sizeof(destBlock));
		p += 8;
	}
	
	if(p + 8 > sourceSize){
		memset(sourceBlock, '\0', 8);
		// sourceBlock[7] = 8 - (sourceSize % 8);
		memcpy(sourceBlock, sourceData + p, sourceSize % 8);
		DES_EncryptBlock(sourceBlock, subKeys, destBlock);
		memcpy(destData + p, destBlock, sizeof(destBlock));
	}
	
	return destData;
} 

char* DES_Decrypt(char *sourceData, int sourceSize, char *keyStr, int* resultSize){
	
	int count,times = 0; 
	long fileLen; 
	char sourceBlock[8], destBlock[8], keyBlock[8];
	char bKey[64]; 
	char subKeys[16][48];
	char *destData = (char*)malloc(sourceSize);
	*resultSize = sourceSize;
	
	memcpy(keyBlock,keyStr,8); 
	Char8ToBit64(keyBlock,bKey); 
	DES_MakeSubKeys(bKey,subKeys); 
	
	int p = 0;
	while(p < sourceSize){
		memcpy(sourceBlock, sourceData + p, 8);
		DES_DecryptBlock(sourceBlock, subKeys, destBlock);
		memcpy(destData + p, destBlock, 8);
		p+= 8;
	}
	int i;
	for(i=0; i<sourceSize; i++){
		printf("%d ", 0xFF & destData[i]);
	}
	printf("\r\n");
	int nullCnt = destData[*resultSize - 1];
	int realNullCnt = 1;
	int pt = *resultSize - 2;
	int pi = 6;
	while(destData[pt] == '\0' && pi > 0){
		pt--;
		pi--;
		realNullCnt++;
	}
	printf("nullCnt = %d, realNullCnt = %d\r\n", nullCnt, realNullCnt);
	if(nullCnt != realNullCnt){
		printf("aaa null byte count = %d\r\n", realNullCnt);
	}else{
		printf("bbb null byte count = %d\r\n", realNullCnt);
		*resultSize -= realNullCnt;
		char *resultData = (char*)malloc(*resultSize);
		memcpy(resultData, destData, *resultSize);
		free(destData);
		destData = resultData;
	}
	
	return destData;
} 

int main() 
{ 
	char* pSource = "uid=802779641&token=T2a362a4e84d86d3&owner=1084046&version=7.3.8.1&session=712289";
	char *pKey = "abcdefg";
	int sourceLength = strlen(pSource);
	
	char* source = (char*)malloc(sourceLength);
	char key[8];
	memcpy(source, pSource, sourceLength);
	memcpy(key, pKey, 8);
	char *dest;
	int destSize;
	
	printf("Source:%s\n", source);
	int i;
	for(i=0; i<sourceLength; i++){
		//printf("%d ", 0xFF & source[i]);
	}
	printf("\r\n");
	dest = DES_Encrypt(source, sourceLength, key, &destSize);
	char *enc = base64_encode(dest, destSize); 
	printf("Encrypt complete:%s\n",enc);
	for(i=0; i<destSize; i++){
		//printf("%d ", (0xFF & dest[i]));
	}
	//printf("\r\ndestSize = %d\r\n", destSize);
	
	char* dest1 = DES_Decrypt(dest, destSize, key, &destSize);
	printf("destSize = %d\r\n", destSize);
	for(i=0; i<destSize; i++){
		printf("%c", dest1[i]);
	}
	printf("\r\n");
	
	return 0; 
} 