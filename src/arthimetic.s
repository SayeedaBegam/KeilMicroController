; /**************************************************************************************************
; Name 			|	YoGanath. P_19EC2004	|	 ECE-A
; Expt. Name	|	Implementation of Simple Programs
; Sub Name		|		b) Arithmetic Operation
; Cycle 2		|	ARM (LPC2148) Micro-controller
; Subject		|	MICROPROCESSORS AND MICROCONTROLLERS LAB
; **************************************************************************************************/

	AREA RESET, CODE, READONLY
num equ 3
num1 equ 2
ENTRY
	MOV R1,#num
	MOV R2,#num1
	ADD R3,R1,R2
	SUB R4,R1,R2
	RSBS R5,R1,R2
	MUL R6,R1,R2
	MLA R7,R1,R2,R3
HERE B HERE
	END