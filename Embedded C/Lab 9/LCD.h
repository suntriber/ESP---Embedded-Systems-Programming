/*
 * LCD.h
 *
 * Created: 2020-05-26 09:09:11
 *  Author: Patric
 */ 


#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000
#define LCD_DATA_DDR DDRD
#define LCD_DATA_PORT PORTD
#define LCD_DATA_PIN PIND
#define LCD_CONTROL_DDR DDRB
#define LCD_CONTROL_PORT PORTB
#define LCD_CONTROL_PIN PINB

void clearScreenLCD();
void resetCursor();
void initializeLCD();
void lcdEnableCommandMode();
void lcdEnableDataMode();
void writeCharToLCD(unsigned char charData);
void writeStringToLCD(char* stringPointer);
void writeVoltMeterModeLCD();
void writePhotoResistorSensorModeLCD();
void writeSoilHumiditySensorModeLCD();
void setCursorOnSecondRow();


#endif /* LCD_H_ */