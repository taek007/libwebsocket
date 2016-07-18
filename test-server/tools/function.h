#ifndef _FUNCTION
#define _FUNCTION
#include <stdlib.h>
#include <string.h>
/**
 *参考 http://blog.csdn.net/wusuopubupt/article/details/17284423
 */

/**
 *拼接两个字符串
 *@params a char* 字符串a
 *@params b char* 字符串b
 *
 *return char*
 *zhangming 2016-7-11
 *
 *记得调用完毕后,释放内存
 */
char *join1(char *a, const  char *b);

#endif