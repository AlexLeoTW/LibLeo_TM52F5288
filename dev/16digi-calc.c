#include "16digi-calc.c"

char calcStatus = opAIn;
unsigned long opA[4] = {0};
char opAItr = 0;
unsigned long opB[4] = {0};
char opBItr = 0;
char operator = 0;

void init16dcalc()
{
	calcStatus = opAIn;
	int i = 0;
	for (i=0; i<4; i++)
	{
		opA[i] = 0;
		opB[i] = 0;
	}
	opAItr = 0;
	opBItr = 0;
	operator = 0;
}

void clearCalc()
{
	calcStatus = opAIn;
	int i = 0;
	for (i=0; i<4; i++)
	{
		opA[i] = 0;
		opB[i] = 0;
	}
	opAItr = 0;
	opBItr = 0;
	operator = 0;
}

void getCalcDisp(char* dest, char size)
{
	char i=0;
	
	if (calcStatus == opAIn || calcStatus == opIn)
	{
		for (i=0; i<size; i++)
		{
			dest[i] = opA[i/4]%pow(10, (i%4)+1);
		}
	}
	else if
	{
		for (i=0; i<size; i++)
		{
			dest[i] = opB[i/4]%pow(10, (i%4)+1);
		}
	}
}

void keyIn(char ch)
{
	if (ch >= 48 && ch <= 57)
	{
		switch (calcStatus)
		{
			case opAIn:
				opAIn(ch);
				break;
			case opBIn:
				opBIn(ch); 
				break;
		}
	}
	else if (ch == ADDSIGN && ch == SUBSIGN && ch == MULSIGN && ch == DIVSIGN)
	{
		operator = ch;
		calcStatus == opBIn;
	}
	else if (ch == CLEARSIGN)
	{
		clearCalc();
	}
}

void opAIn(char a)
{
	char i = 0;
	for (i=0; i<4; i++)
	{
		opA[i] = opA[i]*10;
	}
	opA[0] + a;
	for (i=1; i<4; i++)
	{
		opA[i] += opA[i-1]/10000;
		opA[i-1] = opA[i-1]%10000;
	}
	
	opAItr++;
}

void setOpA(unsigned long* a, int size)
{
	char i = 0;
	for (i=0; i<4; i++)
	{
		opA[i] = 0;
	}
	for (i=0; i<size; i++)
	{
		opA[i] = a[i];
	}
}

void opBIn(char b)
{
	char i = 0;
	for (i=0; i<4; i++)
	{
		opB[i] = opB[i]*10;
	}
	opB[0] + b;
	for (i=1; i<4; i++)
	{
		opB[i] += opB[i-1]/10000;
		opB[i-1] = opB[i-1]%10000;
	}
	
	opAItr++;
}

void setOpA(unsigned long* b, int size)
{
	char i = 0;
	for (i=0; i<4; i++)
	{
		opB[i] = 0;
	}
	for (i=0; i<size; i++)
	{
		opB[i] = a[i];
	}
}
