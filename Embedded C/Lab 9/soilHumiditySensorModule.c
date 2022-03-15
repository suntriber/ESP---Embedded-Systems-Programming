/*
 * soilHumiditySensorModule.c
 *
 * Created: 2020-05-27 08:30:16
 *  Author: Patric
 */ 
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include "LCD.h"


/**********************************************************************************************
* Function name  : initADCSoilHumiditySensor()
* Input          : none 
* Output         : none
* Calls          :
* Gets called by : callForReading()
*
* Function that sets the ADMUX register bits in order to perform ADC on channel 3.
**********************************************************************************************/
void initADCSoilHumiditySensor(){
	ADMUX |= (1 << MUX0) | (1 << MUX1);   // ADC Multiplexer Selection Register
	ADMUX &= ~((1 << MUX2) | (1 << MUX3));
	// ADMUX = 0b XXXX 0011      == ADC channel 3 selected (Table 23-4)
	//_delay_ms(5);
	
}


/**********************************************************************************************
* Function name  : soilHumiditySensorOutput()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD(), setCursorOnSecondRow(), writeStringToLCD()
* Gets called by : callForReading()
*
* This functions purpose is to display a value from a given source on the LCD.
* The source in this case coming from ADC channel 3 and the value is stored in the ADC register.
* ADC is a 16-bit register which hold the value from the latest ADC conversion.
* The value is via an algorithm calculated as voltage between 0-5V and presented on the LCD.
**********************************************************************************************/
void soilHumiditySensorOutput(){
	uint8_t humidity = (ADC * 100) / 600;            // ADC value converted to percentage representation
	char humid[3];                                   // temporary char array to hold percentage value
	sprintf(humid, "%2d", humidity);                 // percentage value put into char array
	writeCharToLCD(humid[0]);                        // present on LCD
	writeCharToLCD(humid[1]);
	writeCharToLCD('%'); 
	writeCharToLCD(' ');                               // extra blank space to clear potential previous writings
	writeCharToLCD(' ');
	
	int adcCopy = ADC;                                 // putting value from ADC in a temporary variable
	char acop[4];                                      // temporary char array for ADC value
	setCursorOnSecondRow();                            // places cursor on second row for LCD
	char *adcPrint = "ADC =";                          // string to print on LCD
	writeStringToLCD(adcPrint);                        // prints above string to LCD
	sprintf(acop, "%3d", adcCopy);                     // integer value of ADC into the temporary char array
	writeCharToLCD(acop[0]);                           // present value on LCD
	writeCharToLCD(acop[1]);
	writeCharToLCD(acop[2]);

	
	
	writeSoilHumiditySensorModeLCD();                  // write HM on LCD to indicate which mode
	
	
}