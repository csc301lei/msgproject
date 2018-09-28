#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msg_sub.h"
#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>

#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"

using namespace std;

void fatal(const char *func)
{
    fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

//template<typename U> U msg_sub( google::protobuf::Message *U , const char *topic )
template<typename U> U msg_sub(const char *topic, const U &msg)
{
    int sock;
    if ((sock = nn_socket(AF_SP, NN_SUB)) < 0) 
	{
		fatal("nn_socket");
	}

    int sz_topic = strlen(topic); 
    if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, topic, sz_topic) < 0) 
	{
        fatal("nn_setsockopt");
    }
	if (nn_connect(sock, CLIENT_ADDR) < 0) 
	{
        fatal("nn_connet");
    }
    //for (;;) 
	//{
		char *buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        if (bytes < 0) 
		{
        	fatal("nn_recv");
        }
		printf("CLIENT: RECEIVED %s\n", buf);

		//google::protobuf::Message *msg;

		int i = 0;
		int j = 0;
		for (i = 0;i < NN_MSG;i++)
		{
			if (buf[i] = '|')
			{
				j = i + 1;
				break;
			}
		}
		msg->ParseFromArray(buf + j, 4096 - j);
		
		printf("CLIENT: RECEIVED ok\n"); 
        nn_freemsg(buf);
    //}
	nn_close(sock);
}

/*
template<typename T> void parse(const T &msg, const char *topic, int j)
{
	msg->ParseFromArray(topic + j, 4096 - j);
}
int msg_sub(const char *topic)
{
    int sock;
    if ((sock = nn_socket(AF_SP, NN_SUB)) < 0) 
	{
		fatal("nn_socket");
	}

    int sz_topic = strlen(topic); 
    if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, topic, sz_topic) < 0) 
	{
        fatal("nn_setsockopt");
    }
	if (nn_connect(sock, CLIENT_ADDR) < 0) 
	{
        fatal("nn_connet");
    }
    for (;;) 
	{
		char *buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        if (bytes < 0) 
		{
        	fatal("nn_recv");
        }
		printf("CLIENT: RECEIVED %s\n", buf);

		google::protobuf::Message *msg;

		int i = 0;
		int j = 0;
		for (i = 0;i < NN_MSG;i++)
		{
			if (buf[i] = '|')
			{
				j = i + 1;
				break;
			}
		}
		parse(msg, buf, j);
		
		printf("CLIENT: RECEIVED ok\n"); 
        nn_freemsg(buf);
    }
	nn_close(sock);
}
*/
int msg_sub(const char *topic, const char *data)
{
    int sock;
    if ((sock = nn_socket(AF_SP, NN_SUB)) < 0) 
	{
		fatal("nn_socket");
	}

    int sz_topic = strlen(topic); 
    if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, topic, sz_topic) < 0) 
	{
        fatal("nn_setsockopt");
    }
	if (nn_connect(sock, CLIENT_ADDR) < 0) 
	{
        fatal("nn_connet");
    }
    //for (;;) 
	//{
        int bytes = nn_recv(sock, &data, NN_MSG, 0);
        if (bytes < 0) 
		{
        	fatal("nn_recv");
        }
		printf("CLIENT: RECEIVED %s\n", data);
    //}
	nn_close(sock);
}
/*
int main(const int argc, const char **argv)
{
    if (argc >= 1)
    {
        msg_sub(argv[1]);
	}
	
	return 1;
}
*/