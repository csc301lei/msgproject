#include <iostream>
#include "msg_sub.h"
#include "drone.pb.h"
#include "sensor.pb.h"

using namespace std;

int main(const int argc, const char **argv)
{
    for(;;)
    {
        sensor::Sensor sensor;
        sensor = msg_sub("SENSOR", sensor);
        cout << "CLIENDT RECEIVE : " << sensor.id() << endl;
	}
	return 1;
}

