/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
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
#include "window.h"
#include "system.h"

/*
 * Outer variable definitions
 */
// Screen dimension constants
// Used by system.c
// !! Constants: all caps with underscores
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

/*
 * Outer function definitions
 */
// Draw to the screen
// Used by game.c
void drawScreen()
{
    // Clear screen
    glClearDepth( 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Swap GL buffers
    SDL_GL_SwapWindow( sdlWindow );

    // Wait 5 seconds
    SDL_Delay( 5000 );
}
