
#include <s3c44b0x.h>
#include <leds.h>

void leds_init( void )
{
	led_off( RIGHT_LED );
	led_off( LEFT_LED );
}

void led_on( uint8 led )
{
	if(led == RIGHT_LED) {
		PDATB &= ~ (1 << 10);
	}
	else {
		PDATB &= ~ (1 << 9);
	}

}

void led_off( uint8 led )
{
	if(led == RIGHT_LED) {
		PDATB |= (1 << 10);
	}
	else {
		PDATB |= (1 << 9);
	}
}

void led_toggle( uint8 led )
{
	if(led == RIGHT_LED) {
		//PDATB &= ~ ((PDATB >> 9 ) <<9 );
		if(led_status(RIGHT_LED)) {
			led_off(RIGHT_LED);
		}
		else {
			led_on(RIGHT_LED);
		}
	}
	else {
		if(led_status(LEFT_LED)) {
			led_off(LEFT_LED);
		}
		else {
			led_on(LEFT_LED);
		}
	}
}

uint8 led_status( uint8 led )
{
	uint8 aux;
	if(led == RIGHT_LED) {
		return (PDATB >> 10) == 0;
	}
	else {
		return PDATB == (PDATB & (~ (1 << 9)));
		//aux = ~PDATB;
		//return aux == (aux | (1 << 9));
		//return (PDATB & aux) == 0;
	}
}

