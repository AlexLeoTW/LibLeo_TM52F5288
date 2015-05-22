#include "common.h"

//延遲副程式
void delay(unsigned int time)
{
  unsigned int n;
	while(time>0)
	{
		n=4; 
		while(n>0) 
			n--;
		time--;
	}
}