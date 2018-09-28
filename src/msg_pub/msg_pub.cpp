#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msg_pub.h"
#include <nn.h>
#include <reqrep.h>
#include <pubsub.h>
#include <pipeline.h>
#include <pthread.h>

#define ROUTER_ADDR "tcp://127.0.0.1:19001"
#define CHECK_NAME "ipc:///tmp/checkname.ipc"

using namespace std;
//std::string topiclist[];

void fatal(const char *func)
{
    fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

bool if_named_topic(const char *topic)
{
    char *buf = NULL;
    int sock;
    int rv;
    int bytes;
    int sz_topic = strlen(topic) + 1;
    if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
        fatal("nn_socket");
    }
    if ((rv = nn_connect (sock, CHECK_NAME)) < 0) {
        fatal("nn_connect");
    }
    if ((bytes = nn_send(sock, topic, sz_topic, 0)) < 0) {
                fatal("nn_send");
    }
    if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
                fatal("nn_recv");
    }
    
    if(strcmp("new", buf) == 0)
    {
        return false;
    }
    if(strcmp("exist", buf) == 0)
    {
        return true;
    }
}

int msg_pub(const char * d, google::protobuf::Message &msg)
{
    //if( if_named_topic(d) )
    //{
    //    printf("Topic name exist! Please rename your topic or longer it…\n");
    //    return 0;
    //}

    
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
    //for (;;) 
    //{
        char buf[4096];
        int sz_d = strlen(d);
        char protodata[4048];
        msg.SerializeToArray(protodata, 4048);
        sprintf(buf, "%s%c%s", d, '|', protodata);
        int len = sz_d + msg.ByteSize() + 1;
        //printf("sz_d is %d, msg.ByteSize() is %d, len is %d.\n", sz_d, msg.ByteSize(), len);
        printf("SERVER: PUBLISHING %s\n",buf);
        int bytes = nn_send(sock, buf, len, 0);
        if (bytes < 0)
        {
            fatal("nn_send");
        }
        sleep(1);
    //}
    nn_close(sock);
}

int msg_pub(const char *topic, const char *d)
{    
    if( if_named_topic(topic) )
    {
        printf("Topic name exist! Please rename your topic or longer it…\n");
        return 0;
    }
    
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
    
        
    //for (;;) 
    //{
        int sz_topic = strlen(topic) + 1;
        int sz_d = strlen(d); // '\0' too
        int len = sz_topic + sz_d + 1;
        char buf[100];
        sprintf(buf,"%s%c%s",topic, '|', d);
        printf("SERVER: PUBLISHING %s\n", buf);
        int bytes = nn_send(sock, buf, len, 0);
        if (bytes < 0) 
        {
            fatal("nn_send");
        }
        sleep(1);
    //}
    nn_close(sock);
}

int msg_pub(const char *d)
{    
    //if( if_named_topic(d) )
    //{
    //    printf("Topic name exist! Please rename your topic or longer it…\n");
    //    return 0;
    //}
        
        int sock;
        if ((sock = nn_socket(AF_SP, NN_PUB)) < 0) 
        {
            fatal("nn_socket");
        }
        if (nn_connect(sock, ROUTER_ADDR) < 0) 
        {
            fatal("nn_connect");
        }
        
        //for (;;) 
        //{
            int sz_d = strlen(d) + 1; // '\0' too
            printf("SERVER: PUBLISHING %s\n",d);
            int bytes = nn_send(sock, d, sz_d, 0);
            if (bytes < 0) 
            {
                fatal("nn_send");
            }
            sleep(1);
        //}
        nn_close(sock);
    //return nn_shutdown(sock, 0);
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
