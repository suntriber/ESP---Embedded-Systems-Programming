/*
 * CFile1.c
 *
 * Created: 2020-05-26 09:55:35
 *  Author: Patric
 */ 
#include <avr/io.h>
#include <avr/delay.h>

#include "LCD.h"
uint8_t cursorControl = 0x80;       // function-wide variable to control cursor on LCD


/**********************************************************************************************
* Function name  : initializeLCD()
* Input          : none
* Output         : none
* Calls          : lcdEnableCommandMode(), clearScreenLCD()
* Gets called by : main()
*
* This functions purpose is to initialize data direction register for both sending data
* and controlling the LCD.
* PORTD bits 0-7 are used for sending one byte of data to the LCD for displaying purposes,
* hence PORTD is set as output.
* PORTB PINB0 is connected to the enable bit of the LCD so this is set as output.
* PORTB PINB1 is connected to the register select bit of the LCD, this is also set as output.
* Sending hexadecimal value 0x38 to PORTD as a command enables the LCD to display a 7*matrix
* of dots for each character. This is specified in the LCD Display Datasheet on page 8.
* Sending hexadecimal value 0x0E to PORTD as a command enable the LCD to turn on display
* and display the cursor.
**********************************************************************************************/
void initializeLCD(){
	LCD_DATA_DDR = 0xFF; //PORTD Output
	LCD_CONTROL_DDR |= (1<<PINB0); //PORTB Pin0 - enable - output
	LCD_CONTROL_DDR |= (1<<PINB1); //PORTB Pin1 - register select - output
	LCD_DATA_PORT = 0x38; //initialize as 7*5 matrix
	lcdEnableCommandMode(); // sending previous data as a command to the LCD
	LCD_DATA_PORT = 0x0E; //Turn on LCD, cursor displayed
	lcdEnableCommandMode(); // sending previous data as a command to the LCD
	clearScreenLCD();
	resetCursor();
}


/**********************************************************************************************
* Function name  : resetCursor()
* Input          : none
* Output         : none
* Calls          : none
* Gets called by : initializeLCD(), main()
*
* This functions purpose is solely to give the variable cursorControl its original value that
* is hexadecimal 0x80
* This value corresponds to the first column and first row on the LCD and used in conjunction
* with calling the LCD with a command if will effectively reset the cursor position to start
* with easy readable and understandable code.
**********************************************************************************************/
void resetCursor(){
	cursorControl = 0x80;  // starting point for cursor = first column, first row on LCD
}


/**********************************************************************************************
* Function name  : clearScreenLCD()
* Input          : none
* Output         : none
* Calls          : lcdEnableCommandMode()
* Gets called by : initializeLCD(), main()
*
* This function set the value of PORTD to 0x01 and then called lcdEnableCommandMode() which
* will effectively clear the screen of the LCD. This is specified in the LCD Display Datasheet
* under "Commands" on page 8.
* Function is mainly created for facilitating readability and understanding of the code.
**********************************************************************************************/
void clearScreenLCD(){
	LCD_DATA_PORT = 0x01; // hexadecimal 0x01 is the command to clear LCD screen
	lcdEnableCommandMode(); // sending previous data as a command to the LCD
}

void setCursorOnSecondRow(){
	cursorControl = 0xC0;
}


/**********************************************************************************************
* Function name  : writeStringToLCD()
* Input          : char* stringPointer
* Output         : none
* Calls          : lcdEnableCommandMode(), lcdEnableDataMode()
* Gets called by : main()
*
* This functions purpose is to receieve a pointer for a character array and display it on the
* LCD starting at column one and row one.
* A local variable is initialied to be used as a counter to keep track of what index in the
* array pointer we are currently accessing.
* A while-loop is iterated until a '\0' is found on the incoming array pointer, indicating
* end of the string.
* A short description of the logic is that the cursor is placed according to variable
* cursorControl (origin first column, first row).
* After that the array pointer at index = counter (origin 0) is dereferenced into a local character
* variable which is sent as a command to the LCD via the command function.
* Both variables are incremented and loop iterates again.
* If statements are placed to change row after 16 characters is used on first row.
* After maximum of 32 characters the loop breaks since the LCD cannot display any more characters
* at any given time.
**********************************************************************************************/
void writeStringToLCD(char* stringPointer){
	uint8_t counter = 0;    // local variable to iterate through index of string pointer
	
	while (*(stringPointer+counter) != '\0'){    // while loop iterates until end of string
		
		LCD_DATA_PORT = cursorControl;    // writing data for cursor placement to PORTD
		lcdEnableCommandMode();  // sending previous data as a command to the LCD
		char tmp = *(stringPointer+counter);   // local variable to be displayed
		LCD_DATA_PORT = tmp;                   // writing local variable to PORTD
		lcdEnableDataMode();                   // calling function to display the data previously written to PORTD
		cursorControl++;                       // increment cursor placement
		counter++;                             // increment string index
		
		if (cursorControl == 0xD0)             // if cursor has reached last column on second row
		break;                                 // loop will break because there is not room for more characters
		if (cursorControl == 0x90){            // if cursor reaches last column on first row
			cursorControl = 0xC0;              // cursor is places on first column in second row
		}
	}
}


