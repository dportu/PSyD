/*
#include <s3c44b0x.h>
#include <s3cev40.h>
#include <timers.h>
#include <keypad.h>

extern void isr_KEYPAD_dummy( void );

void keypad_init( void )
{
    timers_init();  
};

uint8 keypad_scan( void )
{
    uint8 aux;

    aux = *( KEYPAD_ADDR + 0x1c );
    if( (aux & 0x0f) != 0x0f )
    {
        if( (aux & 0x8) == 0 )
            return KEYPAD_KEY0;
        else if( (aux & 0x4) == 0 )
            return KEYPAD_KEY1;
        else if( (aux & 0x2) == 0 )
            return KEYPAD_KEY2;
        else if( (aux & 0x1) == 0 )
            return KEYPAD_KEY3;
    }
	aux = *( KEYPAD_ADDR + ... );
	if( (aux & 0x0f) != 0x0f )
	{
		if( (aux & 0x8) == 0 )
			return KEYPAD_KEY4;
		else if( (aux & 0x4) == 0 )
			return KEYPAD_KEY5;
		else if( (aux & 0x2) == 0 )
			return KEYPAD_KEY6;
		else if( (aux & 0x1) == 0 )
			return KEYPAD_KEY7;
	}
    ...

    return KEYPAD_FAILURE;
}

uint8 keypad_pressed( void )
{
    return !( PDATG & (1<<1) );
}

uint8 keypad_getchar( void )
{
    uint8 scancode;

	while( ... );
	sw_delay_ms( KEYPAD_KEYDOWN_DELAY  );

	scancode = keypad_scan();

	while( ... );
	sw_delay_ms( KEYPAD_KEYUP_DELAY );

	return scancode;    
}

uint8 keypad_getchartime( uint16 *ms )
{
	uint8 scancode;
	
	while( ... );
	timer3_start();
	sw_delay_ms( KEYPAD_KEYDOWN_DELAY );

	scancode = keypad_scan();

	while( ... );	
	*ms = timer3_stop() / 10;
	sw_delay_ms( KEYPAD_KEYUP_DELAY );

	return scancode;    
}

uint8 keypad_timeout_getchar( uint16 ms )
{
	uint8 scancode;

	timer3_start_timeout( 10*ms );
	while( ... );
	if( timer3_timeout() ) return KEYPAD_TIMEOUT;
	sw_delay_ms( KEYPAD_KEYDOWN_DELAY );
	
	scancode = keypad_scan();

	while( ... );
	if( timer3_timeout() ) return KEYPAD_TIMEOUT;
	sw_delay_ms( KEYPAD_KEYUP_DELAY ); 
    
 	return scancode;   
}

void keypad_open( void (*isr)(void) )
{
	pISR_KEYPAD = (uint32) isr;
	I_ISPC	    = BIT_KEYPAD;
	INTMSK     &= ~( BIT_GLOBAL | BIT_KEYPAD );
}

void keypad_close( void )
{
	INTMSK   |= BIT_KEYPAD;				   
	pISR_TICK = (uint32) isr_KEYPAD_dummy; 
}

*/
