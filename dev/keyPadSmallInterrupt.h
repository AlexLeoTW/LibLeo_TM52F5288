#ifndef KEYPADSMALLINTUPT_H
#define KEYPADSMALLINTUPT_H

#include "REG320.h"
#include<intrins.h>

#define keyA 10
#define keyB 11
#define keyC 12
#define keyD 13
#define keyHash 99
#define keyStar 20
#define TRUE 1
#define FALSE 0

sbit P1IE = INTE1^1;
sbit PP1H = IP1H^1;

void initKeyPadIO();

void keyValueChanged();

void getKey(char* dest, int size);

unsigned getKeyCnt();

void scanKey();

#endif