/**********************************************************************************************
* Function name  : writeCharToLCD()
* Input          : unsigned char charData
* Output         : none
* Calls          : lcdEnableCommandMode(), lcdEnableDataMode()
* Gets called by : main()
*
* This function is used to display characters on the LCD one at a time.
* First a command given to LCD places the cursor at its current location according to global
* cursorControl variable.
* Next the incoming character is written to PORTD and then the LCD is given the command to display
* this character via lcdEnableDataMode function.
* Finally cursorControl is incremented so the next call will ensure that the previous character
* isnt overwritten.
**********************************************************************************************/
void writeCharToLCD(unsigned char charData){
	if (cursorControl == 0x90){
		cursorControl = 0xC0;
	}
	LCD_DATA_PORT = cursorControl;  // writing placement of cursor to PORTD
	lcdEnableCommandMode();         // sending previous data as a command to the LCD
	LCD_DATA_PORT = charData;       // writing the incoming character data to PORTD
	lcdEnableDataMode();            // calling function to display the data previously written to PORTD
	cursorControl++;                // increment cursor placement
}

/**********************************************************************************************
* Function name  : lcdEnableCommandMode()
* Input          : none
* Output         : none
* Calls          : none
* Gets called by : initializeLCD(), clearScreenLCD(), writeStringToLCD(), writeCharToLCD()
*
* This function is one of the backbones of the program. After any value is written to PORTD
* (defined as LCD_DATA_PORT) this function must be called for that command to be executed.
* The R/S bit of the LCD is written a logic 0. This means that the LCD will interpret the data
* data coming into it as a command.
* The enable bit is connected to PINB0. This bit is used to send an enable trigger to the LCD.
* The enable trigger is falling edge triggered, meaning it will be triggered when the bits goes
* from high to low.
* A logic one is first written followed by a delay for 100ms, then a logic 0 is written thus
* triggering the enable bit and the LCD will act accordingly to its commands.
**********************************************************************************************/
void lcdEnableCommandMode(){
	LCD_CONTROL_PORT &= ~(1<<PINB1); //Register select = 0   == command mode
	LCD_CONTROL_PORT |= (1<<PINB0); //Enable bit written high
	_delay_ms(100);                 // delay for 100ms for IO unit to catch up
	LCD_CONTROL_PORT &= ~(1<<PINB0); //Enable bit written low - falling edge triggered
}


/**********************************************************************************************
* Function name  : lcdEnableDataMode()
* Input          : none
* Output         : none
* Calls          : none
* Gets called by : writeStringToLCD(), writeCharToLCD()
*
* This function is the second backbone of the program. After writing a value to PORTD
* (defined as LCD_DATA_PORT) that one wish to have displayed on the screen this function
* must be called.
* It works similar to lcdEnableCommandMode function, except this function sets the register select
* bit (PINB1) to a logic one, meaning that the LCD will interpret the incoming byte as data to be
* displayed.
* Similar action is done to the enable bit as in command function.
**********************************************************************************************/
void lcdEnableDataMode(){
	LCD_CONTROL_PORT |= (1<<PINB1); //Register select = 1  == data mode
	LCD_CONTROL_PORT |= (1<<PINB0); //Enable bit = high
	_delay_ms(100);                 // delay for 100ms for IO unit to catch up
	LCD_CONTROL_PORT &= ~(1<<PINB0); //Enable bit written low - falling edge triggered
}


/**********************************************************************************************
* Function name  : writeVoltMeterModeLCD()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD()
* Gets called by : voltMeterOutput()
*
* Simply write VM top right corner of LCD.
**********************************************************************************************/
void writeVoltMeterModeLCD(){
	cursorControl = 0x8E; //cursor top right corner
	writeCharToLCD('V');
	writeCharToLCD('M');
}

/**********************************************************************************************
* Function name  : writePhotoResistorSensorModeLCD()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD()
* Gets called by : photoResistorSensorOutput()
*
* Simply write PR top right corner of LCD.
**********************************************************************************************/
void writePhotoResistorSensorModeLCD(){
	cursorControl = 0x8E;   //cursor top right corner
	writeCharToLCD('P');
	writeCharToLCD('R');
}

/**********************************************************************************************
* Function name  : writeSoilHumiditySensorModeLCD()
* Input          : none
* Output         : none
* Calls          : writeCharToLCD()
* Gets called by : soilHumiditySensorOutput()
*
* Simply write HM top right corner of LCD.
**********************************************************************************************/
void writeSoilHumiditySensorModeLCD(){
	cursorControl = 0x8E; //cursor top right corner
	writeCharToLCD('H');
	writeCharToLCD('M');
}