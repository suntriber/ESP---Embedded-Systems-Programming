/*
 * Task3A.asm
 *
 *  Created: 2020-02-21 17:18:11
 *   Author: Patric
 */ 
 ; Task information
 ; Suppose you have an array of integer data (say 10 numbers) in a memory
 ; Write a program to find the largest of these numbers and show the location on the lab deck display
 ;====================================================================================================
 ; Variable initialization
 .def highest = R17
 .def temp = R18
 .def counter = R19
 .def zero = R20
 LDI zero, 0x00
 LDI counter, 11
 ;====================================================================================================
 ; Loading ten integer values into memory
 ; Values will be randomly selected between 0-255 in order to fit into one memory address space and register
 .cseg
 LDI R26, 0x00               ; setting lower bytes of register X to point at 0x00
 LDI R27, 0x01               ; setting higher bytes of register X to point at 0x01
                             ; Register X now pointing towards memory address space 0x0100
 LDI temp, 0x04              ; set value of temp to 0x04
 ST X+, temp                 ; store value of temp to memory 0x0100
 LDI temp, 0x14              ; set value of temp to 0x14
 ST X+, temp                 ; store value of temp to memory 0x0101
 LDI temp, 0x24              ; set value of temp to 0x24
 ST X+, temp                 ; store value of temp to memory 0x0102
 LDI temp, 0x44              ; set value of temp to 0x44
 ST X+, temp                 ; store value of temp to memory 0x0103
 LDI temp, 0x84              ; set value of temp to 0x84
 ST X+, temp                 ; store value of temp to memory 0x0104
 LDI temp, 0xA4              ; set value of temp to 0xA4
 ST X+, temp                 ; store value of temp to memory 0x0105
 LDI temp, 0xC4              ; set value of temp to 0xC4
 ST X+, temp                 ; store value of temp to memory 0x0106
 LDI temp, 0xF4              ; set value of temp to 0xF4
 ST X+, temp                 ; store value of temp to memory 0x0107
 LDI temp, 0x4F              ; set value of temp to 0x4F
 ST X+, temp                 ; store value of temp to memory 0x0108
 LDI temp, 0xFE              ; set value of temp to 0xFE
 ST X, temp                  ; store value of temp to memory 0x0109
                             ; Array of ten integers is now stored in memory on addresses 0x0100-0x0109
 CLR R26                     ; clearing R26 = clearing lower two bytes of X-register
 CLR R27                     ; clearing R27 = clearing higher two bytes of X-register
                             ; X-register is now cleared and pointing to default value 0x0000
 ;====================================================================================================
 ; Algoritm for finding the biggest number in the array which starts at memory address space 0x0100
 LDI R26, 0x00               ; setting lower bytes of register X to point at 0x00
 LDI R27, 0x01               ; setting higher bytes of register X to point at 0x01
                             ; Register X now pointing towards first number in the array
 searchHighestNumber:        ; subroutine for searching the addresses X-register is pointing towards
 LD temp, X+                 ; loads value from address X is pointing at into temp
 DEC counter                 ; counter--
 CP temp, highest            ; compare variable temp to variable highest
 BRSH isBigger               ; if temp is bigger then or equals highest -->> branch to subroutine isBigger
 CP zero, counter            ; check if counter is zero
 BRNE searchHighestNumber    ; if counter isnt zero -->> branch back to subroutine isBigger
 ;====================================================================================================
 endme:                      ; infinite "do-nothing loop"
                             ; Highest number of the array is now stored in variable highest
 RJMP endme                  ; program ends with an infinite loop
 ;====================================================================================================
 isBigger:                   ; subroutine for when a bigger number is found
 MOV highest, temp           ; copies content of temp to highest
 jmp searchHighestNumber     ; returns to subroutine searchHighestNumber