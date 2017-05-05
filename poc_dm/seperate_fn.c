#include <string.h>
#include<stdlib.h>
#include <stdio.h>
float * buf_seperate(char *buf)
{
	char *token, *ptr;
	int count = 0;
	static float axis[3];
	token = strtok(buf, " ");

	while(token !=NULL)
	{
		if(count == 0)
			axis[0] = strtof(token, &ptr);
			

		else if(count == 1)
			axis[1] = strtof(token, &ptr);
				
		else if(count == 2)
			axis[2] = strtof(token, &ptr);
		
		count++;
		token = strtok(NULL, " ");
	}

//	int i;
//	for ( i = 0 ; i < 3; i++)
//			printf("%f\n",axis[i]);
	return axis;
}
