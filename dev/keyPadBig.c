#include "keyPadSmall.h"

void initKeyPadIO()
{
	P3MODH = 0xaa; 	//設定P3.4~7為pull up input  ;20140123 debug
	P3MODL = 0x00; 	//設定P3.0~3為CMOS output    ;20140123 debug
	P3 = 0xff;
}

unsigned isKeyPressed()
{
	P3=0x0f;
	_nop_();
	
	if (P3 != 0x0f)
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
	if(P3==0xee){
		return 1;
	}
	else if(P3==0xed){
		return 2;
	}	
	else if(P3==0xeb){
		return 3;
	}	
	else if(P3==0xe7){
		return keyA;
	}
	//row2
	P3=0xdf;
	_nop_();		
	if(P3==0xde){
		return 4;
	}
	else if(P3==0xdd){
		return 5;
	}	
	else if(P3==0xdb){
		return 6;
	}	
	else if(P3==0xd7){
		return keyB;
	}	
	//row3
	P3=0xbf;
	_nop_();		
	if(P3==0xbe){
		return 7;
	}
	else if(P3==0xbd){
		return 8;
	}	
	else if(P3==0xbb){
		return 9;
	}	
	else if(P3==0xb7){
		return keyC;
	}	
	//row4
	P3=0x7f; 
	_nop_();		
	if(P3==0x7e){
		return keyStar;
	}
	else if(P3==0x7d){
		return 0;
	}	
	else if(P3==0x7b){
		return keyHash;
	}	
	else if(P3==0x77){
		return keyD;
	}
    return 0;
}