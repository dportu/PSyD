/*
#include <s3c44b0x.h>
#include <uart.h>

void uart0_init( void )
{  
    UFCON0  = ...;	           // FIFOs activadas
    UMCON0  = ...;	           // Control de flujo manual
	ULCON0  = ...;       	   // normal (no infrarojos), sin paridad, 1 bit de stop, 8 bits de datos
	UBRDIV0 = ...;             // 115200 bps asumiendo 64MHz
    UCON0   = ...;             // Tx int/polling, Rx int/polling
}

void uart0_putchar( char ch )
{
    while( ... );
    ... = ch;
}        

char uart0_getchar( void )
{
    while( ... );
    return ...;
}

void uart0_puts( char *s )
{
    ...
}

void uart0_gets( char *s )
{
    ...
}

void uart0_putint( int32 i )
{
	char buf[10 + 2];
	char *p = buf + 10 + 1;

	*p = '\0';

	if( i >= 0 )
	{
        ...
	}
	else
	{
		...
	}

	uart0_puts( p );
}

void uart0_puthex( uint32 i )
{
    char buf[8 + 1];
    char *p = buf + 8;
    uint8 c;

    *p = '\0';

    do {
        c = i & 0xf;
        if( c < 10 )
            *--p = '0' + c;
        else
            *--p = 'a' + c - 10;
        i = i >> 4;
    } while( i );

    uart0_puts( p );
}

int32 uart0_getint( void )
{
	char s[256];
	char *p = s;
	int32 acc = 0;
	boolean neg = FALSE;

	uart0_gets( s );

	if( *p == '-' )
	{
		neg = TRUE;
		p++;
	}
	while( *p ) 
    {
       ...
    }
	if( neg )
		acc = -acc;
	return acc;
}

uint32 uart0_gethex( void )
{
	char s[256];
	char *p = s;
	uint32 acc = 0;

	uart0_gets( s );

	while( *p )
		if( *p >= 'A' && *p <= 'F'  )
			acc = (acc<<4) + ((*p++) - 'A' + 10);
		else if( *p >= 'a' && *p <= 'f'  )
			acc = (acc<<4) + ((*p++) - 'a' + 10);
		else
			acc = (acc<<4) + ((*p++) - '0');

	return acc;
}
*/