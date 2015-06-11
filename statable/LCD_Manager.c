#include "LCD_Manager.h"

idata char lcdDisplayBuffer[2][16] = {0};
idata char lcdUpdateRow = 0, lcdUpdateColumn = 0;

void initLcdManager()
{
	char i = 0, j = 0;
	
	initLCD();
	for (i=0; i<2; i++)
	{
		for (j=0; j<16; j++)
		{
			lcdDisplayBuffer[i][j] = 32;	// All initialize to space(character)
		}
	}
}

char* getBuffer()
{
	return &lcdDisplayBuffer[0][0];
}

void lcdUpdateByChar()
{
	if (lcdUpdateRow == 0 && lcdUpdateColumn < 16)
	{
		writeDR(lcdDisplayBuffer[lcdUpdateRow][lcdUpdateColumn]);
		lcdUpdateColumn++;
		//curserRShift();
	}
	else if (lcdUpdateRow == 0 && lcdUpdateColumn == 16)
	{
		//writeDR(lcdDisplayBuffer[lcdUpdateRow][lcdUpdateColumn]);
		lcdUpdateColumn = 0;
		lcdUpdateRow++;
		moveCurser(1, 0);
	}
	else if (lcdUpdateRow == 1 && lcdUpdateColumn < 16)
	{
		writeDR(lcdDisplayBuffer[lcdUpdateRow][lcdUpdateColumn]);
		lcdUpdateColumn++;
		//curserRShift();
	}
	else if (lcdUpdateRow == 1 && lcdUpdateColumn == 16)
	{
		//writeDR(lcdDisplayBuffer[lcdUpdateRow][lcdUpdateColumn]);
		lcdUpdateColumn = 0;
		lcdUpdateRow = 0;
		moveCurser(0, 0);
	}
}

void lcdUpdate()
{
	char i = 0;
	
	moveCurser(0, 0);
	for (i=0; i<16; i++)
	{
		writeDR(lcdDisplayBuffer[0][i]);
	}
	for (i=0; i<16; i++)
	{
		writeDR(lcdDisplayBuffer[1][i]);
	}
}