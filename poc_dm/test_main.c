#include <json/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

struct device Sensor_Hub[5];
int Sensor_Hub_cnt = 0;
int Sensors_cnt = 0;


void json_parse_array( json_object *jobj, char *key);
void json_parse(json_object * jobj); 
void display_fn(void); 

int main(void)
{
	int dev_cnt = 1;
//	Sensor_Hub = malloc (dev_cnt * sizeof(struct device));

	FILE *fp = fopen( "file.json", "r" );
	fseek(fp,0,2);
	int cnt = ftell(fp);
	fseek(fp , 0 , 0);
	char *string = (char *)malloc(cnt+1); //allocating memory for json string
	fread(string ,cnt  , 1 ,fp);
	json_object * jobj = json_tokener_parse(string);     
	json_parse(jobj);
	printf("\n");
	int i;
	display_fn(); 
	/*for(i=0; i<3; i++)
		printf("%f\n", Sensor_Hub[0].Sensors[0].axis[i]);
	for(i=0; i<3; i++)
		printf("%f\n", Sensor_Hub[0].Sensors[1].axis[i]);
	for(i=0; i<3; i++)
		printf("%f\n", Sensor_Hub[0].Sensors[2].axis[i]);*/
}

