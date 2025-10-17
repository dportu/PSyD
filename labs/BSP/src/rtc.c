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
	BCDYEAR = ((rtc_time->year/10)<<4) + rtc_time->year%10;
	BCDMON  = ((rtc_time->mon/10)<<4) + rtc_time->mon%10;
	BCDDAY  = ((rtc_time->mday/10)<<4) + rtc_time->mday%10;
	BCDDATE = rtc_time->wday;
	BCDHOUR = ((rtc_time->hour/10)<<4) + rtc_time->hour%10;
	BCDMIN  = ((rtc_time->min/10)<<4) + rtc_time->min%10;
	BCDSEC  = ((rtc_time->sec/10)<<4) + rtc_time->sec%10;
}

void rtc_gettime( rtc_time_t *rtc_time )
{
	rtc_time->year = (BCDYEAR & 0xF) + (BCDYEAR >>4)*10;
	rtc_time->mon  = (BCDMON & 0xF) + (BCDMON >>4)*10;
	rtc_time->mday = (BCDDAY & 0xF) + (BCDDAY >>4)*10;
	rtc_time->wday = BCDDATE;
	rtc_time->hour = (BCDHOUR & 0xF) + (BCDHOUR >>4)*10;
	rtc_time->min  = (BCDMIN & 0xF) + (BCDMIN >>4)*10;
	rtc_time->sec  = (BCDSEC & 0xF) + (BCDSEC >>4)*10;
	if( ! rtc_time->sec ){
		rtc_time->year = (BCDYEAR & 0xF) + (BCDYEAR >>4)*10;
		rtc_time->mon  = (BCDMON & 0xF) + (BCDMON >>4)*10;
		rtc_time->mday = (BCDDAY & 0xF) + (BCDDAY >>4)*10;
		rtc_time->wday = BCDDATE;
		rtc_time->hour = (BCDHOUR & 0xF) + (BCDHOUR >>4)*10;
		rtc_time->min  = (BCDMIN & 0xF) + (BCDMIN >>4)*10;
		rtc_time->sec  = (BCDSEC & 0xF) + (BCDSEC >>4)*10;
	};
}

void rtc_open( void (*isr)(void), uint8 tick_count )
{
    pISR_TICK = (uint32)isr;
    I_ISPC    = BIT_TICK;
    INTMSK   &= ~(BIT_GLOBAL | BIT_TICK);
    TICNT     = (1 << 7) | (tick_count & 0x7F);
}

void rtc_close( void )
{
	TICNT     = 0x0;
	INTMSK   |= ((1<<20));
	pISR_TICK = (uint32) isr_TICK_dummy;
}
