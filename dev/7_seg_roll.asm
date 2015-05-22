#include "tx3703.inc"

;跑馬燈副程式實驗

		org 00h;
		JMP INIT;
		org 30h;
		
SEG_7_DATA:
		SEG_7_1 equ 28h;
		SEG_7_2 equ 29h;
		SEG_7_3 equ 2Ah;
		SEG_7_4 equ 2Bh;
		DISP_DLAY equ 2Ch;
		TEN_0	EQU	2Ah;	個位
		TEN_1	EQU	2Bh;	十位
		
STU_NUM:
		N1 equ 7;
		N1 equ 9;
		N1 equ 2;
		N1 equ 6;

INIT:
		MOV P0OE,#11111111b;
		MOV P0,#11111111b;
		MOV SEG_7_1, #N1;
		MOV SEG_7_2, #N2;
		MOV SEG_7_3, #N3;
		MOV SEG_7_4, #N4;
		MOV DISP_DLAY, #32;
		MOV TEN_0, #11100000b;
		MOV TEN_1, #11010000b;

START:
		ACALL DISPLAY;				Step.1
		
		ACALL DISP_OFF;				Step.2
		
		ACALL DISPLAY;				Step.3
		
		ACALL DISP_OFF;				Step.4
		
		MOV SEG_7_1, #00001111b;	Step.5
		ACALL DISPLAY;
		
		MOV SEG_7_1, #N1;			Step.6
		MOV SEG_7_2, #00001111b
		ACALL DISPLAY;
		
		MOV SEG_7_2, #N2;			Step.7
		MOV SEG_7_3, #00001111b
		ACALL DISPLAY;
		
		MOV SEG_7_3, #N3;			Step.8
		MOV SEG_7_4, #00001111b
		ACALL DISPLAY;
		
		MOV SEG_7_4, #N4;			Step.9
		ACALL DISPLAY;
		
		ACALL DISP_OFF;				Step.10
		
		MOV SEG_7_3, TEN_1;			Step.11
		MOV SEG_7_4, TEN_0;
		ACALL DISPLAY;
		ACALL L_COUNT_UP;
		
		AJMP START;					Step.12
		
;-----------------------------------------------
SEG_7_ROLL_L: ;(DPTR SEG_7_DATA, R0 Length)
		DEC R0; R0 設為陣列末端(length-1)
		MOV A, #0;
		MOV A, @A+DPTR;
		MOV R1, A; R1 保存 SEG_7_1
		MOV R2, #1;
SE7_RL_L:
		MOV A, R2; A = i
		MOV A, @A+DPTR; A = a[i]
		MOV R3, A; R3 = a[i] / 每回的陣列值 ( a[i-1] = a[i] )
		MOV A, R2; A = i
		DEC A; A = i-1
		ADD A, DPTR; A = *a[i-1]
		MOV R4, A; R4 = *a[i-1]
		MOV A, R3; A = a[i]
		MOV @R4, A; a[i-1] = a[i]
		INC R2; i++
		MOV A, R0;
		SUBB A, R2;
		JNZ SE7_RR_L; if (R0(length-1) - R2(i) = 0) JUMP
		MOV A, DPTR; A = DPTR
		ADD A, R0; A = DPTR + Length-1
		MOV R3, A; R3 = *a[length-1]
		MOV A, R1; A = a[0]
		MOV @R3, A; a[length-1] = a[0];
		RET;

;-----------------------------------------------
SEG_7_ROLL_R: ;(DPTR SEG_7_DATA, R0 Length)
		DEC R0; R0 設為陣列末端(length-1)
		MOV A, R0; A = length-1
		MOV A, @A+DPTR; A = a[length-1]
		MOV R1, A; R1 = a[length-1]
		MOV A, R0; A = length-1
		MOV R2, A; i = length-1
SE7_RL_R:
		MOV A, R2; A = i
		DEC A; A = i-1
		MOV A, @A+DPTR; A = a[i-1]
		MOV R3, A; R3 = a[i-1] / 每回的陣列值 ( a[i] = a[i-1] )
		MOV A, R2; A = i
		ADD A, DPTR; A = *a[i]
		MOV R4, A; R4 = *a[i]
		MOV A, R3; A = a[i-1]
		MOV @R4, A; a[i] = a[i-1]
		DEC R2; i--
		CJNE R2, #0, SE7_RR_L; for (i=length-1; i!=0; i--)
		MOV A, DPTR; A = DPTR
		MOV @A, R1; a[0] = a[length-1];
		RET;

;-----------------------------------------------
DISPLAY: ;(DISP_DLAY)
		MOV R5, DISP_DLAY;
D1:
		MOV R6, #15;
D2:
		MOV A, SEG_7_1;		12 osc
		ANL A, #00001111b;	12 osc
		ADD A, #01110000b;	12 osc
		MOV SEG_7_1, A;		12 osc
		MOV P0, SEG_7_1;	24 osc
		
		MOV A, SEG_7_2;
		ANL A, #00001111b;
		ADD A, #10110000b;
		MOV SEG_7_2, A;
		MOV P0, SEG_7_2;
		
		MOV A, SEG_7_3;
		ANL A, #00001111b;
		ADD A, #11010000b;
		MOV SEG_7_3, A;
		MOV P0, SEG_7_3;
		
		MOV A, SEG_7_4;
		ANL A, #00001111b;
		ADD A, #11100000b;
		MOV SEG_7_4, A;
		MOV P0, SEG_7_4;
		
		DJNZ R6, D2;
		DJNZ R5, D1;
		RET
		; ( ( (1+1+1+1+2+2)*R6 + 1 ) + 2 ) * R5 + 2 = ( ( 8 * R6 + 1 ) + 2 ) * R5 + 2 = ( 8 * R6 + 3 ) * R5 + 2 = 8 * R6 *R5 + 3 * R5 + 2
		
;-----------------------------------------------
DISP_OFF:
		MOV R5, DISP_DLAY;
DO_L_1:
		MOV R6, #250;
DO_L_2:
		MOV P0, #11111111b;
		
		DJNZ R6, DO_L_2;
		DJNZ R5, DO_L_1;

;-----------------------------------------------
L_COUNT_UP:		; With 99 Reset Function
		MOV A, TEN_1;
		CJNE A, #11101001b, LCUT1_N;
LCUT1_N:
		MOV A, TEN_0;
		CJNE A, #11101001b, LCUT0_N;
LCUT0_9:
		MOV A, TEN_1;
		ANL A, #00001111b;
		ACALL INC_TEN;
		ADD A, #11010000b;
		MOV TEN_1, A;
LCUT0_N:
		MOV A, TEN_0;
		ANL A, #00001111b;
		ACALL INC_TEN;
		ADD A, #11100000b;
		MOV TEN_0, A;
		JMP L_COUNT_UP_END;
		
LCUT1_9:
		MOV A, TEN_0;
		CJNE A, #11101001b, LCUT0_N;
		MOV TEN_1 #00h;
		MOV TEN_0 #00h;
		JMP L_COUNT_UP_END;

L_COUNT_UP_END:
		RET

;-----------------------------------------------
EE:		
		END