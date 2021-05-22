/*
 * Lab9_2.c
 *
 * Created: 22/05/2021 23:17:15
 * Author : David Ramon Alaman
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

uint8_t numero[5]; //Lottery number
uint8_t position = 0; //index
uint8_t counter = 0; //Pseudo random generator
uint8_t state = 0;

void selectNum(); //State 0

int main(void){
	
	DDRD &= ~(1 << DDD4); //Set PD4 as input
	PORTD |= (1 << PORTD4); //Enable pull up resistor PD4
	lcd_init(LCD_DISP_ON);
	
    while (1){
		if (!state){ //State 0
			lcd_clrscr();
			lcd_puts("Get a number: ");
			lcd_gotoxy(0,1);
			selectNum();
		}
		else { //State 1
			lcd_clrscr();
			lcd_puts("Congratulations:");
			lcd_gotoxy(0, 1);
			for (position = 0; position <= 4; position ++){ 
				lcd_putc((char) (numero[position] + 48)); 
			} //Print 5 digit lottery number
			while(PIND & (1 << PIND4)){
				//Wait until pushed button
			}
			_delay_ms(100);
			state = 0;
			position = 0;
		}
    }
}

void selectNum(){
	while(position <= 4){ //Wait until we have 5 numbers
		counter ++; 
		if(!(PIND & (1 << PIND4))){ //Pushed
			numero[position] = counter % 10; //Take a random digit
			lcd_putc((char) (numero[position] + 48)); //Print the digit
			position++; 
			_delay_ms(100);
		}
	}
	state = 1;
}