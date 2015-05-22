#ifndef KEYPADSMALL_H
#define KEYPADSMALL_H

#include "REG320.h"
#include<intrins.h>

#define keyA 10
#define keyB 11
#define keyC 12
#define keyD 13
#define keyHash 99
#define keyStar 20

void initKeyPadIO();

unsigned isKeyPressed();

unsigned getKey(void);

#endif