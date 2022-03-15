/*
 * voltMeterModule.c
 *
 * Created: 2020-05-26 14:24:41
 *  Author: Patric
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include "LCD.h"

/**********************************************************************************************
* Function name  : initADCVoltageMeter()
* Input          : none
* Output         : none
* Calls          : 
* Gets called by : callForReading()
*
* Function that sets the ADMUX register bits in order to perform ADC on channel 5.
**********************************************************************************************/
void initADCVoltageMeter(){
	ADMUX |= (1 << MUX0) | (1 << MUX2);   // ADC Multiplexer Selection Register
	ADMUX &= ~((1 << MUX1) | (1 << MUX3));
	//_delay_ms(5);
	// ADMUX = 0b XXXX 0101      == ADC channel 5 selected (Table 23-4)
}

/**********************************************************************************************
* Function name  : voltMeterOutput()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD(), setCursorOnSecondRow(), writeStringToLCD()
* Gets called by : callForReading()
*
* This functions purpose is to display a value from a given source on the LCD.
* The source in this case coming from ADC pin 5 and the value is stored in the ADC register.
* ADC is a 16-bit register which hold the value from the latest ADC conversion.
* The value is via an algorithm calculated as voltage between 0-5V and presented on the LCD.
**********************************************************************************************/
void voltMeterOutput(){
	double incomingVoltage = (double) (ADC * 5) / 1024;      // converting value from ADC to a double value between 0-5
	int temp = incomingVoltage * 100;                       // multiplying previous value with 100 to eliminate first two decimals
	char buf[4];                                           // temporary char array for presenting value on LCD
	sprintf(buf, "%03d", temp);                           // loading first three digits of voltage value into char array
	                                                     //
	writeCharToLCD(buf[0]);                             // Presenting digits on LCD
	writeCharToLCD('.');
	writeCharToLCD(buf[1]);
	writeCharToLCD(buf[2]);
    writeCharToLCD('V');

	
	int adcCopy = ADC;                               // putting value from ADC in a temporary variable
	char acop[4];                                   // temporary char array for ADC value
	setCursorOnSecondRow();                        // places cursor on second row for LCD
	char *adcPrint = "ADC =";                     // string to print on LCD
	writeStringToLCD(adcPrint);                  // prints above string to LCD
	sprintf(acop, "%3d", adcCopy);              // integer value of ADC into the temporary char array
    writeCharToLCD(acop[0]);                   // present value on LCD
	writeCharToLCD(acop[1]);     
	writeCharToLCD(acop[2]);
	
	writeVoltMeterModeLCD();                // write VM on LCD to indicate which mode
	
}