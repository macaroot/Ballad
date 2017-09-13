/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
/* SDL2 includes */
#include <SDL.h>
/* Standard C includes */
#include <stdio.h>
/* .h includes */
#include "logic.h"
#include "graphics.h"
#include "data.h"

/*****************************************************************************
 * Getsetted variables                                                       *
 *****************************************************************************/

struct sSpriteList
/*{{{*/
{
	int modusFlux;
	int modusFlags;
	int position[2];
	int* graphic;
};
sSPRITELIST sSprite[10];/*}}}*/

/*****************************************************************************
 * Local variables                                                           *
 *****************************************************************************/

typedef enum eGamestate
/*{{{*/
{
	QUIT,
	PLAY
} eGAMESTATE;
eGAMESTATE gamestateMain;/*}}}*/

typedef struct sMouseEntity sMOUSE;
/*{{{*/
struct sMouseEntity
{
	int modusFlux;
	int modusFlags;
	int position[2];
	int pressed;
	int* graphic;
};
sMOUSE mouseMain;/*}}}*/

typedef struct sSquareEntity sSQUARE;
struct sSquareEntity
/*{{{*/
{
	int modusFlux;
	int modusFlags;
	int position[2];
	int* graphic;
};
sSQUARE sSquare;/*}}}*/

/*****************************************************************************
 * Getset definitions                                                        *
 *****************************************************************************/

void* spriteList_getPointer( void )
/*{{{*/
{
	return sSprite;
}
int spriteList_getModusFlags( sSPRITELIST* p, int index )
{
	return p[index].modusFlags;
}
void spriteList_setModusFlags( sSPRITELIST* p, int index, int newInt )
{
	p[index].modusFlags = newInt;
}
int spriteList_getModusFlux( sSPRITELIST* p, int index )
{
	return p[index].modusFlux;
}
void spriteList_setModusFlux( sSPRITELIST* p, int index, int newInt )
{
	p[index].modusFlux = newInt;
}
void spriteList_getPosition( sSPRITELIST* p, int index, int** fetcher )
{
	*fetcher = p[index].position;
}
void spriteList_setPosition( sSPRITELIST* p, int index, int* newArr )
{
	p[index].position[0] = newArr[0];
	p[index].position[1] = newArr[1];
}
int* spriteList_getGraphic( sSPRITELIST* p, int index )
{
	return p[index].graphic;
}
void spriteList_setGraphic( sSPRITELIST* p, int index, int* newArr )
{
	p[index].graphic = newArr;
}/*}}}*/

/*****************************************************************************
 * Local                                                                     *
 *****************************************************************************/

/* Initialize mouse */
void generateMouse( sMOUSE* p )
/*{{{*/
{
	p->modusFlags = 0;
	p->modusFlux = 0;
	p->graphic = imgCursor;
	p->pressed = 0;
	p->position[0] = 0;
	p->position[1] = 0;
}/*}}}*/

void generateSquare( sSQUARE* p )
/*{{{*/
{
	p->modusFlags = 0;
	p->modusFlux = 0;
	p->graphic = imgSquare;
	p->position[0] = 0;
	p->position[1] = 0;
}/*}}}*/

/* Catch input and set flags */
void vInputManager( void )
/*{{{*//*{{{*//*
 * - SDL2 event handle
 * - PollEvent is event queue
 *//*}}}*/
{
	SDL_Event sdlE;
	SDL_GetMouseState( &mouseMain.position[0], &mouseMain.position[1] );
	while( SDL_PollEvent( &sdlE ) != 0 )
	{
		if( sdlE.type == SDL_QUIT )
		{
			gamestateMain = QUIT;
		}
		if( sdlE.type == SDL_KEYDOWN )
		{
			switch( sdlE.key.keysym.sym )
			{
				case SDLK_ESCAPE: ;
					gamestateMain = QUIT;
					break;
				default:
					return;
			}
		}
		if( sdlE.type == SDL_MOUSEBUTTONDOWN )
		{
			mouseMain.pressed = 1;
		}
		if( sdlE.type == SDL_MOUSEBUTTONUP )
		{
			mouseMain.pressed = 0;
		}
	}
}/*}}}*/

/* Game logic, should manage near to everything */
void vLogic( void )
/*{{{*/
{
	mouseMain.modusFlags = 1;
	mouseMain.modusFlux = 0x1;
	spriteList_setModusFlags( sSprite, 0, mouseMain.modusFlags );
	spriteList_setModusFlux( sSprite, 0, mouseMain.modusFlux );
	spriteList_setPosition( sSprite, 0, mouseMain.position );
	spriteList_setGraphic( sSprite, 0, mouseMain.graphic );
	spriteList_setGraphic( sSprite, 1, sSquare.graphic );
	if( mouseMain.pressed )
	{
		spriteList_setPosition( sSprite, 1, mouseMain.position );
	}
}/*}}}*/

/* Pre-loop setups */
void vSetupGame( void )
/*{{{*/
{
	gamestateMain = PLAY;
	generateMouse( &mouseMain );
	generateSquare( &sSquare );
}/*}}}*/

/* Everything in the game itself happens here */
void vTheLoop( void )
/*{{{*//*{{{*//*
 * - End game when state is QUIT
 * - SDL_Delay() halts everything for ms, so might cause slowdowns at some
 *   point TODO What else needs time.  SDL_GetTicks() fetches how long SDL
 *   library has been initialized in ms 16ms about 63FPS, 33ms is about 33FPS
 *//*}}}*/
{
	vSetupGame();
	while( gamestateMain != QUIT )
	{
		SDL_Delay(33);
		vInputManager();
		vLogic();
		vDrawScreen();
	}
}/*}}}*/
