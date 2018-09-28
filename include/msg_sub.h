#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <nn.h>
#include <pubsub.h>
#include <reqrep.h>
#include <pipeline.h>
#include <iostream>
#include <pthread.h>
#include <google/protobuf/message.h>
#include "fatal.h"

#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"

template<typename T> void parse(const T &msg, const char *topic, int j);
int msg_sub(const char *topic, const char *data);

template<typename U> U msg_sub(const char *topic, U &msg)
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
	char *buf = NULL;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);
    if (bytes < 0) 
	{
       	fatal("nn_recv");
    }
	//printf("CLIENT: RECEIVED %s\n", buf);

	int i = 0;
	int j = 0;
	for (i = 0;i < NN_MSG;i++)
	{
		if (buf[i] == '|')
		{
			j = i + 1;
			break;
		}
	}
	msg.ParseFromArray(buf + j, 4096 - j);
	//printf("CLIENT: RECEIVED ok\n"); 
    nn_freemsg(buf);
    
	nn_close(sock);
	return msg;
}