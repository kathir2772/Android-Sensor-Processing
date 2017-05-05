#include"headers.h"
#include<stdio.h>

extern struct device Sensor_Hub[5];
extern int Sensor_Hub_cnt;
extern int Sensors_cnt;

/*void print_X(float);
  void print_Y(float);
  void print_Z(float);
 */
void print_val(void);
static int flag = -1;
char axs[3];
char ch = '\n';
char x_axs = 'X';
char y_axs = 'Y';
char z_axs = 'Z';
char equ = '=';
float val;
FILE *fp2;

void display_fn(void) 
{
	FILE *fp1;
	fp1 = fopen("common_file.txt", "a+");
	fp2 = fopen("output_file.txt", "a+");
	//fp1 = fopen("generic_file.txt", "w");
	int count = 0, i=0;
	char buf[50], *token;
	while(fgets(buf, 50, fp1))
	{

		 if(strstr(buf, "1")){
			fprintf(fp2,"Sensor Hub Id --> 1 ");
			fprintf(fp2,"%c",ch);
		}
		
		else if(strstr(buf, "Accelerometer"))
		{	
			flag = 0;
		//	printf("\nAccelerometer::\n");
		}

		else if(strstr(buf, "Gyroscope"))
		{
			flag = 1;
		//	printf("\nGyroscope::\n");
		}		

		else if(strstr(buf, "Magneto Sensor"))
		{
			flag = 2;
		//	printf("\nMagneto Sensor::\n");
		}

		else if(strstr(buf, "Proximity")){
				fprintf(fp2,"Proximity ");
				fprintf(fp2,"%c",equ);
				val  = Sensor_Hub[0].Proximity.val;
				fprintf(fp2, "%f", val);
				fprintf(fp2,"%c",ch);
			//intf("\nProximity :%f\n",Sensor_Hub[0].Proximity.val);
		}


		else if(strstr(buf, ","))
		{
			token = strtok(buf, " ,");
			while( token != NULL)
			{
				if( (strcmp(token,"x") == 0) || (strcmp(token,"X") == 0))
					axs[i++] = 'x';					

				else if( (strncmp(token,"y",1) == 0) || (strncmp(token,"Y",1) == 0))
					axs[i++] = 'y';					

				else if( (strncmp(token,"z",1) == 0) || (strncmp(token,"Z",1) == 0))
					axs[i++] = 'z';					

				token = strtok(NULL, " ,");
			}
		}
	}
	print_val();
	return ;
}

void print_val()
{
fp2 = fopen("output_file.txt","w+");
	int i;
	if(flag >= 0)
	{
		for(i=0; i<3; i++)
		{
			if(axs[i] == 'x')
			{
				//printf("X Axis :: %f\n",Sensor_Hub[0].Sensors[flag].axis[0]);
				val = Sensor_Hub[0].Sensors[flag].axis[0]; 
				fprintf(fp2,"%c",x_axs);
				fprintf(fp2,"%c",equ);
				fprintf(fp2, "%f", val);
				fprintf(fp2,"%c",ch);
				//fwrite(&val, sizeof(val) ,1 ,fp2);
				//printf("|||___%f\n",val);
				//fwrite(&ch, sizeof(ch), 1, fp2);
			}

			if(axs[i] == 'y')
			{
				val = Sensor_Hub[0].Sensors[flag].axis[1];
				fprintf(fp2,"%c",y_axs);
				fprintf(fp2,"%c",equ);
				fprintf(fp2, "%f", val);
				fprintf(fp2,"%c",ch);
				//printf("___%f\n",val);
				//fwrite(&val, sizeof(val),1 ,fp2);
				//fwrite(&ch, sizeof(ch), 1, fp2);

			}
			if(axs[i] == 'z')

			{
				val = Sensor_Hub[0].Sensors[flag].axis[2];
				fprintf(fp2,"%c",z_axs);
				fprintf(fp2,"%c",equ);
				fprintf(fp2, "%f", val);
				fprintf(fp2,"%c",ch);
				//printf("___%f\n",val);
				//fwrite(&val, sizeof(val) ,1 ,fp2);
				//fwrite(&ch, sizeof(ch), 1, fp2);
			}

		}

	}
	printf("\ncompleted\n");
}


