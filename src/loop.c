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
// OpenGL includes
#include <glew.h>
// Standard C includes
#include <stdio.h>
// .h includes
#include "loop.h"
#include "game.h"
#include "window.h"
#include "input.h"

/*
 * Variable definitions
 */

/*
 * Function definitions
 */
// Everything in the game happens here
// Used by game.c
void theLoop()
{
    while( eCurrentState != QUIT )
    {
        inputManager();
        drawScreen();
    }
}
