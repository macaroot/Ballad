/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
// SDL2 includes
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
// Standard C includes
#include <stdio.h>
// .h includes
#include "input.h"
#include "game.h"
#include "input.h"
/*
 * Variable definitions
 */

/*
 * Function definitions
 */
void inputManager()
{
	// SDL2 event handle
	SDL_Event sdlE;

	// Event queue
	while( SDL_PollEvent( &sdlE ) != 0 )
	{
		if( sdlE.type == SDL_QUIT )
		{
			eCurrentState = QUIT;
		}
		else if( sdlE.type == SDL_KEYDOWN )
		{
			switch( sdlE.key.keysym.sym )
			{
				case SDLK_ESCAPE: ;
					eCurrentState = QUIT;
					break;
				default:
					return;
			}
		}
	}
}
