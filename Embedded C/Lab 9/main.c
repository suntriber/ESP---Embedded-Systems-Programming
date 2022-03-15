/*
 * Lab 9 - Patric Sandberg.c
 *
 * Created: 2020-05-25 07:52:10
 * Author : Patric
 */ 
/**********************************************************************************************
* Function name  :
* Input          :
* Output         :
* Calls          :
* Gets called by :
*
*
**********************************************************************************************/
#include <avr/io.h>
#include "LCD.h"
#include "voltMeterModule.h"
#include "photoResistorSensorModule.h"
#include "soilHumiditySensorModule.h"
#include "errorAlert.h"
#define F_CPU 16000000

#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

uint8_t modeLCD = 3;
uint8_t extraTime = 0;
void initADC();
void startConversion();



/**********************************************************************************************************************************************
* Program info:
*
*
************************************************************************************************************************************************/




/**********************************************************************************************
* Function name  : initADC()
* Input          : none
* Output         : none
* Calls          : none
* Gets called by : main()
*
* This functions purpose is to initialize settings for ADC.
* It chooses 5V as reference voltage source in the ADMUX register.
* It enables ADC and sets prescaler to 128 in the ADCSRA register.
* Finally, it disables digital input from the corresponding ADC pin, which is pin 5 in this case.
**********************************************************************************************/
void initADC(){
	ADMUX |= (1 << REFS0);   // ADC Multiplexer Selection Register
	// REFS0 = 5V reference source selected
	
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	// ADC Control and status register - ADEN = enable bit
	// ADIE = ADC Interrupt Enable
	// ADPS0-2 = Prescaler set to 128 for ADC

	DIDR0 |= (1 << ADC5D) | (1 << ADC4D) | (1 << ADC3D);  // Digital Input Disable Register 0
	// When this bit is written logic one, the digital input buffer on the
	// corresponding ADC pin is disabled.
}

/**********************************************************************************************
* Function name  : startConversion()
* Input          : none
* Output         : none
* Calls          : none
* Gets called by : main()
*
* This functions purpose is to start an analog-to-digital conversion.
* It is done by writing a one to the ADSC (Analog Digital Start Conversion) bit in the ADCSRA
* (Analog Digital Conversion Status Register) register.
* When this bit is written a one, conversion will start.
* This must happen for each and every conversion so it makes sense to have it in its own function.
**********************************************************************************************/
void startConversion(){
	ADCSRA |= (1 << ADSC);   // ADC Start Conversion
	// In single conversion mode, write this bit to one to start
	// each conversion.
	// ADSC will read as one as long as a conversion is in progress.
	// When the conversion is complete, it returns to zero
}




/**********************************************************************************************
* Function name  : ISR(TIMER2_COMPA_vect)
* Input          : none
* Output         : none
* Calls          : 
* Gets called by : compare match with register OCR2B and TCNT2 (timer2 counter)
*
* ISR routine for timer2.
* When timer2 counter matches value in OCR2A register, it will trigger an interrupt for this function.
**********************************************************************************************/
ISR(TIMER2_COMPA_vect){
	extraTime++;                 // increment extraTime variable 
	if (extraTime == 100){       // if extraTime is 100, means one second has passed
		PORTB ^= (1 << PORTB3);  // toggle red LED
		extraTime = 0;           // reset extraTime to 0 means wait another second before next toggle
	}
}


/**********************************************************************************************
* Function name  : ISR(PCINT0_vect)
* Input          : none
* Output         : none 
* Calls          :
* Gets called by : logic pin state change on PINB4
*
* Function simply checks global variable modeLCD. If its three, it is reset to zero.
* It is then incremented by 1.
* This way the global variable will always be between 1-3.
**********************************************************************************************/
ISR(PCINT0_vect){
	
	_delay_ms(100);          // delay to counter debounce-effect
	if (modeLCD == 3){       // if modeLCD is three
			 modeLCD = 0;    // set it to 0
		 }
		 modeLCD++;          // increment modeLCD by 1
	
}

/**********************************************************************************************
* Function name  : initPCInt()
* Input          : none	
* Output         : none
* Calls          : 
* Gets called by : main()
*
* Function for initializing Pin Change Interrupt on PINB4.
* The function will set the necessary parameters to enable an interrupt
* should the state of PINB4 change in any way.
**********************************************************************************************/
void initPCInt(){
	DDRB &= ~(1<<PINB4);  // setting PINB4 as INPUT
	PORTB |= (1<<PINB4);  // enable pull-up resistor on PINB4
	PCICR |= (1<<PCIE0);  // enable pin change interrupt on PCI0-vector
	PCMSK0 |= (1<<PCINT4);  // enable pin change interrupt on pin4 in the PCI0-vector (PINB4)
	
}


/**********************************************************************************************
* Function name  : callForReading()
* Input          : none
* Output         : none
* Calls          : initADCVoltageMeter(), voltMeterOutput(), initADCPhotoResistorSensor(), 
* photoResistorSensorOutput(), initADCSoilHumiditySensor(), soilHumiditySensorOutput()
* Gets called by : main()
*
* A switch function to check global variable modeLCD and call appropriate initialization and
* display output functions.
**********************************************************************************************/
void callForReading(){
	
	switch(modeLCD){            // check global variable "modeLCD"
		
		case 1:                    // if 1
		initADCVoltageMeter();     // init voltageMeter
		voltMeterOutput();         // display output
		break;
		
		case 2:                         // if 2
		initADCPhotoResistorSensor();   // init photo resistor
		photoResistorSensorOutput();    // display output
		break;
		
		case 3:                         // if 3
		initADCSoilHumiditySensor();    // init humidity sensor
		soilHumiditySensorOutput();     // display output
		break;
		
		default:
		break;
		
	}
}


/**********************************************************************************************
* Function name  : main()
* Input          : none
* Output         : none
* Calls          : intializeLCD(), initADC(), startConversion(), outputIncomingVoltage(), _delay_ms(), clearScreenLCD(), resetCursor()
* Gets called by : program start
*
* Main function is the start of the program.
* It start by calling initializeLCD function.
* Then initialization for ADC is called, followed by pin change interrupt initialization.
* Global interrupts are enabled and LED are initalized.
* Afterwards a while-loop continuously iterates doing AD-conversion and presenting result.
* Mode is changed via pin change interrupt at PINB4, and should any reading be higher then 80%
* the red LED will start to blink.
**********************************************************************************************/
int main(void)
{
	initializeLCD();  // initialization for LCD
	initADC();        // initialization for ADC
	initPCInt();      // initialization for pin change
	sei();            // enable interrupts
	DDRB |= (1<<PORTB2) | (1<<PORTB3);  //LED are output
	PORTB |= (1<<PINB2);                // blue LED start on
	
	
	while (1)
	{
		startConversion();  // start AD-conversion
		callForReading();   // display ADC-result dependant on mode
		
		
		if ((modeLCD == 3) & (ADC > 480)){   // if HM mode and reading is above 80%
			startErrorAlert();               // blink red LED
		}
		else if ((modeLCD == 2) & (ADC < 150)){   // if PR mode and reading is below 80%
			startErrorAlert();                    // blink red LED
		}
		
		else if ((modeLCD == 1) & (ADC > 800)){   // if VM mode and reading is above 80%
			startErrorAlert();                    // blink red LED
		}
		else {disableErrorAlert();}               // else keep blue LED on and red OFF
		
		
		resetCursor();  // place cursor on first column first row on LCD
	
		
	}
	return 0;
}


