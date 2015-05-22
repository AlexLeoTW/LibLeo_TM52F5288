#include "keyPadBigInterrupt.h"

char keyPressed = FALSE;
unsigned keyValue = 0;
unsigned keyBuffer = 0;
unsigned char pressedColumn[] = {FALSE, FALSE, FALSE, FALSE};
unsigned char pressedRow[] = {FALSE, FALSE, FALSE, FALSE};
unsigned char p1Ctrl[i] = {0xef, 0xdf, 0xbf, 0x7f};
unsigned keyTable[][] = {
	{ 1, 2 , 3, KeyA }, 
	{ 4, 5 , 6, KeyB }, 
	{ 7, 8 , 9, KeyC }, 
	{ keyHash, 0 , keyStar, KeyD }
}

void initKeyPadIO()
{
	P1MODH = 0xaa; 		// PORT1高四位設為CMOS output
	P1MODL = 0x00; 		// PORT1低四位設為Open Drain (others pin) with internal pull up resistor	
	P1 = 0x00;			// Global Interrupt Enable
	P1IE = 1;			// PORT1 PIN CHANGE Interrupt ENABLE
	P1WKUP = 0x00;		// PORT1 低四位之PIN設為中斷觸發
	PP1H = 1;			// PORT1 PIN CHANGE Interrupt優先權設為1表示於所有中斷中 優先權較高
	INTFLG = 0x00		// 所有中斷旗標初始值設為零
}

void keyValueChanged() Interrupt 8
{
	if (keyPressed == FALSE)
	{
		keyPressed = TRUE;
		keyBuffer = getKey();
	}
	else
	{
		keyPressed = FALSE;
		keyValue = keyBuffer;
	}
}

void getKey(char* dest, int size)
{
	char i = 0, j = 0;
	char keyCnt = 0;
	
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if ( pressedRow[i] && pressedColumn[i] && keyCnt<size )
			{
				dest[keyCnt] = keyTable[i][j];
				keyCnt++;
			}
		}
	}
}

unsigned getKeyCnt()
{
	char map[][] = {0};
	char keyCnt = 0;
	
	char i = 0, j = 0;
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if ( pressedRow[i] && pressedColumn[i] )
			{
				keyCnt++;
			}
		}
	}
	
	return keyCnt;
}

void scanKey()
{
	unsigned char columnStatus = 0;
	unsigned char rowStatus = 0;
	
	short i = 0;
	for (i=0; i< 4; i++)
	{
		pressedColumn[i] = FALSE;
		pressedRow[i] = FALSE;
	}
	
	short i = 0;
	for (i=0; i<4; i++)
	{
		P1 = p1Ctrl[i];
		_nop_();
		_nop_();
		rowStatus = p1;
		rowStatus = rowStatus ^ p1Ctrl[i];
		if (rowStatus != 0)
		{
			pressedRow[i] = TRUE;
		}
	}
	
	P1 = 0x0f;
	_nop_();
	_nop_();
	columnStatus = P1;
	columnStatus = columnStatus & 0x0f;	// extract only columnStatus
	columnStatus = columnStatus ^ 0x0f;	// set only changed bit to 1
	pressedColumn[0] = columnStatus%2;
	pressedColumn[1] = columnStatus/2%2;
	pressedColumn[2] = columnStatus/4%2;
	pressedColumn[3] = columnStatus/8%2;
}