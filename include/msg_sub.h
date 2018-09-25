#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <google/protobuf/message.h>
#include <nn.h>
#include <pubsub.h>
#include <pipeline.h>


void fatal(const char *func);
int msg_sub(const char *topic);

//google::protobuf::Message *T;
//google::protobuf::Message *U;
//template<typename U> U msg_sub( google::protobuf::Message *U , const char *topic );
//template<typename T> void parse(google::protobuf::Message *T, const char *topic, int j);

template<typename U> U msg_sub(const U &msg, const char *topic);
template<typename T> void parse(const T &msg, const char *topic, int j);
