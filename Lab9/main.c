/*
 * Lab9_1.c
 *
 * Created: 21/05/2021 12:26:36
 * Author : David Ramon Alaman
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

uint8_t state = 0; 
uint8_t tiempo = 0; //Time of pulsation 
uint8_t count = 0; //Countdown counter
char snumero[3]; //Output string

void cerostate(); //State 1 - Countdown setting-start
void countdown(); //State 2 - Countdown
void enddcount(); //State 3 - Final state

int main(void)
{
 
	DDRD &= ~(1 << DDD4); //Set DDRD4 input
	PORTD |= (1 << PORTD4); //Enable Pull-up
	DDRD |= (1 << DDD6); //Set DDRD4 output  

	lcd_init(LCD_DISP_ON); //Init LCD

    while (1) 
    {
		if(!state) //Check if state 0 
		{
			lcd_clrscr(); //Clear LCD
			lcd_puts("Introduce time:"); 
			while (!state)
			{
				cerostate(); //State 0
			}
		}
		else if(state == 1) //Check if state 1
		{
			lcd_clrscr(); //Clear LCD
			lcd_puts("Countdown:");
			lcd_gotoxy(0, 1); 
			lcd_puts(snumero);
			countdown(); //State 1
		}
		else { //Else state 2
			enddcount(); //State 2
		}
	}
}

void cerostate(){ //State 0
	if (!(PIND & (1 << PIND4))) //If pushed
	{
		while(!(PIND & (1 << PIND4))) //While pushed
		{
			tiempo ++; //Time counter 
			_delay_ms(100);
		}
		if (tiempo >= 20) //If more than 2 seconds
		{
			state = 1; //Change to stage 1
		}
		else //Else increment the countdown
		{
			count ++;
			itoa(count, snumero, 10);
			lcd_gotoxy(0, 1);
			lcd_puts(snumero);
		}
	}
	tiempo = 0; //Reset time counter
}

void countdown(){ //State 1
	while (count)	//While there is time in countdown
	{
		_delay_ms(1000);
		count --;	//Subtract 1 of the countdown
		itoa(count, snumero, 10);
		lcd_gotoxy(0, 1);
		lcd_puts(snumero);
	}
	state = 2; //Change to state 2
}

void enddcount(){ //State 2
	if(state == 2){	//Set LCD
		lcd_clrscr();
		lcd_puts("Finish!:");
		state ++;
		PORTD |= (1 << PORTD6); //Turn on LED
	}
	
	tiempo ++; //Blink counter
	_delay_ms(10);  
	
	if(tiempo > 50){
		PORTD ^= (1 << PORTD6); //Toggle LED state
		tiempo = 0; //Reset blink counter
	}
	
	if(!(PIND & (1 << PIND4))) //If pushed button
	{
		PORTD &= ~(1 << PORTD6); // Turn off LED
		state = 0; //Return to state 0
		tiempo = 0; //Reset blink counter
	}
}