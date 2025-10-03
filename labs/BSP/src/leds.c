
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
		PDATB |= ~ (1 << 10);
	}
	else {
		PDATB |= ~ (1 << 9);
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
		PDATB &= ~ (PDATB & 0x100); //en caso de que sean 11 bits
	}
	else {
		PDATB &= ~ (PDATB & 0x80); //en caso de que sean 11 bits
	}
}

uint8 led_status( uint8 led )
{
    ...
}

