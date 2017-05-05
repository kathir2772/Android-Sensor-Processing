#include <json/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true 1
#include "headers.h"

extern struct device Sensor_Hub[5];
extern int Sensor_Hub_cnt;
extern int Sensors_cnt;
float *buf_seperate(char *buf);
void json_parse(json_object * jobj); 

void json_parse_array( json_object *jobj, char *key) {
	static int cnt = 0;
	enum json_type type;
	const char *cpy = NULL;
	json_object *jarray = jobj; 
	if(key) {
		jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
	}	
	int arraylen = json_object_array_length(jarray);
	int i;
	json_object *jvalue;
	for (i=0; i< arraylen; i++){
		jvalue = json_object_array_get_idx(jarray, i);
		type = json_object_get_type(jvalue);
		cpy = json_object_get_string(jvalue);
		if (type == json_type_array) {
			json_parse_array(jvalue, NULL);
		}
		else if (type != json_type_object) {
			printf("hi\n");
		}
		else {
			json_parse(jvalue);
		}
	}
}





void json_parse(json_object * jobj) 
{

	static int cnt = 0;
	int exists;
	enum json_type type;
	char buf[20];
	int i;
	json_object *new_obj;
	json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
		type = json_object_get_type(val);	
		const char *key_str = NULL;
		switch (type) {
			case json_type_boolean: 
			case json_type_double: 
			case json_type_int: 
			case json_type_string: exists = json_object_object_get_ex(jobj , "Accelerometer",&new_obj);
					       if(exists==true) { 
						       strcpy(buf , json_object_get_string(val));
						       float *axis= buf_seperate(buf);
						       for ( i = 0 ; i < 3 ; i++)
							       //printf("%f\n",axis[i]);
							       Sensor_Hub[Sensor_Hub_cnt].Sensors[0].axis[i] = axis[i];
					       }
					       exists = json_object_object_get_ex(jobj , "Gyroscope",&new_obj);
					       if(exists==true) {
						       strcpy(buf , json_object_get_string(val));
						       float *axis= buf_seperate(buf);
						       for ( i = 0 ; i < 3 ; i++)
							       Sensor_Hub[Sensor_Hub_cnt].Sensors[1].axis[i] = axis[i];
					       }
					       exists = json_object_object_get_ex(jobj , "Magneto sensor",&new_obj);
					       if(exists==true) {
						       strcpy(buf , json_object_get_string(val));
						       float *axis= buf_seperate(buf);
						       for ( i = 0 ; i < 3 ; i++)
							       Sensor_Hub[Sensor_Hub_cnt].Sensors[2].axis[i] = axis[i];
					       }
					       exists = json_object_object_get_ex(jobj , "GPS",&new_obj);
					       if(exists==true) {
						       strcpy(buf , json_object_get_string(val));
						       float *axis= buf_seperate(buf);
						       for ( i = 0 ; i < 3 ; i++)
							       Sensor_Hub[Sensor_Hub_cnt].Sensors[3].axis[i] = axis[i];
					       }
					       exists = json_object_object_get_ex(jobj , "Proximity",&new_obj);
					       if(exists==true) {
							char *ptr;
						       strcpy(buf , json_object_get_string(val));
						       //printf("Proximity --> %s\n",buf);
							Sensor_Hub[Sensor_Hub_cnt].Proximity.val = strtof(buf,&ptr);
					       }
					       exists = json_object_object_get_ex(jobj , "Uncalibrated",&new_obj);
					       if(exists==true) {
						       strcpy(buf , json_object_get_string(val));
						       //													   printf("uncalibrated --> %s\n",buf);
					       }
						break;


			case json_type_array: //printf("|||||%d\n",cnt++);
					       json_parse_array(jobj, key);
					       break;
		}
	}
} 
