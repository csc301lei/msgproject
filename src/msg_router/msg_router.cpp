#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//#include "router.h"
#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>

#define CLIENT "client"
#define ROUTER "router"
#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"
//#define ROUTER_ADDR "ipc:///tmp/pubsub_router.ipc"
#define ROUTER_ADDR "tcp://*:19001"


void fatal(const char *func)
{
        fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

int router()
{
	int frontend;
    if ((frontend = nn_socket(AF_SP, NN_SUB)) < 0) 
    {
        fatal("nn_socket");
    }
    if (nn_setsockopt(frontend, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) 
    {
           fatal("nn_setsockopt");
    }
    if (nn_bind(frontend, ROUTER_ADDR) < 0) 
    {
        fatal("nn_bind");
   	}
   	
    int backend;
    if ((backend = nn_socket(AF_SP, NN_PUB)) < 0) 
    {
        fatal("nn_socket");
   	}
    if (nn_bind(backend, CLIENT_ADDR) < 0) 
    {
        fatal("nn_bind");
    }
    for(;;)
    {
    	char *buf = NULL;
        nn_recv(frontend, &buf, NN_MSG, 0);
        printf("frontend: %s\n", buf); 
   	 	int sz_buf = strlen(buf) + 1;
  		nn_send(backend, buf, sz_buf, 0);
   		printf("backend: %s\n", buf); 
   		nn_freemsg(buf);
   	}
}

int main(const int argc, const char **argv)
{	
		//if ((argc >= 2) && (strcmp(ROUTER, argv[1]) == 0))
        //{
            router();
		//}
        //return 1;
}
