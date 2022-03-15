/*
 * photoResistorSensorModule.c
 *
 * Created: 2020-05-27 08:31:22
 *  Author: Patric
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include "LCD.h"


/**********************************************************************************************
* Function name  : initADCPhotoResistorSensor()
* Input          : none
* Output         : none 
* Calls          :
* Gets called by : callForReading()
*
* Function that sets the ADMUX register bits in order to perform ADC on channel 4.
**********************************************************************************************/
void initADCPhotoResistorSensor(){
	ADMUX |= (1 << MUX2);   // ADC Multiplexer Selection Register
	ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX3));
	// ADMUX = 0b XXXX 0100      == ADC channel 4 selected (Table 23-4)
	//_delay_ms(5);
}


/**********************************************************************************************
* Function name  : photoResistorSensorOutput()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD(), setCursorOnSecondRow(), writeStringToLCD()
* Gets called by : callForReading()
*
* This functions purpose is to display a value from a given source on the LCD.
* The source in this case coming from ADC channel 4 and the value is stored in the ADC register.
* ADC is a 16-bit register which hold the value from the latest ADC conversion.
* This function simply prints the value in the ADC to the LCD.
**********************************************************************************************/
void photoResistorSensorOutput(){
	
	writeCharToLCD(' ');           // clear previous characters on LCD first row
	writeCharToLCD(' ');
	writeCharToLCD(' ');
	writeCharToLCD(' ');
	writeCharToLCD(' ');
	
	
	int adcCopy = ADC;                    // putting value from ADC in a temporary variable
	char acop[4];                         // temporary char array for ADC value
	setCursorOnSecondRow();               // places cursor on second row for LCD
	char *adcPrint = "ADC =";             // string to print on LCD
	writeStringToLCD(adcPrint);           // prints above string to LCD
	sprintf(acop, "%3d", adcCopy);        // integer value of ADC into the temporary char array
	writeCharToLCD(acop[0]);              // present value on LCD
	writeCharToLCD(acop[1]);
	writeCharToLCD(acop[2]);

	
	
	writePhotoResistorSensorModeLCD();     // write PR on LCD to indicate which mode
}