/*
#include <s3c44b0x.h>
#include <s3cev40.h>
#include <rtc.h>

extern void isr_TICK_dummy( void );

void rtc_init( void )
{
    TICNT   = 0;			// Tick desactivado
	RTCALM  = 0;			// Alarma desactivada	
	RTCRST  = 0;			// Round reset desactivado 
		
	RTCCON  = 0x1;			// No reset, merge BCD Counters, XTAL, activar R/W de registros
	
    BCDYEAR = (0x13);		// 2013
    BCDMON  = (0x01);       // enero
    BCDDAY  = (0x01);       // 1
    BCDDATE = (0x03);       // martes SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7
    BCDHOUR = (0x00);
    BCDMIN  = (0x00);
    BCDSEC  = (0x00);

    ALMYEAR = 0;			// Inicializa registros de alarma
    ALMMON  = 0;
    ALMDAY  = 0;
    ALMHOUR = 0;
    ALMMIN  = 0;
    ALMSEC  = 0;
}

void rtc_puttime( rtc_time_t *rtc_time )
{  
    BCDYEAR = ...;
    BCDMON  = ...;
    BCDDAY  = ...;
    BCDDATE = ...;
    BCDHOUR = ...;
    BCDMIN  = ...;
    BCDSEC  = ...;
}

void rtc_gettime( rtc_time_t *rtc_time )
{
    rtc_time->year = ...;
    rtc_time->mon  = ...;
    rtc_time->mday = ...;
    rtc_time->wday = ...;
    rtc_time->hour = ...;
    rtc_time->min  = ...;
    rtc_time->sec  = ...;
    if( ! rtc_time->sec ){
        rtc_time->year = ...;
        rtc_time->mon  = ...;
        rtc_time->mday = ...;
        rtc_time->wday = ...;
        rtc_time->hour = ...;
        rtc_time->min  = ...;
        rtc_time->sec  = ...;
    };
}

void rtc_open( void (*isr)(void), uint8 tick_count )
{
    pISR_TICK = ...;
    I_ISPC    = ...;
    INTMSK   &= ...;
    TICNT     = ...;
}

void rtc_close( void )
{
    TICNT     = ...;  
    INTMSK   |= ...;    
    pISR_TICK = ...;
}
*/