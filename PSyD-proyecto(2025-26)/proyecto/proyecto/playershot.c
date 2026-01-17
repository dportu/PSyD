
// El alcanzado es el que estalla y suena



#include "config.h"
#include "pixmaps.h"
#include "wavs.h"
#include "playerShot.h"

static void playerShot_draw( PlayerShot *self );
static void playerShot_clear( PlayerShot *self );

void playerShot_init( PlayerShot *self )
{
    self->state           = noPlayerShot;
    self->sprite          = (Sprite){ PLAYERSHOT_WIDTH, PLAYERSHOT_HEIGHT, playerShotPixMap };
    self->explosionSprite = (Sprite){ PLAYERSHOT_EXPLOSION_WIDTH, PLAYERSHOT_EXPLOSION_HEIGHT, playerShotExplosionPixMap };
    self->launchSound     = (Sound){ PLAYERSHOOT_LAUNCH };
}

static void playerShot_draw( PlayerShot *self )
{   
	switch( self->state ) {
		case playerShotMovingUp:
			sprite_draw( &self->sprite, self->col, self->row );
			break;
		case playerShotExplodingCeiling:
		case playerShotExplodingShield:
			sprite_draw( &self->explosionSprite, self->col, self->row );
			break;
	}
}

static void playerShot_clear( PlayerShot *self )
{   
	if( self->state == playerShotMovingUp ) {
		sprite_clear( &self->sprite, self->col, self->row );
	}
	else {
		sprite_clear( &self->explosionSprite, self->col, self->row );
	}
}

void playerShot_launch( PlayerShot *self, Player *player )
{
	if (self->state == noPlayerShot) { // Solo se puede un disparo maximo
		self->shooter = player;
		self->col = player->col + (PLAYER_WIDTH / 2) - (PLAYERSHOT_WIDTH / 2) - 1;
		self->row = player->row - PLAYERSHOT_HEIGHT - 1;
		self->state = playerShotMovingUp;

		playerShot_draw(self);
	}
}

void playerShot_update( PlayerShot *self, Shield *shield, Swarm *swarm, EnemyShot *enemyShot, Ufo *ufo )
{   
	if (self->state != noPlayerShot) {
		playerShot_clear( self );

		switch (self->state) {
		case playerShotMovingUp:
			self->row -= PLAYERSHOT_ADVANCE_ROW;

			// Comprobar si la bala ha colisionado con algun objeto
			playerShot_onUfo(self, ufo);
			playerShot_onSwarm(self, swarm);
			playerShot_onShield(self, shield);
			playerShot_onEnemyShot(self, enemyShot);

			if (self->state == playerShotMovingUp && self->row <= PLAYERSHOT_MIN_ROW) {
				self->state = playerShotExplodingCeiling;
				self->countDown = ENEMYSHOT_EXPLODING_TIME/ENEMYSHOT_UPDATE_PERIOD;
			}
			break;
		case playerShotExplodingCeiling:
		case playerShotExplodingShield:
			if (--self->countDown == 0) {
				self->state  = noPlayerShot;
			}
			break;
		}

		if (self->state != noPlayerShot) {
			playerShot_draw( self );
		}
	}
}

void playerShot_onUfo( PlayerShot *self, Ufo *ufo )
{
	if (self->state != playerShotMovingUp) return;
	if (ufo->state != ufoMovingLeft && ufo->state != ufoMovingRight) return;

	if ( OVERLAP(self->col, ufo->col, UFO_WIDTH) && OVERLAP(self->row, ufo->row, UFO_HEIGHT) ) { // Si impacta con el ufo
		self->state = playerShotExplodingCeiling;
		self->countDown = ENEMYSHOT_EXPLODING_TIME/ENEMYSHOT_UPDATE_PERIOD;
		ufo->state = ufoExploding;
	}

}

void playerShot_onSwarm( PlayerShot *self, Swarm *swarm )
{
}


void playerShot_onShield( PlayerShot *self, Shield *shield )
{
}

void playerShot_onEnemyShot( PlayerShot *self, EnemyShot *enemyShot )
{
}

