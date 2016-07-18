编译

gcc example-server.c -o example-server -lpthread   -lwebsockets -L/home/debug_c/libwebsockets/build/lib  -lssl  -L/usr/local/lib `pkg-config --cflags --libs glib-2.0`


gcc example-client.c -o example-clien -lpthread   -lwebsockets -L/home/debug_c/libwebsockets/build/lib  -lssl  -L/usr/local/lib `pkg-config --cflags --libs glib-2.0`