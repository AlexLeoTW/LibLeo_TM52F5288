#include "Marquee.h"
#include "LCD_Manager.h"

idata unsigned char startColumn = 0;
idata unsigned char startRow = 0;
idata unsigned char endColumn = 0;
idata unsigned char endRow = 0;
idata unsigned char direction = LEFT;
idata char* lcdBuffer;

void setMarquee(unsigned char startX, unsigned char startY, unsigned char endX, unsigned char endY, unsigned char direct)
{
	startColumn = startX;
	startRow = startY;
	endColumn = endX;
	endRow = endY;
	direction = direct;
	lcdBuffer = getBuffer();
}

void marqueeStep()
{
	if (direction == LEFT)
	{
		int i=0, j=0;
		for (i=startRow; i<=endRow; i++)
		{
			char temp = lcdBuffer[i*16 + startColumn];
			for (j=startColumn; j<endColumn-1; j++)
			{
				lcdBuffer[i*16 + j] = lcdBuffer[i*16 + j+1];
			}
			lcdBuffer[i*16 + endColumn] = temp;
		}
	}
	else
	{
		int i=0, j=0;
		for (i=startRow; i<=endRow; i++)
		{
			char temp = lcdBuffer[i*16 + endColumn];
			for (j=endColumn; j>0; j--)
			{
				lcdBuffer[i*16 + j] = lcdBuffer[i*16 + j-1];
			}
			lcdBuffer[i*16 + 0] = temp;
		}
	}
}