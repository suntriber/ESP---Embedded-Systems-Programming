/*
 * Task1B.asm
 *
 *  Created: 2020-02-21 09:50:30
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
; initializing variables to be used
.def factorone = R16    ; register R16 can now be called factorone
.def factortwo = R17    ; register R17 can now be called factortwo
.def sum = R18          ; register R18 can now be called sum
.def temp = R19         ; register R19 can now be called temp
;------------------------------------------------------
; Start of code segment
.cseg              ; code segment start
.org 0x00          ; start from 0x00
;-------------------------------------------------------
; Initialize PORT D as output
LDI temp, 0xFF       ;sets R16 to 0xFF (all ones)
OUT DDRD, temp       ;sets data direction for port D as output (all ones from R16)
;--------------------------------------------------------
; Setting values for I/O register PORTD to all zeros to ensure LED is currently not displaying anything
LDI temp, 0x00       ; loading temp with 0x00 which equals all zeros
OUT PORTD, temp      ; setting portD to all zeros
;---------------------------------------------------------
LDI factorone, 3     ; value of factorone is 3
LDI factortwo, 2     ; value of factortwo is 2
MULS factorone, factortwo      ; multiply factorone with factortwo
; result from MULS operation is stored in R0 and R1
MOV sum, R0          ; copies value of R0 to sum
;------------------------------------------------------
; subroutine checksum
; uses branch if equal to check value of sum with number 0-9
; if it finds a match it jumps to a subroutine for that number
checksum:
CPI sum, 0      ; compare sum to value 0              
BREQ ledzero	; if sum is 0 goto subroutine ledzero
CPI sum, 1      ; compare sum to value 1
BREQ ledone     ; if sum is 1 goto subroutine ledone
CPI sum, 2      ; compare sum to value 2
BREQ ledtwo     ; if sum is 2 goto subroutine ledtwo
CPI sum, 3      ; compare sum to value 3
BREQ ledthree   ; if sum is 3 goto subroutine ledthree
CPI sum, 4      ; compare sum to value 4
BREQ ledfour    ; if sum is 4 goto subroutine ledfour
CPI sum, 5      ; compare sum to value 5
BREQ ledfive    ; if sum is 5 goto subroutine ledfive
CPI sum, 6      ; compare sum to value 6
BREQ ledsix     ; if sum is 6 goto subroutine ledsix
CPI sum, 7      ; compare sum to value 7
BREQ ledseven   ; if sum is 7 goto subroutine ledseven
CPI sum, 8      ; compare sum to value 8
BREQ ledeight   ; if sum is 8 goto subroutine ledeight
CPI sum, 9      ; compare sum to value 9
BREQ lednine    ; if sum is 9 goto subroutine lednine
;-----------------------------------------------------------
ledzero:
LDI temp, zero  ; loading values for displaying 0 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledone:
LDI temp, one  ; loading values for displaying 1 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledtwo:
LDI temp, two  ; loading values for displaying 2 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledthree:
LDI temp, three  ; loading values for displaying 3 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledfour:
LDI temp, four  ; loading values for displaying 4 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledfive:
LDI temp, five  ; loading values for displaying 5 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledsix:
LDI temp, six  ; loading values for displaying 6 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledseven:
LDI temp, seven  ; loading values for displaying 7 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
ledeight:
LDI temp, eight  ; loading values for displaying 8 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------
lednine:
LDI temp, nine  ; loading values for displaying 9 into temp
OUT PORTD, temp ; sending values to I/O register portD
rjmp start       ; goto subroutine start to keep program in loop
;---------------------------------------------------------------


; keep program in loop
start:           ; initializing subroutine start
rjmp start       ; jump back to start
;--------------------------------------------------------------
