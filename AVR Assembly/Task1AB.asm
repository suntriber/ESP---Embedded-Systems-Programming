/*
 * Task1A.asm
 *
 *  Created: 2020-02-21 09:23:23
 *   Author: Patric
 */ 
 ;-----------------------------------------------------
 ; Display numbers on LED
.equ zero = 0b11111110
.equ one = 0b00011000
.equ two = 0b11001101
.equ three = 0b01011101
.equ four = 0b00011011
.equ five = 0b01010111
.equ six = 0b11010111
.equ seven = 0b00011100
.equ eight = 0b11011111
.equ nine = 0b00011111
;-------------------------------------------------------
.cseg              ; code segment start
.org 0x00          ; start from 0x00
;-------------------------------------------------------
; Initialize PORT D as output
LDI R16, 0xFF       ;sets R16 to 0xFF (all ones)
OUT DDRD, R16       ;sets data direction for port D as output (all ones from R16)
;--------------------------------------------------------
; program start
LDI R19, 55      ; set R19 to 55
LDI R18, 51      ; set R18 to 51
CP R19, R18      ; compare R18 to R19 - arg1 >= arg 2
BRGE GREATEQ     ; branch greater then - R19 greater than R18 = go to routine "GREATEQ"
LDI R20, zero    ; loading display values for number 0 into R20
OUT PORTD, R20   ; setting pins on port d to display 0
GREATEQ:
LDI R20, eight   ; loading display values for number 8 into R20
OUT PORTD, R20   ; setting pins on port d to display 8
;---------------------------------------------------------------
; keep program in loop
start:           ; initializing subroutine start
rjmp start       ; jump back to start
;--------------------------------------------------------------
;   Task B
TASKB:    ;intialize subroutine TASKB
;  same code as above except R19 is now set to 45
LDI R19, 45      ; set R19 to 45* 
LDI R18, 51      ; set R18 to 51
CP R19, R18      ; compare R18 to R19 - arg1 >= arg 2
BRGE GREATEQTASKB     ; branch greater then - R19 greater than R18 = go to routine "GREATEQ"
LDI R20, zero    ; loading display values for number 0 into R20
OUT PORTD, R20   ; setting pins on port d to display 0
GREATEQTASKB:
LDI R20, eight   ; loading display values for number 8 into R20
OUT PORTD, R20   ; setting pins on port d to display 8
jmp start     ; jumps to routine start to keep program in loop
;--------------------------------------------------------------