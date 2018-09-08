#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msg_sub.h"
#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>


#define NANOSUB "nanosub"
#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"

void fatal(const char *func)
{
        fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

int msg_sub(const char *topic)
{
        int sock;

        if ((sock = nn_socket(AF_SP, NN_SUB)) < 0) {
                fatal("nn_socket");
        }

        // subscribe to everything ("" means all topics)
        int sz_topic = strlen(topic); 
        
        if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, topic, sz_topic) < 0) {
                fatal("nn_setsockopt");
        }
        
        if (nn_connect(sock, CLIENT_ADDR) < 0) {
                fatal("nn_connet");
        }
        for (;;) {
        		
                char *buf = NULL;
                int bytes = nn_recv(sock, &buf, NN_MSG, 0);
                if (bytes < 0) {
                        fatal("nn_recv");
                }
                printf("CLIENT: RECEIVED %s\n", buf); 
                nn_freemsg(buf);
        }
}

int main(const int argc, const char **argv)
{
    
        if ((argc >= 2) && (strcmp(NANOSUB, argv[1]) == 0))
        {
            msg_sub(argv[2]);
		}
	
		
        //fprintf(stderr, "Usage: pubsub %s|%s <URL> <ARG> ...\n",
        //    SERVER, CLIENT);
        return 1;
}
