#include "keyPadSmall.h"

void initKeyPadIO()
{
	P3MODH = 0x00; 	//設定P3.4~7為pull up input  ;20140123 debug
	P3MODL = 0xaa; 	//設定P3.0~3為CMOS output    ;20140123 debug
	P3 = 0xff;
}

unsigned isKeyPressed()
{
	P3=0xf0;
	_nop_();
	
	if (P3 != 0xf0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned getKey(void)
{
	//row1
	P3=0xef; 
	_nop_();
	P3=0xfe; 
	_nop_();	
	if(P3==0x7e){
		return 1;
	}
	else if(P3==0xbe){
		return 2;
	}	
	else if(P3==0xde){
		return 3;
	}	
	else if(P3==0xee){
		return keyA;
	}
	//row2
	P3=0xfd;
	_nop_();		
	if(P3==0x7d){
		return 4;
	}
	else if(P3==0xbd){
		return 5;
	}	
	else if(P3==0xdd){
		return 6;
	}	
	else if(P3==0xed){
		return keyB;
	}	
	//row3
	P3=0xfb;
	_nop_();		
	if(P3==0x7b){
		return 7;
	}
	else if(P3==0xbb){
		return 8;
	}	
	else if(P3==0xdb){
		return 9;
	}	
	else if(P3==0xeb){
		return keyC;
	}	
	//row4
	P3=0xf7; 
	_nop_();		
	if(P3==0x77){
		return keyStar;
	}
	else if(P3==0xb7){
		return 0;
	}	
	else if(P3==0xd7){
		return keyHash;
	}	
	else if(P3==0xe7){
		return keyD;
	}
    return 0;
}