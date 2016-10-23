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
#include "system.h"
#include "window.h"

/*
 * Inner variable initialization
 */
// SDL2 surface pointer to NULL for error recognition
SDL_Surface* sdlSurface = NULL;
// OpenGL context handle to NULL for error recognition
SDL_GLContext glContext = NULL;

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

int initOpengl()
{
    // Tie GL context to the window
    glContext = SDL_GL_CreateContext( sdlWindow );
    if( glContext == NULL )
    {
        printf("SDL_GL context could not be created! Error: %s\n",
                SDL_GetError() );
        return 0;
        systemQuit();
    }
    else
    {
        // Initialize Glew
        GLenum error = glewInit();
        if( error != GLEW_OK )
        {
            printf("Glew could not be initialized! Error: %s\n",
                    SDL_GetError() );
            return 0;
            systemQuit();
        }
        // Setup window attributes
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

        // Clear color to cyan
        glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );
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
            initOpengl();
        }
    }
}

// Quit OpenGl, SDL2 and it's subsystems
// Used by game.c
void systemQuit()
{
    // Delete OpenGL context
    SDL_GL_DeleteContext( glContext );

    // Destroy window
    SDL_DestroyWindow( sdlWindow );

    // Quit SDL2 and it's subsystems
    SDL_Quit();
}
