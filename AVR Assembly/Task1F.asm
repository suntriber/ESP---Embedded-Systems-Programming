/*
 * Task1F.asm
 *
 *  Created: 2020-02-21 11:18:39
 *   Author: Patric
 */ 
; 8 bit integer division
;=================================================
; initializing variables to be used
.def intOne = R16
.def intTwo = R17
.def sum = R18
.def temp = R19
.def quotient = R20
;=================================================
 ; Start of code segment
.cseg              ; code segment start
.org 0x00          ; start from 0x00
;=================================================
; initializing values
LDI intOne, 0x99      ; intOne has value of 0x99
LDI intTwo, 0x33      ; intTwo has value of 0x33
;=================================================
; performing division, should be equal to three

division:    ;initializing subroutine division
SUB intOne, intTwo    ; subtracting value of intTwo from intOne
INC quotient          ; increase quotient by one
CP intOne, intTwo     ; compare intOne with intTwo
BRGE division         ; if intOne is bigger then or equal to intTwo, jump back upp to division routine
MOV sum, quotient     ; if intOne is less then intTwo, copy value of quotient to sum
CLR quotient          ; clears value of quotient 
; result stored in sum and it has the value of three which was the aim
;=================================================
; keep program in loop
start:           ; initializing subroutine start
rjmp start       ; jump back to start


