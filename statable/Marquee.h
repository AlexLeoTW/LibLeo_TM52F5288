#ifndef MARQUEE_H
#define MARQUEE_H

#define RIGHT 1
#define LEFT 0

void setMarquee(unsigned char startX, unsigned char startY, unsigned char endX, unsigned char endY, unsigned char direct);

void marqueeStep();

#endif