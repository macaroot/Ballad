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
#include "window.h"
#include "system.h"
/*
 * Innver variable initializations
 */
// SDL2 image to texture converter
extern SDL_Texture* sdlLoadTexture( char* path );

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
// Get the image for texture
SDL_Texture* sdlLoadTexture( char* path )
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n",
                path, SDL_GetError() );
    }
    else
    {
        // Convert texture from surface to pixels
        newTexture = SDL_CreateTextureFromSurface(
                sdlRenderer,
                loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n",
                    path, SDL_GetError() );
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

// Load media
int loadMedia()
{
    sdlTexture = sdlLoadTexture( "include/visual/blaBox.png" );
    if( sdlTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return 0;
        systemQuit();
    }
    return 1;
};

// Draw to the screen
// Used by game.c
void drawScreen()
{
    SDL_RenderClear( sdlRenderer );

    // Render texture to screen
    SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, NULL );

    // Update the surface
    SDL_RenderPresent( sdlRenderer );
}
