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
#include "main.h"
#include "logic.h"

/*****************************************************************************
 * Getsetted variables                                                       *
 *****************************************************************************/

/* Struct for holding all the data concerning a window */
struct sWindowEntity
/*{{{*/
{
	void* pointer;
	int width;
	int height;
	int tetraRow;
	int tetraColumn;
	int tetpixSize;
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
};/*}}}*/

/*****************************************************************************
 * Local variables                                                           *
 *****************************************************************************/

WINDOW windowMain;

/*****************************************************************************
 * Getset definitions                                                        *
 *****************************************************************************/

WINDOW* window_create( void )
/*{{{*/
{
	return malloc( sizeof( WINDOW ) );
}
void window_free( WINDOW* p )
{
	free( p );
}
void* window_getPointer( void )
{
	return windowMain.pointer;
}
void window_setPointer( WINDOW* p )
{
	p->pointer = p;
}
int window_getWidth( WINDOW* p )
{
	return p->width;
}
void window_setWidth( WINDOW* p, int newInt )
{
	p->width = newInt;
}
int window_getHeight( WINDOW* p )
{
	return p->height;
}
void window_setHeight( WINDOW* p, int newInt )
{
	p->height = newInt;
}
int window_getTetraRow( WINDOW* p )
{
	return p->tetraRow;
}
void window_setTetraRow( WINDOW* p, int newInt )
{
	p->tetraRow = newInt;
}
int window_getTetraColumn( WINDOW* p )
{
	return p->tetraColumn;
}
void window_setTetraColumn( WINDOW* p, int newInt )
{
	p->tetraColumn = newInt;
}
int window_getTetpixSize( WINDOW* p )
{
	return p->tetpixSize;
}
void window_setTetpixSize( WINDOW* p, int newInt )
{
	p->tetpixSize = newInt;
}
void* window_getContext( WINDOW* p )
{
	return p->sdlWindow;
}
void window_setContext( WINDOW* p, SDL_Window* newSDLptr )
{
	p->sdlWindow = newSDLptr;
}
void* window_getRenderer( WINDOW* p )
{
	return p->sdlRenderer;
}
void window_setRenderer( WINDOW* p, SDL_Renderer* newSDLptr )
{
	p->sdlRenderer = newSDLptr;
}/*}}}*/

/*****************************************************************************
 * Local                                                                     *
 *****************************************************************************/

/* Initialize values for window */
void window_generate( WINDOW* p )
/*{{{*//*{{{*//*
 * - Screen dimensions
 * - Temporary consts for amount of tetras needed to fill 1080x720 with tetpix
 *   size = 1 so tetra size is 4. 1080/4=270, 720/4=180
 * - Size of rectangels used to draw everything, effectively the resolution.
 *   Currently used just to offset tetpix at draw phase when using
 *   SDL_RenderFillRect()
 *//*}}}*/
{
	window_setPointer( p );
	window_setWidth( p, 1080 );
	window_setHeight( p, 720 );
	window_setTetraRow( p, 270 );
	window_setTetraColumn( p, 180 );
	window_setTetpixSize( p, 1 );
	window_setContext( p, NULL );
	window_setRenderer( p, NULL );
}/*}}}*/

/* Quit SDL2 and it's subsystems */
void vSystemQuit( void )
/*{{{*//*{{{*//*
 * - Destroy renderer and window
 * - Quit SDL2 and it's subsystems
 *//*}}}*/
{
	SDL_DestroyRenderer( window_getRenderer( &windowMain ) );
	SDL_DestroyWindow( window_getContext( &windowMain ) );
	window_setContext( &windowMain, NULL );
	window_setRenderer( &windowMain, NULL );
	SDL_Quit();
}/*}}}*/

/* Initialize SDL2 */
int iInitVideo( void )
/*{{{*/
{
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		printf( "SDL could not be initialized! SDL_Error: %s\n",
                SDL_GetError() );
		return 0;
		vSystemQuit();
	}
	return 1;
}/*}}}*/

/* Get a pointer to SDL2 window */
int iInitWindow( void )
/*{{{*/
{
	window_setContext(
        &windowMain,
        SDL_CreateWindow( "Ballad", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, window_getWidth( &windowMain ),
        window_getHeight( &windowMain ), SDL_WINDOW_SHOWN ) );
	if( window_getContext( &windowMain ) == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n",
                SDL_GetError() );
		return 0;
		vSystemQuit();
	}
	return 1;
}/*}}}*/

/* Create context for SDL2 renderer */
int iInitRenderer( void )
/*{{{*/
{
	window_setRenderer(
        &windowMain,
        SDL_CreateRenderer( window_getContext( &windowMain ), -1,
        SDL_RENDERER_ACCELERATED ) );
	if( window_getRenderer( &windowMain ) == NULL )
	{
		printf("Renderer could not be created! SDL_Error: %s\n",
                SDL_GetError() );
		return 0;
		vSystemQuit();
	}
	return 1;
}/*}}}*/

/* Enables Alpha blending */
int iInitBlend( void )
/*{{{*/
{
	if( SDL_SetRenderDrawBlendMode( window_getRenderer( &windowMain ),
        SDL_BLENDMODE_BLEND ) != 0 )
	{
		printf( "Blend mode could not be enabled! SDL_Error: %s\n",
                SDL_GetError() );
		return 0;
		vSystemQuit();
	}
	return 1;
}/*}}}*/

/* Nested initialization */
void vSystemInit( void )
/*{{{*/
{
	window_generate( &windowMain );
	if( iInitVideo() )
	{
		if( iInitWindow() )
		{
			if( iInitRenderer() )
			{
				iInitBlend();
				/* Hide OS cursor */
				SDL_ShowCursor(SDL_DISABLE);
			}
		}
	}
}/*}}}*/

/* Everything divided in three: initialization, loop and exiting */
void vRunGame( void )
/*{{{*/
{
	vSystemInit();
	vTheLoop();
	vSystemQuit();
}/*}}}*/

/* Main */
int main( int argc, char* argv[] )
/*{{{*/
{
	vRunGame();
	return 0;
}/*}}}*/

/*{{{*//* Debug printfs */
/* printf( "xRef:%d	yRef:%d",xRefPos,yRefPos ); printf( "%d
 * %d	%d	%d	%d\n",  xSizecntr, xSizeLimit, ySizecntr, ySizeLimit, i
 * ); printf( "draw x:%d	y:%d	xDev:%d	yDev:%d\n", xRefPos + (
 * xSizecntr * 4 * PIXEL ) + ( xDev * PIXEL ),yRefPos + ( ySizecntr * 4 * PIXEL
 * ) + ( yDev * PIXEL ), xDev, yDev  ); printf("s0:%04x	s1:%04x
 * s2:%04x\n",(*(screenColor)&0xff),((*(screenColor+1)>>8)&0xff),
 * ((*(screenColor +2)>>16)&0xff)); printf("0:%04x	1:%04x
 * 2:%04x\n",rgbaArray[0],rgbaArray[1], rgbaArray[2]); printf( "int: %ld
 * uint: %ld\n", sizeof( int ), sizeof( unsigned ) );
 *//*}}}*/
