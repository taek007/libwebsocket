/**
 *glib.h找不到
 * pkg-config --cflags glib-2.0
-I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include  
  gcc example-server.c url_parser.c -o example-server -lpthread   -lwebsockets -L/home/debug_c/libwebsockets/build/lib  -lssl  -L/usr/local/lib `pkg-config --cflags --libs glib-2.0` 


  gcc example-server.c url_parser.c -o example-server -lpthread   -lwebsockets -L/home/debug_c/libwebsockets-master/build/lib  -lssl  -L/usr/local/lib `pkg-config --cflags --libs glib-2.0` 
  
 http://kimux.net/?p=826

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "glib.h"
//#include "url_parser.h"
#include "test-server.h"

#include "../lib/libwebsockets.h"
//#include "../lib/private-libwebsockets.h"

#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KMAG "\033[0;35m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define RESET "\033[0m"

static int destroy_flag = 0;




static void INT_HANDLER(int signo) {
    destroy_flag = 1;
}

/* *
 * websocket_write_back: write the string data to the destination wsi.
 */
int websocket_write_back2(struct lws *wsi_in, char *str, int str_size_in) 
{
    if (str == NULL || wsi_in == NULL)
        return -1;

    int n;
    int len;
    unsigned char *out = NULL;

    if (str_size_in < 1) 
        len = strlen(str);
    else
        len = str_size_in;

    out = (unsigned char *)malloc(sizeof(unsigned char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
    //* setup the buffer*/
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out*/
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);

    //printf(KBLU"[websocket_write_back] %s\n"RESET, str);
    //* free the buffer*/
    free(out);

    return n;
}

GHashTable* table=NULL;
static GHashTable* get_ghash_table(){
    return table;
}


GArray * sockfd_array = NULL;
static GArray* get_sockfd_array(){
    return sockfd_array;
}

static struct libwebsocket* wsis[100];
static int client_count = 0;

static void send_to_all_client(gpointer key, gpointer value ,gpointer user_data){

    //http://blog.chinaunix.net/uid-24774106-id-3605760.html
    printf("the key is %s, \n", (char*)key);

}

static void free_data(gpointer hash_data)
{
    g_free(hash_data);
    hash_data = NULL;
}

static int callback_chat(
        struct lws *wsi,
        enum lws_callback_reasons reason, void *user,
                               void *in, size_t len)
{
    //lwsl_notice("%s\n", reason_strings[reason]);
    
//GHashTable* table = get_ghash_table();

GArray* sockfd_array = get_sockfd_array();

//int m= g_hash_table_size(table);
//printf("hash len is %d\n",m);
//char name[20];
//printf("reason %d\n",reason);
    switch (reason) 
    {
        // 新規接続
        case LWS_CALLBACK_ESTABLISHED:
            {
                /**
                 *glib使用详见http://www.cnblogs.com/wangkangluo1/archive/2011/07/09/2101983.html
                 */
                //ii=5;
                //wsis[client_count++]=wsi;

                  //printf("%x\n",table);
                  //char*host_name=lws_canonical_hostname(lws_get_context(wsi));
                 // printf("host_name =%s", host_name);
//lws_client_connect_info

                  int client_sockfd=lws_get_socket_fd(wsi);
                  //printf("host_sockfd = %d\n", host_sockfd);

                  
                  //sprintf(name, "%d", host_sockfd);
                  //char *key;  
                  //key=g_strdup(name);

                //gint* key = g_new(gint, host_sockfd);                   
               // g_hash_table_insert(table, key, key);

                //http://blog.csdn.net/plusboy/article/details/1491508
                  //http://www.cnphp6.com/archives/104607

                  //http://www.cnblogs.com/wangkangluo1/archive/2011/07/09/2101983.html
                  
                g_array_append_val(sockfd_array, client_sockfd);
                printf("the array len is %d\n", sockfd_array->len);

                /**
                 *glib 数组http://blog.csdn.net/plusboy/article/details/1491508
                 */
                 
                //char* Bean_score = g_hash_table_lookup(table,"7");
                //printf("find the key is %s\n", Bean_score);
                
                //g_hash_table_foreach(table,send_to_all_client,NULL);
                 char*p;
                 int port=0;
                 const char *prot, *ads = NULL, *path;
                 p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_GET_URI);
                 printf("the httpis %s\n",p);
                 struct parsed_url *pu=NULL;
                 pu=lws_parse_uri(p, &prot, &ads, &port, &path);
                printf("%s\n", prot);
                 printf("%s\n", ads);
                 printf("%d\n", port);
                printf("%s\n", path);

                /**
                 *enum lws_token_indexes 
                 WSI_TOKEN_CONNECTION  Upgrade
                 WSI_TOKEN_UPGRADE  websocket
                 WSI_TOKEN_PROTOCOL my-echo-protocol  
                 WSI_TOKEN_KEY GA78GtRaICleOqOJ4pll2w== 
                */
                 const char *hostname = lws_hdr_simple_ptr(wsi, WSI_TOKEN_KEY);
                 printf("the host is %s\n", hostname);

                 const char* meth;
                 meth = lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_URI);
                 printf("the method is %s\n", meth);

               
                 //printf("the true host is %s\n",wsi->u.hdr.stash->host);

              
            }
            break;
        // クローズ
        case LWS_CALLBACK_PROTOCOL_DESTROY:
            {
                  int host_sockfd=lws_get_socket_fd(wsi);
                  printf("destory = %d\n", host_sockfd);
            }
            break;
        // 送信処理
        case LWS_CALLBACK_SERVER_WRITEABLE:
            {
               // websocket_write_back(wsi, (char *)in,-1);
            }
            break;
        // 受信処理
        case LWS_CALLBACK_RECEIVE:
            {
                lwsl_notice("接收到客户端的信息=[%s]\n",(const char*)in);
             
                //int j;
               // for(j=0;j<100;j++){
                    //websocket_write_back(wsis[j], (char *)in,-1);
              //  }
                //g_hash_table_foreach(table,send_to_all_client,NULL);
               // for (j = 0; j < queue->length; j++){
                  //  websocket_write_back(*(gint *)g_queue_peek_nth(queue, j),(char *)in,-1 );
               // }
                //lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));
            }
            break;
        // えーと、えーと、
        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            {
                //dump_handshake_info(wsi);
            }
            break;
         case LWS_CALLBACK_CLOSED:{

             int host_sockfd=lws_get_socket_fd(wsi);
                  printf("LWS_CALLBACK_CLOSED  = %d\n", host_sockfd);
         }
        default:
            {
            }
            break;
    }
 
    return 0;
}

