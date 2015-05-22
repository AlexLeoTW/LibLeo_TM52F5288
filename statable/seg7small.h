#ifndef SEGC7SMALL_H
#define SEGC7SMALL_H

#include "REG320.h"

void initSeg7IO();

void showSeg();

unsigned getSeg(void);

void setSeg(unsigned value);

void appendSeg(unsigned keyValue);

unsigned pow(unsigned base, unsigned power);

#endif