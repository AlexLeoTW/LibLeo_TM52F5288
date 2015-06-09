#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include "LCD_Ctrl.h"

void initLcdManager();

char* getBuffer();

void lcdUpdateByChar();

void lcdUpdate();

#endif