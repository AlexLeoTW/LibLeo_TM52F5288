#include "LCD_Ctrl.h"

/*********************************
struct functionCtlSet
{
	char DL_8Bit;
	char N_2LineDisp;
	char F_5By7;
	char dispON;
	char curserOnAC;
	char curserFlash;
	char I_D_ACRShiftOnRW;
	char S_dispRShiftRW;
};
*********************************/
functionCtlSet functionCtl = { DL_8_BIT, N_2_LINE, F_5_BY_7, D_LCD_ON, C_CURSER_AC, B_CURSER_FLASH_OFF,I_D_AC_SHIFT_RIGHT, S_LCD_ROLL_AC_ON };
functionCtlSet modedCtl = { DL_8_BIT, N_2_LINE, F_5_BY_7, D_LCD_ON, C_CURSER_AC, B_CURSER_FLASH_OFF,I_D_AC_SHIFT_RIGHT, S_LCD_ROLL_AC_ON };
/*{
	.DL_8Bit = DL_8_BIT,
	.N_2LineDisp = N_2_LINE, 
	.F_5By7 = F_5_BY_7, 
	.dispON = D_LCD_ON, 
	.curserOnAC = C_CURSER_AC, 
	.curserFlash = B_CURSER_FLASH_ON,
	.I_D_ACRShiftOnRW = I_D_AC_SHIFT_RIGHT, 
	.S_dispRShiftRW = S_LCD_ROLL_AC_ON
};*/
unsigned char lcdLineCnt = 2;

void initLCD()
{
	p0oe = 0xff;
	P3MODH = 0xA8; //#10101000B	7~5 OUTPUT
	P0 = 0x00;
	P3 = 0x00;
	
	delay(20);
	
	setFunction(DL_8_BIT, N_2_LINE, F_5_BY_10);
	//功能設定：設定DL=N=1,F=0 : 使用八位元, 雙排顯示, 5*10字型(無效)
	
	setCurserMode(D_LCD_OFF, C_CURSER_NO, B_CURSER_FLASH_OFF);
	//顯示器控制：D=C=B=0 : 顯示器OFF, 沒有游標(無效), 不閃爍(無效)
	
	clearLCD();
	//清除顯示
	
	setInputMode(I_D_AC_SHIFT_RIGHT, S_LCD_ROLL_AC_OFF);
	//模式設定：I/D=1, S=0 : RW右移, Roll關閉
	
	setCurserMode(D_LCD_ON, C_CURSER_AC, B_CURSER_FLASH_OFF);
	//顯示器控制：D=C=1, B=0 : 顯示器ON, 游標@AC, 不閃爍
	
}

functionCtlSet* getFunctionCtl()
{
	return &modedCtl;
}

void updateLCDCtrlSet()
{
	if ( (modedCtl.DL_8Bit != functionCtl.DL_8Bit)  || (modedCtl.N_2LineDisp != functionCtl.N_2LineDisp) || (modedCtl.F_5By7 != functionCtl.F_5By7) )
	{
		functionCtl.DL_8Bit = modedCtl.DL_8Bit;
		functionCtl.N_2LineDisp = modedCtl.N_2LineDisp;
		functionCtl.F_5By7 = modedCtl.F_5By7;
		setFunction(modedCtl.DL_8Bit, modedCtl.N_2LineDisp, modedCtl.F_5By7);
	}
		
	if ( (modedCtl.dispON != functionCtl.dispON)  || (modedCtl.curserOnAC != functionCtl.curserOnAC) || (modedCtl.curserFlash != functionCtl.curserFlash) )
	{
		functionCtl.dispON = modedCtl.dispON;
		functionCtl.curserOnAC = modedCtl.curserOnAC;
		functionCtl.curserFlash = modedCtl.curserFlash;
		setCurserMode(modedCtl.dispON, modedCtl.curserOnAC, modedCtl.curserFlash);
	}
	
	if ( (modedCtl.I_D_ACRShiftOnRW != functionCtl.I_D_ACRShiftOnRW)  || (modedCtl.S_dispRShiftRW != functionCtl.S_dispRShiftRW) )
	{
		functionCtl.I_D_ACRShiftOnRW = modedCtl.I_D_ACRShiftOnRW;
		functionCtl.S_dispRShiftRW = modedCtl.S_dispRShiftRW;
		setInputMode(modedCtl.I_D_ACRShiftOnRW, modedCtl.S_dispRShiftRW);
	}
}

void printLCD(char* string)
{
	char len = strlen(string);
	char i=0;
	
	for (i=0; i<len; i++)
	{
		writeDR(string[i]);
	}
}

void clearLCD()
{
	writeIR(1);
}

void dispRShift()
{
	writeIR(0x11);	// right shift display & courser
	writeIR(0x00);	// courser left shift
}

void dispLShift()
{
	writeIR(0x10);	// left shift display & courser
	writeIR(0x04);	// courser right shift
}

void moveCurser(int row, int column)
{
	if (functionCtl.N_2LineDisp == N_2_LINE)
	{
		writeIR( pow(2, 7) + (row)*pow(2, 6) + (column)*pow(2, 0) );
	}
	else if (functionCtl.N_2LineDisp == N_1_LINE)
	{
		if (column <= 8)
		{
			writeIR( pow(2, 7) + (column)*pow(2, 0) );
		}
		else
		{
			writeIR( pow(2, 7) + pow(2, 6) + (column)*pow(2, 0) );
		}
	}
}

void curserReset()
{
	writeIR(0x02);
}

void curserRShift()
{
	writeIR(0x13);
}

void curserLShift()
{
	writeIR(0x12);
}

void setInputMode(unsigned char curserShift, unsigned char lcdRoll)
{
	writeIR( 4 + curserShift*2 + lcdRoll );
}

void setCurserMode(unsigned char dispPsw, unsigned char curserDisp, unsigned char curserFlash)
{
	writeIR( 8 + dispPsw*4 + curserDisp*2 + curserFlash );
}

void setFunction(unsigned char DataLink, unsigned char Num, unsigned char Font)
{
	writeIR( 32 + DataLink*16 + Num*8 + Font*4 );
}

void writeIR(unsigned instruction)
{
	RS_LCM = 0;					// RS=0 選擇指令暫存器
	RW_LCM = 0;					// RW=0 選擇進行寫入動作
	EN_LCM = 1;					// EN=1 開啟LCM讀寫功能
	P0 = instruction;		// 將A的值由P0送出 = 送出命令碼	
	delay(10);						// 等候一段時間，讓資料完成寫入動作
	EN_LCM = 0;					// EN=0 關閉LCM讀寫功能
	// The LCD Module is Fall Edge Tragger
	//P2 = instruction;
}

void writeDR(char dataIn)
{
	RS_LCM = 1;					// RS=1 選擇資料記憶體
	RW_LCM = 0;					// RW=0 選擇進行寫入動作
	EN_LCM = 1;					// EN=1 開啟LCM讀寫功能
	P0 = dataIn;		// 將A的值由P0送出 = 送出命令碼	
	delay(10);						// 等候一段時間，讓資料完成寫入動作
	EN_LCM = 0;					// EN=0 關閉LCM讀寫功能
	// The LCD Module is Fall Edge Tragger
}