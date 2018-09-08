#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "msg_pub.h"

#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>

#define SERVER "server"
#define NANOPUB "nanopub"
#define CLIENT "client"
#define ROUTER "router"
#define SERVER_ADDR "ipc:///tmp/pubsub_server.ipc"
#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"
#define ROUTER_ADDR "tcp://127.0.0.1:19001"



void fatal(const char *func)
{
        fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

int msg_pub(const char *d, int sz_d)
{    
       
        int bytes;
        
        int sock;
        if ((sock = nn_socket(AF_SP, NN_PUB)) < 0) 
        {
                fatal("nn_socket");
        }
        if (nn_connect(sock, ROUTER_ADDR) < 0) 
        {
                fatal("nn_connect");
        }
        
        for (;;) 
        {
            int i = 0;
            int len_d = strlen(d);
            for(i = 0; i < len_d; i++)
            {
                if (d[i] == '|')
                {
                    break;
                }
            }
            
            int len = sz_d + i + 1;
             // '\0' too
            
            printf("SERVER: PUBLISHING %s\n",d);
            int bytes = nn_send(sock, d, len, 0);
            if (bytes < 0) 
            {
                    fatal("nn_send");
            }
            //sleep(1);
        }
        return nn_shutdown(sock, 0);
}

int msg_pub(const char *d)
{    
       
        int bytes;
        
        int sock;
        if ((sock = nn_socket(AF_SP, NN_PUB)) < 0) 
        {
                fatal("nn_socket");
        }
        if (nn_connect(sock, ROUTER_ADDR) < 0) 
        {
                fatal("nn_connect");
        }
        
        for (;;) 
        {
            int sz_d = strlen(d) + 1; // '\0' too
            printf("SERVER: PUBLISHING %s\n",d);
            int bytes = nn_send(sock, d, sz_d, 0);
            if (bytes < 0) 
            {
                    fatal("nn_send");
            }
            //sleep(1);
        }
        return nn_shutdown(sock, 0);
}


/*
int main(const int argc, const char **argv)
{
    
	
		if ((argc >= 2) && (strcmp(NANOPUB, argv[1]) == 0))
        {
           msg_pub(argv[2]);
		}
		
        //fprintf(stderr, "Usage: pubsub %s|%s <URL> <ARG> ...\n",
         //   SERVER, CLIENT);
        return 1;
}
*/
