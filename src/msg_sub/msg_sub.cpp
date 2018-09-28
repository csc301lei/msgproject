#include "msg_sub.h"

#define CLIENT_ADDR "ipc:///tmp/pubsub_client.ipc"

using namespace std;

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
	int bytes = nn_recv(sock, &data, NN_MSG, 0);
    if (bytes < 0) 
	{
       	fatal("nn_recv");
    }
	//printf("CLIENT: RECEIVED %s\n", data);
    
	nn_close(sock);
}