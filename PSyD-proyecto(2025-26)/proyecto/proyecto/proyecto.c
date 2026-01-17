#include <s3c44b0x.h>
#include <s3cev40.h>
#include <common_types.h>
#include <system.h>
#include <segs.h>
#include <pbs.h>
#include <keypad.h>
#include <timers.h>
#include <lcd.h>
#include <iic.h>
#include <uda1341ts.h>
#include <iis.h>

#include "config.h"
#include "random.h"
#include "pixmaps.h"
#include "game.h"
#include "player.h"
#include "playerShot.h"

#include "kernelcoop.h"

/////////////////////////////////////////////////////////////////////////////
// Declaraci�n de tareas
/////////////////////////////////////////////////////////////////////////////

void player_update_task( void );
void playerShot_update_task( void );
void swarm_update_task( void );
void enemyShot_launch_task( void );
void enemyShot_update_task( void );
void ufo_launch_task( void );
void ufo_update_task( void );
void keys_read_task( void );
void pbs_read_task( void );

/////////////////////////////////////////////////////////////////////////////
// Declaraci�n de otras funciones
/////////////////////////////////////////////////////////////////////////////

void wellcomeScreen_draw( void );
void gameOverScreen_draw( void );

Game game;

void main( void )
{
    
    sys_init();                   /* Inicializa el sistema */
    segs_init();
    timers_init();
    keypad_init(); 
    pbs_init();
    lcd_init();
    iic_init();
    uda1341ts_init();
    iis_init( IIS_DMA );
    
    lcd_on();

    random_init( (BCDSEC << 16) | (BCDMIN << 8) | BCDHOUR );   				/* Semilla el generador de numeros pseudoaleatorios */
    game_init( &game );                                         			/* Inicializa el juego */

    scheduler_init();                                           				/* Inicializa el kernel */
    create_task( pbs_read_task, PBS_READ_PERIOD/TICK_PERIOD );  				/* Crea las tareas de la aplicaci�n */
    create_task( ufo_launch_task, UFO_LAUNCH_PERIOD/TICK_PERIOD ); 				/* Crea la tarea del UFO */
    create_task( ufo_update_task, UFO_UPDATE_PERIOD/TICK_PERIOD );				/* Mueve el UFO */
    create_task( player_update_task, PLAYER_UPDATE_PERIOD/TICK_PERIOD );		// Muestra la nave del jugador
    create_task( keys_read_task, KEYS_READ_PERIOD/TICK_PERIOD );				// Leer del keypad
    create_task( playerShot_update_task, PLAYERSHOT_UPDATE_PERIOD/TICK_PERIOD );// Mueve la bala del jugador
    create_task( swarm_update_task, SWARM_UPDATE_PERIOD/TICK_PERIOD );
    create_task( enemyShot_update_task, ENEMYSHOT_LAUNCH_PERIOD/TICK_PERIOD );
    create_task( enemyShot_launch_task, ENEMYSHOT_UPDATE_PERIOD/TICK_PERIOD );


    while( 1 )
    {
        wellcomeScreen_draw();
        game_launch( &game );                                    /* Lanza el juego */

        timer0_open_tick( scheduler, TICKS_PER_SEC );            /* Arranca multitarea */




        while( game.player.lives.value > 0 )
        {

            /* sleep(); */  // descomentar cuando funcione
            dispacher();
        }
        timer0_close();                                          /* Para multitarea */
            
        gameOverScreen_draw();
        game_restart( &game );
    }  
}

void player_update_task( void )
{
	player_update(&game.player);
}

void ufo_launch_task( void )
{   
     if( random_get() & 0x1 )                                      /* Lanza UFOs con probabilidad del 50% */
        ufo_launch( &game.ufo );
}

void ufo_update_task( void )
{
    ufo_update( &game.ufo );
}

void playerShot_update_task( void )
{   
	playerShot_update( &game.playerShot, &game.shield, &game.swarm, &game.enemyShot, &game.ufo);
}

void swarm_update_task( void )
{
}

void enemyShot_update_task( void )
{
}

void enemyShot_launch_task( void )
{
}

void keys_read_task( void )
{
	static boolean init = TRUE;
	    static enum { wait_keydown, scan, wait_keyup } state;

	    if( init )
	    {
	        init  = FALSE;
	        state = wait_keydown;
	    }
	    else switch( state )
	    {
	        case wait_keydown:
	            if( keypad_pressed() ) {
	                state = scan;
	            }
	            break;
	        case scan:
	            switch( keypad_scan() )
	            {
	            	case KEYPAD_KEY2:
	            		playerShot_launch(&game.playerShot, &game.player);
	            		break;
	            	case KEYPAD_KEY6:
                        player_right(&game.player);
                        state = wait_keyup;
                        break;
	                case KEYPAD_KEY5:
	                    player_left(&game.player);
                        state = wait_keyup;
                        break;
	                default:
	                    state = wait_keyup;
	            }
	            break;
	        case wait_keyup:
	            if( !keypad_pressed() ) {
	            	player_stop(&game.player);
	                state = wait_keydown;
	            }
	            break;
	    }
}

void pbs_read_task( void )
{
    static boolean init = TRUE;
    static enum { wait_keydown, scan, wait_keyup } state;

    if( init )
    {
        init  = FALSE;
        state = wait_keydown;
    }
    else switch( state )
    {
        case wait_keydown:
            if( pb_pressed() )
                state = scan;
            break;
        case scan:
            switch( pb_scan() )
            {
                case PB_RIGHT:
                case PB_LEFT:
                    credit_update( &game.credit, 1 );
                    state = wait_keyup;
                    break;
                default:
                    state = wait_keyup;
            }
            break;
        case wait_keyup:
            if( !pb_pressed() )
                state = wait_keydown;
            break;
    }
}

/*******************************************************************/


void wellcomeScreen_draw( void )
{
    lcd_clear();
    lcd_puts_x2( 48, 16, BLACK, "SPACE INVADERS" );
    lcd_puts( 48, 64, BLACK, "El juego consiste en conseguir" );
    lcd_puts( 80, 80, BLACK, "que no te maten o te invadan!" );

    lcd_puts( 20, 192, BLACK, "Para comenzar pulse cualquier tecla" );

    keypad_getchar();
    lcd_clear();
}

void gameOverScreen_draw( void )
{
    lcd_clear();
    lcd_puts( 36,  80, BLACK, "OH NO, has perdido :(" );
    lcd_puts( 20, 192, BLACK, "Para continuar pulse cualquier tecla" );
    keypad_getchar();
}
