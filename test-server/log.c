#include "log.h"

zlog_category_t* log_init(){
	int rc;
	zlog_category_t *zc;
	 
    rc = zlog_init("/home/debug_c/libwebsockets/test-server/zlog.conf");
    if (rc) {
        printf("init failed\n");
        return NULL;
    }
	 
    zc = zlog_get_category("websocket");	    
    if (!zc) {
        printf("get cat fail\n");
        zlog_fini();
        return NULL;
    }
    return zc;
}