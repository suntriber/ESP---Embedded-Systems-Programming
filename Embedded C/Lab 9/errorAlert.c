/*
 * errorAlert.c
 *
 * Created: 2020-05-29 07:24:04
 *  Author: Patric
 */ 
#include <avr/io.h>
#include <avr/delay.h>




/**********************************************************************************************
* Function name  : startErrorAlert()
* Input          : none
* Output         : none
* Calls          :
* Gets called by : main()
*
* This function will initialize Timer2, setting it in clear timer on compare mode
* with a 1024 prescaler. OCR2A register, which is the register that the timer counter
* compares with, is set to 156 and calculation is showed inside function.
* It will also turn off the blue LED. 
**********************************************************************************************/	
	void startErrorAlert(){
	TCCR2A |= (1<<WGM01);  // Set CTC (clear timer on compare) bit
	TCCR2B |= (1<<CS22) | (1<<CS20) | (1 << CS21);  // Set prescaler to 1024
	OCR2A = 156;  // Output compare register, value given due to overflow algorithm.
	PORTB &= ~(1 << PINB2);           // blue LED off
	/*  16000000 / 1024 = 15625               1sec with 1024 prescaler is 15625 ticks on timer counter
	*   15625 / 100     = 156.25              If 156 is matched 100 times with timer counter this still means one second (-1024/4 cycles)   
	*/                                        
	
	TIMSK2 |= (1<<OCIE2A);  // When timer value matches comparison value an interrupt will be issued
	_delay_ms(1);  
	
}
/**********************************************************************************************
* Function name  : disableErrorAlert()
* Input          : none
* Output         : none
* Calls          :
* Gets called by : main()
*
* Basically the inverse function of startErrorAlert().
* Each bit being set in startErrorAlert is unset here, meaning timer2 is turned off.
* It will also turn red LED off and blue LED on.
**********************************************************************************************/
void disableErrorAlert(){
	TCCR2A &= ~(1<<WGM01);      // unset clear timer on compare bit
	TCCR2B &= ~(1<<CS22) | (1<<CS20) | (1 << CS21);    // unset prescaler bits
	TIMSK2 &= ~(1<<OCIE2A);      // unset interrupt bit
	PORTB &= ~(1 << PINB3);      // red LED off
	PORTB |= (1 << PINB2);       // blue LED on
	
	_delay_ms(1);
}