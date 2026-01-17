#include "config.h"
#include "pixmaps.h"
#include "wavs.h"
#include "player.h"

static void player_draw( Player *self );
static void player_clear( Player *self );

void player_init( Player *self )
{
    self->state = playerStopped;
    self->col = PLAYER_MIN_COL;
    self->row = PLAYER_ROW;
    self->sprite = (Sprite){ PLAYER_WIDTH, PLAYER_HEIGHT, playerPixMap };
    self->explosionSpriteSet = 0;
    self->explosionSprite[0] = (Sprite){ PLAYER_WIDTH, PLAYER_HEIGHT, playerExplosionPixMap_0 };
    self->explosionSprite[1] = (Sprite){ PLAYER_WIDTH, PLAYER_HEIGHT, playerExplosionPixMap_1 };
    self->explosionSound     = (Sound){ PLAYER_EXPLOSION };
    lives_init( &self->lives );
    score_init( &self->score );
}

static void player_draw( Player *self )
{ 
	sprite_draw(&self->sprite, self->col, self->row);
}

static void player_clear( Player *self )
{
	sprite_clear(&self->sprite, self->col, self->row);
}

void player_launch( Player *self )
{
	player_draw(self);
}

void player_update( Player *self )
{
	player_clear(self);

	player_state_t s = self->state;
	switch (s) {
	case playerStopped:
		break;
	case playerMovingLeft:
		if(self->col - PLAYER_ADVANCE_COL >= PLAYER_MIN_COL) {
			self->col -= PLAYER_ADVANCE_COL;
		}
		break;
	case playerMovingRight:
		if(self->col - PLAYER_ADVANCE_COL < PLAYER_MAX_COL) {
			self->col += PLAYER_ADVANCE_COL;
		}
		break;
	case playerExploding:
		self->sprite.pixMap = playerExplosionPixMap_0;
		break;
	case playerDead:
		self->sprite.pixMap = playerExplosionPixMap_1;
		break;
	}

	player_draw(self);
}

void player_left( Player *self )
{
	if(self->state != playerDead) {
		self->state = playerMovingLeft;
	}

}

void player_right( Player *self )
{
	if(self->state != playerDead) {
		self->state = playerMovingRight;
	}

}

void player_stop( Player *self )
{
	self->state = playerStopped;
}

void player_hit( Player *self )
{
	if((--self->lives.value) < 1) {
		self->state = playerDead;
	}
}

void player_invaded( Player *self )
{
	//TODO
}
