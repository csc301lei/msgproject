#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>
#include <iostream>
#include <google/protobuf/message.h>

void fatal(const char *func);

int msg_pub(const char *d, int sz_d);
int msg_pub(const char *d);
int msg_pub(const char * d, google::protobuf::Message &msg);