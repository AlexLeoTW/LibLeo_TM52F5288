#include "LCD_Manager.h"

char lcdDisplayBuffer[2][16] = {0};
char lcdUpdateRow = 0, lcdUpdateColumn = 0;

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
	return &lcdDisplayBuffer;
}

void lcdUpdateByChar()
{
	if (lcdUpdateRow = 0 && lcdUpdateColumn < 16)
	{
		writeDR(lcdDisplayBuffer[i][j]);
		lcdUpdateColumn++;
		curserRShift();
	}
	else if (lcdUpdateRow = 0 && lcdUpdateColumn == 16)
	{
		writeDR(lcdDisplayBuffer[i][j]);
		lcdUpdateColumn = 0;
		lcdUpdateRow++;
		moveCurser(1, 0);
	}
	else if (lcdUpdateRow = 1 && lcdUpdateColumn < 16)
	{
		writeDR(lcdDisplayBuffer[i][j]);
		lcdUpdateColumn++;
		curserRShift();
	}
	else if (lcdUpdateRow = 1 && lcdUpdateColumn == 16)
	{
		writeDR(lcdDisplayBuffer[i][j]);
		lcdUpdateColumn = 0;
		lcdUpdateRow = 0;
		moveCurser(0, 0);
	}
	else 
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

/*void setMarquee(int startRow, int startColumn, int endColumn, int endRow, char direction)
{
	
}

void updateMarquee()
{
	
}*/