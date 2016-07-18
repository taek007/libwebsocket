#ifndef _BASE64
#define _BASE64
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char* base64_encode(const char* data, int data_len); 
char* base64_decode(const char* data, int data_len);
char find_pos(char ch);
#endif