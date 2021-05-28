/*
 * TemperatureSensor.c
 *
 * Created: 28/05/2021 13:42:31
 * Author : David Ramon Alaman
 */ 

#include <avr/io.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SEG7_HC595.h"

float Temperature;
uint8_t units, tenth, tens;
uint16_t disp_Te, disp_te, disp_un;

int main(void){
    
	ADMUX |= (1 << REFS0); //Use AVcc as the reference
	ADMUX |= (1 << MUX2); //Read ACD4
	ADMUX &= ~((1 << MUX3) & (1 << MUX1) & (1 << MUX0)); //Read ACD4
	ADCSRA |= (1 << ADATE); //Set ADC autotrigger
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Timer 128 prescale
	ADCSRA |= (1 << ADEN); //Enable ADC
	ADCSRA |= (1 << ADIE); //Enable interrupts
	
	sei(); //Enable interrupts 
	ADCSRA |= (1 << ADSC); //Start ADC conversion
	
	HC595Init(); //Initialize HC595 system
	
	while (1){
		tens = (unsigned int)(Temperature/10)%10; //Extract the temperature tens
		tens = led_pattern[tens]; //Convert the tens into 7-segment common anode code
			
		units=(unsigned long int)(Temperature)%10; //Extract the temperature units
		units=led_pattern[units]; //Convert the units into 7-segment common anode code
			
		tenth=(unsigned long int)(Temperature*10)%10;//Extract the temperature tenths 
		tenth=led_pattern[tenth]; //Convert the tenths into 7-segment common anode code
		
		disp_Te = ((tens<<8)|0x02); //Tens value in second digit (NO OUTPUT)
		disp_un = ((units<<8)|0x04); //Units value in the third digit
		disp_te = ((tenth<<8)|0x08); //Tenths value in the forth digit
			
		HC595Write(0X7F04); //Decimal point
		HC595Write(disp_Te); //Write the tens data to HC595
		HC595Write(disp_un); //Write the units data to HC595
		HC595Write(disp_te); //Write the tenths data to HC595
		HC595Write(0XFF01); //Turn off first digit of display
	}
}
ISR(ADC_vect){ //ADC interrupts
	Temperature = 100*(ADCW*5.0)/1023.0; //Calculate temperature value
}


