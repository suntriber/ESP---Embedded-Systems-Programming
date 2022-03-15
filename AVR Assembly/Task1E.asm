/*
 * Task1E.asm
 *
 *  Created: 2020-02-21 10:59:04
 *   Author: Patric
 */ 
 ; program to subtract two 16-bit integers from memory and store the result back to memory
 ;=========================================================
 ; Defining variables to be used
 .def num1Low  = R16  ; lower bytes of num1  
 .def num1High = R17  ; higher bytes of num1
 .def num2Low  = R18  ; lower bytes of num2
 .def num2High = R19  ; higher bytes of num2
 .def sumLow = R20    ; lower bytes of sum
 .def sumHigh = R21   ; higher bytes of sum
;=========================================================
 ; Start of code segment
.cseg              ; code segment start
.org 0x00          ; start from 0x00
;=========================================================
; initializing values
 LDI num1Low, 0x42  ; set value R16 = 0x42
 LDI num1High, 0x86 ; set value R17 = 0x86
 ; first integer now has the value of num1High_num1Low = 0x8642 
 LDI num2Low, 0x76  ; set value R18 = 0x76
 LDI num2High, 0x98 ; set value R19 = 0x98
 ; second integer now haas the value of num2High_num2Low = 0x9876
;=========================================================
; storing integers in memory
clr R26                    ; clear lowest byte in register X
clr R27                    ; clear highest byte in register X
ldi r26,0x00				; Set X low byte to 0x00
ldi r27, 0x01			    ; set X high byte to $01 -> x register ==> 0x0100 (data iram)
; X register is now pointing towards memory slot 0x0100
st X+, num1High				; Store higher 2 bytes of first integer in memory address space 0x0100	(X post inc)
st X+, num1Low				; Store lower 2 bytes of first integer in memory address space 0x101  (X post inc)
st X+, num2High              ; store higher 2 bytes of second integer in memory address space 0x102   (X post inc)
st X+, num2Low              ; store lower 2 bytes of second integer in memory address space 0x103 (X post inc)
; first and second integers are now stored in memory addresses 0x0100-0x0103
; this was done to actually have the integers in memory since the assignment asked for adding integers from memory and then storing
; them to memory again
; since the values in my variables (R16-R19) are still the same i will use them for the subtraction
; i am keeping the incrementation in X-register to be able to store the sum after subtraction
;=========================================================
; subtracting integers
SUB num2Low, num1Low       ; num2Low = num2Low - num1Low
SUB num2High, num1High     ; num2High = num2High - num1Low
MOV sumLow, num2Low        
MOV sumHigh, num2High
; integer num2 subtracted with num1 and result stored in variables sumLow and sumHigh
;=========================================================
; storing sum in memory
; keeping in mind X is still pointing at memory address 0x0104
ST X+, sumHigh    ; storing lower two bytes of sum in memory 0x0104 (X post inc)
ST X, sumLow      ; storing higher two bytes of sum in memory 0x0105
; integers added and stored in memory 0x0104-0x0105
;=========================================================
; keep program in loop
start:           ; initializing subroutine start
rjmp start       ; jump back to start
