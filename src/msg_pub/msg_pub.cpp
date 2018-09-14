#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "msg_pub.h"

#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>


#define ROUTER_ADDR "tcp://127.0.0.1:19001"

using namespace std;
//std::string topiclist[];

void fatal(const char *func)
{
    fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

int msg_pub(const char * d, google::protobuf::Message &msg){
	
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
    //printf("msgpub ok1\n");
    for (;;) 
    {
        char buf[4096];
        int sz_d = strlen(d);
        char protodata[4048];
        //printf("msgpub ok2\n");
        msg.SerializeToArray(protodata, 4048);
        //printf("msgpub ok3\n");
        sprintf(buf, "%s%c%s", d, '|', protodata);
        //printf("msgpub ok4\n");
        int len = sz_d + msg.ByteSize() + 1;
        printf("sz_d is %d, msg.ByteSize() is %d, len is %d.\n", sz_d, msg.ByteSize(), len);
         
        printf("SERVER: PUBLISHING %s\n",d);
        int bytes = nn_send(sock, buf, len, 0);
        if (bytes < 0)
        {
            fatal("nn_send");
        }
                sleep(1);
    }
    return nn_shutdown(sock, 0);
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
            
            /*
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
            */
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
