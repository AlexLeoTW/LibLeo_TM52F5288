#ifndef LCD_CTRL_H
#define LCD_CTRL_H

#include "REG320.H" 
#include "common.h"

#define DL_8_BIT 1
#define DL_4_BIT 0
#define N_2_LINE 1
#define N_1_LINE 0
#define F_5_BY_7 1
#define F_5_BY_10 0
#define D_LCD_ON 1
#define D_LCD_OFF 0
#define C_CURSER_AC 1
#define C_CURSER_NO 0
#define B_CURSER_FLASH_ON 1
#define B_CURSER_FLASH_OFF 0
#define I_D_AC_SHIFT_RIGHT 1
#define I_D_AC_SHIFT_LEFT 0
#define S_LCD_ROLL_AC_ON 1
#define S_LCD_ROLL_AC_OFF 0
#define Enable 1
#define Disable 0

typedef struct fcs
{
	char DL_8Bit;
	char N_2LineDisp;
	char F_5By7;
	char dispON;
	char curserOnAC;
	char curserFlash;
	char I_D_ACRShiftOnRW;
	char S_dispRShiftRW;
} functionCtlSet;

sbit RS_LCM = P3^5;	//LCM的RS訊號
sbit RW_LCM = P3^6;	//LCM的RW訊號
sbit EN_LCM = P3^7;	//LCM的EN訊號

void initLCD();

functionCtlSet* getFunctionCtl();
void updateLCDCtrlSet();

void printLCD(char* string);
void clearLCD();

void dispRShift();
void dispLShift();

void moveCurser(int row, int column);
void curserReset();
void curserRShift();
void curserLShift();

void setInputMode(unsigned char curserShift, unsigned char lcdRoll);
void setCurserMode(unsigned char dispPsw, unsigned char curserDisp, unsigned char curserFlash);
void setFunction(unsigned char DataLink, unsigned char Num, unsigned char Font);

void writeIR(unsigned instruction);
void writeDR(char dataIn);

#endif