/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 */
// SDL2 includes
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
// Standard C includes
#include <stdio.h>
// .h includes
#include "game.h"
#include "system.h"
#include "window.h"
#include "loop.h"

/*
 * Outer variable definitions
 */
// Track game state
// Used by input.c, loop.c
eGameState eCurrentState = PLAY;

/*
 * Outer function definitions
 */
// Run the game; everything happens here
// Used by main.c
void runGame()
{
	systemInit();
	theLoop();
	systemQuit();
}