static int ws_service_callback(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len)
{

    switch (reason) {

        case LWS_CALLBACK_ESTABLISHED:
            printf("[Main Service] Connection established\n");
            break;

        //* If receive a data from client*/
        case LWS_CALLBACK_RECEIVE:
            printf("接收到客户端的信息:%s\n",(char *)in);

            //* echo back to client*/
            websocket_write_back(wsi ,(char *)in, -1);

            break;
    case LWS_CALLBACK_CLOSED:
            printf("[Main Service] Client close.\n");
        break;

    default:
            break;
    }

    return 0;
}

struct per_session_data {
    int fd;
};

int main(void) {
    // server url will usd port 5000
    int port = 5000;

    table= g_hash_table_new_full(g_str_hash,g_str_equal,free_data,free_data);
    //printf("the main table is %x\n",table);

    sockfd_array = g_array_new(FALSE, TRUE, sizeof(int));

    const char *interface = NULL;
    struct lws_context_creation_info info;
    struct lws_protocols protocol;
    struct lws_context *context;
    // Not using ssl
    const char *cert_path = NULL;
    const char *key_path = NULL;
    // no special options
    int opts = 0;


    //* register the signal SIGINT handler */
    struct sigaction act;
    act.sa_handler = INT_HANDLER;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction( SIGINT, &act, 0);

    //* setup websocket protocol */
    protocol.name = "my-echo-protocol";
    protocol.callback = callback_lws_mirror;
    protocol.per_session_data_size=sizeof(struct per_session_data);
    protocol.rx_buffer_size = 0;




    //* setup websocket context info*/
    memset(&info, 0, sizeof info);
    info.port = port;
    info.iface = interface;
    info.protocols = &protocol;
    info.extensions = lws_get_internal_extensions();
    info.ssl_cert_filepath = cert_path;
    info.ssl_private_key_filepath = key_path;
    info.gid = -1;
    info.uid = -1;
    info.options = opts;

    //* create libwebsocket context. */
    context = lws_create_context(&info);
    if (context == NULL) {
        printf(KRED"[Main] Websocket context create error.\n"RESET);
        return -1;
    }

    printf(KGRN"[Main] Websocket context create success.\n"RESET);

    //* websocket service */
    while ( !destroy_flag ) {
        lws_service(context,0);
    }
    usleep(10);
    lws_context_destroy(context);

    return 0;
}
        