/*
 * main.c
 *
 * Created: 5/14/2021 1:31:29 PM
 * Author: David Ramon Alaman
 *
 * Stepper Motor Lab Session 8
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t time = 20; //Time ctt
	
	DDRD = 0xFF; //Port D as output
	DDRB &= ~(1<<DDB0); //PB0 as input
	PORTB |= (1<<PORTB0); //Enable PB0 pull up res
	
	while(1) {
		if(PINB & (1 << PINB0)){ //Direction 
			PORTD = 0b10001010; //Clockwise
			_delay_ms(time);
			PORTD = 0b10001001;
			_delay_ms(time);
			PORTD = 0b10000101;
			_delay_ms(time);
			PORTD = 0b10000110;
			_delay_ms(time);
		} else {
			PORTD = 0b10000110; //Counterclockwise
			_delay_ms(time);
			PORTD = 0b10000101;
			_delay_ms(time);
			PORTD = 0b10001001;
			_delay_ms(time);
			PORTD = 0b10001010;
			_delay_ms(time);
		}
	}
}