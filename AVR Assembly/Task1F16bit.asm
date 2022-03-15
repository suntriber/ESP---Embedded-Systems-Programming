/*
 * Task1F16bit.asm
 *
 *  Created: 2020-02-21 11:50:22
 *   Author: Patric
 */ 
 ; program to perform 16-bit division
 ;=================================================
; initializing variables to be used
.def intOneLow = R16
.def intOneHigh = R17
.def intTwoLow = R18
.def intTwoHigh = R19
.def sumLow = R20
.def sumHigh = R21
.def quotient = R22
 ;=================================================
 ; Start of code segment
.cseg              ; code segment start
.org 0x00          ; start from 0x00
 ;=================================================
; initializing values
LDI intOneLow, 0xCC  ; lower bytes of intOne is 0xCC
LDI intOneHigh, 0xCC ; higher bytes of intOne is 0xCC
LDI intTwoLow, 0x22  ; lower bytes of intTwo is 0x22
LDI intTwoHigh, 0x22 ; higherBytes of intTwo is 0x22
; values intOne = 0xCCCC, intTwo = 0x2222
;=================================================

