#include<stdio.h>
#include <string.h>
#include<stdlib.h>
struct sensor{
		float axis[3];
}Sensors;

struct proxi{
		float val;
}Proximity;

struct device{
		struct sensor Sensors[3];
		struct proxi Proximity;
};
