#include "common.h"

//延遲副程式
void delay(unsigned time)
{
  unsigned n;
	while(time>0)
	{
		n=4; 
		while(n>0) 
			n--;
		time--;
	}
}

//Power
int pow(int base, int power)
{
	int total = 1;
	
	int i=0;
	for (i=0; i<power; i++)
	{
		total *= base;
	}
	
	return total;
}

//Count String Length
unsigned char strlen(char* string)
{
	unsigned char position = 0;
	
	while (string[position] != '\0' )
	{
		position++;
	}
	return position;
}