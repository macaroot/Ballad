/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 */
// SDL2 includes
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
// Standard C includes
#include <stdio.h>
// .h includes
#include "system.h"
#include "window.h"

/*
 * Inner variable initialization
 */
// SDL2 surface pointer to NULL for error recognition
SDL_Surface* sdlSurface = NULL;

/*
 * Inner function initialization
 */

int initVideo()
{
	// Initialize SDL2
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not be initialized! SDL_Error: %s\n",
				SDL_GetError() );
		return 0;
		systemQuit();
	}
	return 1;
}

int initWindow()
{
	// Create window
	sdlWindow = SDL_CreateWindow(
			"Ballad",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL );
	if( sdlWindow == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n",
				SDL_GetError() );
		return 0;
		systemQuit();
	}
	return 1;
}

int initRenderer()
{
	sdlRenderer = SDL_CreateRenderer(
			sdlWindow,
			-1,
			SDL_RENDERER_ACCELERATED );
	if( sdlRenderer == NULL )
	{
		printf("Renderer could not be created! Error: %s\n",
				SDL_GetError() );
		return 0;
		systemQuit();
	}
	return 1;
}

int initImage()
{
	// Initialize renderer color
	SDL_SetRenderDrawColor( sdlRenderer, 0xFF, 0xFF, 0x00, 0xFF );

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n",
			IMG_GetError() );
		return 0;
		systemQuit();
	}
	return 1;
}

/*
 * Outer variable definitions
 */
// SDL2 window pointer to NULL for error recognition
// Used by window.c
// !! SDL2 pointers: sdl -prefix
SDL_Window* sdlWindow = NULL;
SDL_Renderer* sdlRenderer = NULL;
// Currently displayed texture
SDL_Texture* sdlTexture = NULL;

/*
 * Outer function definitions
 */

// Initialize SDL2, it's subsystems and OpenGL
// Used by game.c
void systemInit()
{
	if( initVideo() )
	{
		if( initWindow() )
		{
			if( initRenderer() )
			{
				initImage();
			}
		}
	}
}

// Quit OpenGl, SDL2 and it's subsystems
// Used by game.c
void systemQuit()
{
	// Free loaded image
	SDL_DestroyTexture( sdlTexture );
	sdlTexture = NULL;

	// Destroy renderer and window
	SDL_DestroyRenderer( sdlRenderer );
	SDL_DestroyWindow( sdlWindow );
	sdlRenderer = NULL;
	sdlWindow = NULL;

	// Quit SDL2 and it's subsystems
	SDL_Quit();
}
