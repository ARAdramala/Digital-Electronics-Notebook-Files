/*
 * ServoController.c
 *
 * Created: 04/06/2021 12:16:08
 * Author : David Ramon Alaman
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t state = 1;
float lecture = 0;


int main(void){
	DDRC |= (1 << DDC5); //PC5 out
	
    ADMUX |= (1 << REFS0); //Ref = AVcc
	ADMUX &= ~(1 << ADLAR); //Right adjust
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0)); //ADC 0
	ADCSRA |= (1 << ADATE); //Autotrigger
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //Timer presacale ADC = 128
	ADCSRA |= (1 << ADEN); //Enable ADC
	ADCSRA |= (1 << ADIE); //Enable interrupts
	ADCSRA |= (1 << ADSC); //Start ADC conversion
	
	sei(); //Enable global interrupts
	
	TCCR0A |= (1 << WGM01); //Timer CTC mode
	OCR0A = 46; //Initial value for timer0 comparator A
	TIMSK0 |= (1 << OCIE0A); //Enable interrupt when compared with 0CR0A
	
	TCCR0B |= (1 << CS02); //Set timer prescaler to 256
	TCCR0B &= ~((1 << CS01) | (1 << CS00)); //Set timer prescaler to 256
	
	 
    while (1){
	}
}

ISR(TIMER0_COMPA_vect){ //Timer interrupt
	
	state %= 3; 
	if(!state){ //HIGH
		PORTC |= (1 << PORTC5); //Set PC5
		OCR0A = (uint8_t)lecture; //Save lecture in comparator reg.
		TCCR0B |= (1 << CS02); //Set prescaler to 256
		TCCR0B &= ~((1 << CS01) | (1 << CS00)); //Set prescaler to 256
	}else{ //LOW
		PORTC &= ~(1 << PORTC5); //Clear PC5
		OCR0A = 154; //OCR0A for 10ms delay
		TCCR0B |= ((1 << CS02) | (1 << CS00)); //Set prescaler to 1024
		TCCR0B &= ~(1 << CS01); //Set prescaler to 1024
	}
	state ++; 
}

ISR(ADC_vect){ //ADC interrupt
	lecture = (94.0/1023.0)*ADCW + 46;
}