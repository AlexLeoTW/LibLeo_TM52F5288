#include "common.h"
#include "seg7big.h"
#include <intrins.h>

unsigned char numbers[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xff};   //數字0-9,0xff表示都不亮
unsigned char seg_num[]={0xe0,0xd0,0xb0,0x70};										//控制七段顯示器哪顆亮
char digit[] = {10, 10, 10, 10};
char msdPos = -1;
unsigned char segDisplayCnt = 0;

void initSeg7IO()
{
    p0oe = 0xff;
    P0 = 0xff;
}

//顯示數值在七段顯示器上
void ShowSeg()
{
	unsigned char segIndex = segDisplayCnt%4;
	P0 = seg_num[segIndex] + numbers[digit[segIndex]];
	segDisplayCnt++;
}

unsigned getSeg(void)
{
	unsigned char i = 0;
	unsigned total = 0;
	
	for (i=0; i<=msdPos; i++)
	{
		total += digit[i]*pow(10, i);
	}
	
	return total;
}

void setSeg(unsigned value)
{
	char i=0;
	unsigned char digi = 0;
	
	for (i=0; i<=msdPos; i++)
	{ // 歸零
		digit[i] = 10;
	}
	msdPos = 0;
	
	for (i=3; i>=0; i--)
	{
		digi = (value/pow(10, i))%10;
		
		if (digi != 0)
		{
			msdPos = i;
			break;
		}
	}
	
	for (i=0; i<=msdPos; i++)
	{
		digit[i] = (value/pow(10, i))%10;
	}
}

void appendSeg(unsigned keyValue)
{
	if (msdPos >= 0)
	{
		setSeg(getSeg()*10 + keyValue);
	}
	else
	{
		setSeg(keyValue);
	}
}


unsigned pow(unsigned base, unsigned power)
{
	unsigned i = 0;
	unsigned total = 1;
	
	for (i = 0; i<power; i++)
	{
		total*=base;
	}
	
	return total;
}