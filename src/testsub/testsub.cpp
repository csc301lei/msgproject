#include <iostream>
#include "msg_sub.h"
#include "drone.pb.h"
#include "sensor.pb.h"

int main(const int argc, const char **argv)
{
    for(;;)
    {
        sensor::Sensor sensor;
        sensor = msg_sub("SEBSOR", sensor);
        printf("Sensor id is %d\n", sensor.id);
	}
	return 1;
}

