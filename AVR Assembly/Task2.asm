/*
 * Task2.asm
 *
 *  Created: 2020-02-21 12:13:36
 *   Author: Patric
 */ 
 ; Task information
 ;One of the important aspects of real-time applications is accurate timing of tasks. 
 ;Write a code that produces a delay of 1msec. Explain how you estimated the duration of the loop. 
 ;Repeat the above for delays of 10ms, 100ms, 1s, 10sec.
;=============================================================================  
; variable initialization
.def allOnes = R16
.def allZero = R17
.def thirdloop = R18
.def secondloop = R19
.def firstloop = R20
.def fourthloop = R21
;=============================================================================  
; program order
startme:
  call lightled
  call loadVarOneSecDelay
  call delayLoop1s
  call stopled
  call delayLoop1s
  call lightled
  call loadVarOneSecDelay 
  call delayLoop1s
  call stopled
  call delayLoop1s
  jmp startme
  ;rjmp endme
;=============================================================================  
 ; turning led lights on
 lightled:          ; subroutine for turning all leds on for 7-segment display
    LDI allOnes, 0xFF   ; loads 0xFF into variable allOnes
	OUT DDRD, allOnes   ; sets data direction register as output for all pins on portD
	OUT PORTD, allOnes  ; sets all ones for port D which turns on all leds
	ret                 ; return to previous call
;=============================================================================  
; subroutine for turning all led lights off
stopled:
LDI allZero, 0x00     ; loads 0x00 into variable allZero
OUT PORTD, allZero    ; sets all zeroes for port D which turns off all leds
ret                   ; return to previous call
;=============================================================================  
loadVarOneSecDelay:          ; subroutine for loading variable values for 1s delay
    ldi  thirdloop, 82       ; sets value of thirdloop to 82
    ldi  secondloop, 43      ; sets value of secondloop to 43
    ldi  firstloop, 0        ; sets value of firstloop to 0
	ret                      ; return to previous call
	                         ;trial and error in simulator gave me these values for a 1 second delay
 ;=============================================================================  
delayLoop1s:                 ; subroutine for creating a one second delay using 3 registers
    dec  firstloop           ; decrement value of firstloop (is 0, becomes 255)
    brne delayLoop1s         ; checks zero flag for variable firstloop (if not zero it branches back up to loop1)
    dec  secondloop          ; secondloop--
    brne delayLoop1s         ; if secondloop != 0  -->> branch back up to Loop1
    dec  thirdloop           ; thirdloop--
    brne delayLoop1s         ; if thirdloop != 0   -->> branch back up to Loop1
	ret                      ; return to previous call
 ;=============================================================================  
  loadVarTenSecDelay:        ; subroutine for loading variables values for a 10 sec delay
	ldi  fourthloop, 21      ; sets value of fourthloop to 21
    ldi  thirdloop, 4        ; sets value of thirdloop to 4
    ldi  secondloop, 44      ; sets value of secondloop to 44
    ldi  firstloop, 175      ; sets value of firstloop to 175
	ret                      ; return to previous call
 ;=============================================================================  
 delayLoop10s:               ; subroutine for creating a 10 second delay using 4 registers
    dec  fourthloop          ; fourthloop--
    brne delayLoop10s        ; if not zero branch back to delayLoop10s 
    dec  firstloop           ; firstloop--
    brne delayLoop10s        ; if not zero branch back to delayLoop10s
    dec  secondloop          ; secondloop--
    brne delayLoop10s        ; if not zero branch back to delayLoop10s
    dec  thirdloop           ; thirdloop--
    brne delayLoop10s        ; if not zero branch back to delayLoop10s
	ret                      ; return to previous call
 ;=============================================================================  
 loadVarTenMsDelay:          ; subroutine for loading variable values for a 10ms delay
    ldi  thirdloop, 208      ; sets value of thirdloop to 208
    ldi  secondloop, 202     ; sets value of secondloop to 208
 ;=============================================================================  
 delayLoop10ms:              ; subroutine for creating a 10ms delay using 2 registers
    dec  secondloop          ; secondloop--
    brne delayLoop10ms       ; if not zero branch back to delayLoop10ms
    dec  thirdloop           ; thirdloop--
    brne delayLoop10ms       ; if not zero branch back to delayLoop10ms
	ret                      ; return to previous call
 ;=============================================================================  
 loadVarHundredMsDelay:      ; subroutine for loading variable values for a 100ms delay
	ldi thirdloop, 9         ; sets value of thirdloop to 9
	ldi secondloop, 30       ; sets value of secondloop to 30
	ldi firstloop, 229       ; sets value of firstloop to 229
	ret                      ; return to previous call
 ;=============================================================================  
delayLoop100ms:              ; subroutine for creating a 100ms delay using 3 registers
    dec firstloop            ; firstloop--
	brne delayLoop100ms      ; if not zero branch back to delayLoop100ms
	dec secondloop           ; secondloop--
	brne delayLoop100ms      ; if not zero branch back to delayLoop100ms
	dec thirdloop            ; thirdloop--
	brne delayLoop100ms      ; if not zero branch back to delayLoop100ms
	ret                      ; return to previous call
 ;=============================================================================  
    endme:                   ; subroutine for putting program in an infinite "do-nothing loop"
	rjmp endme               ;
 ;=============================================================================  
