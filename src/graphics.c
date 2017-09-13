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
#include "graphics.h"
#include "main.h"
#include "logic.h"
#include "data.h"

/*****************************************************************************
 * Getsetted variables                                                       *
 *****************************************************************************/


/*****************************************************************************
 * Local variables                                                           *
 *****************************************************************************/

const int PALETTE[2][16] =
/*{{{*//*{{{*//*
 * - Predefined palettes, all of the colors are from here.
 * - Two dimensional array, [16][16] is the largest possible due to the nature
 *   of imagedata
 *//*}}}*/
{
	{
		0x002B36, 0x073642, 0x586E75, 0x657B83,
		0x839496, 0x93A1A1, 0xEEE8D5, 0xFDF6E3,
		0xB58900, 0xCB4B16, 0xDC322F, 0xD33682,
		0x6C71C4, 0x268BD2, 0x2AA198, 0x859900
	},
	{	0x002B36, 0x073642, 0x586E75, 0x657B83,
		0x839496, 0x93A1A1, 0xEEE8D5, 0xFDF6E3,
		0xB58900, 0xCB4B16, 0xDC322F, 0xD33682,
		0x6C71C4, 0x268BD2, 0x2AA198, 0x859900
	}
};/*}}}*/

/*****************************************************************************
 * Getset definitions                                                        *
 *****************************************************************************/


/*****************************************************************************
 * Local                                                                     *
 *****************************************************************************/

/* Get just the color of a screen, currently hardcoded to canRegular */
int* ipGetScreenColor( void )
/*{{{*//*{{{*//*
 * - Get 3 byte color from palette. Uses color index from screen data
 * - Calc alpha from screen data. Flag only uses lower halfbyte
 * - return address of array: [0]color index, [1]palette color, [2]alpha
 *//*}}}*/
{
	static int rgbaArray[4];
	rgbaArray[1] = ( screenRegular[0] >> 0x4 ) & 0xF;
	rgbaArray[0] = PALETTE[ rgbaArray[1] ][ ( screenRegular[0] & 0xF ) ];
	rgbaArray[2] = ( ( ( screenRegular[0] >> 0x8 ) & 0x3 ) |
        ( ( ( screenRegular[0] >> 0x8 ) & 0x3 ) << 0x2 ) ) |
        ( ( ( ( screenRegular[0] >> 0x8 ) & 0x3 ) |
        ( ( ( screenRegular[0] >> 0x8 ) & 0x3 ) << 0x2 ) ) << 0x4 );
	return rgbaArray;
}/*}}}*/

/* Get image data by passing ptr to imagedata array running one through this
 * is all that's needed to draw a full image */
int* ipGetImageData( int** ptrToStream, int* image )
/*{{{*//*{{{*//*
 * - Get address of image array, skipping the info element and place it inside
 *   tetraStream
 * - return address of array: [0]length of image array, [1]x width of image,
 *   [2]y height of image
 *//*}}}*/
{
	static int infoArray[3];
	*ptrToStream = &image[1];
	infoArray[1] = image[0] & 0xFFFF;
	infoArray[2] = ( image[0] >> 0x10 ) & 0xFFFF;
	infoArray[0] = infoArray[1] * infoArray[2];
	return infoArray;
}/*}}}*/

/* Modifying whole image with modus */
void applyModus( int* tetra, int currentImageIndex, int flags, int flux )
/*{{{*//*{{{*/
/* - Modus are modifications of the image. They consist of two ints, flag and
 *   flux, flag activates different modus and flux modifies them. There will be
 *   overlap between modus' fluxes. Constructions:
 *   &0x1 alpha flag
 *   &0xF alpha flux
 * - (Conforming) alpha -modus. The first ANDing line makes it so that the flux
 *   doesn't just replace tetra's alpha portion, instead it never makes things
 *   more opaque than the original. This preserves outlines made with alpha.
 *//*}}}*/
{
	if( flags & 0x1 )
	{
		flux = *tetra & ( flux << 0x1C );
		*tetra = *tetra ^ ( ( *tetra ^ flux ) & 0xF0000000 );
	}
}/*}}}*/

/* Draw a single tetra. The more independent this is, the better */
void drawTetra( int tetraData, int drawOrigin[], int cntrTetra,
                int cntrImageWidth, int cntrImageHeight )
/*{{{*//*{{{*//*
 * - Go through tetra from left upper corner to bottom right, drawing each
 *   individual tetpix
 * TODO figure efficient way to skip fully transparent tetras
 * - First draw upper line from left to right, then go to next line
 * - Use different halfbyte depending on whether current pixel is fg or bg
 *   First halfbyte of data's 4th byte to enter palette and FIRST halfbyte of
 *   data's 3rd byte to get index of foreground color Retrieves 3 byte color
 * - First halfbyte of data's 4th byte to enter palette and SECOND halfbyte
 *   of data's 3rd byte to get index of background color
 * - Places 3 byte color in col
 * - Get 3rd, 2nd & 1st bytes of color for r, g & b
 * - Draw single tetpix, which is an actual pixel, PIXEL would be assumed 1
 * - Inc to next column
 * - Going to explain this alpha monstrosity here: Two bits (different two if
 *   fg or bg) are duplicated twice with bitfiddling, so that no check needs
 *   to be made to determine alpha, you can just CRUNCH it and correct numbers
 *   for alpha levels are always achieved. 0x00, 0x55, 0xAA or 0xFF.
 *   Example: 0110 10'01' -> 0000 0001 -> 0000 0101 -> 0101 0101.
 *   If we call 0000 0001 a, then (a | (a<<2)) | ((a | (a<<2))<<4)
 *   Maybe at some point I'll find this is really slow, but for now it's fun.
 *//*}}}*/
{
	int cntrTetpix;
	int cntrTetpixColumn = 0;
	int cntrTetpixRow = 0;
	for( cntrTetpix = 0; cntrTetpix < 16; cntrTetpix++ )
	{
		int color; int alpha;
		if( cntrTetpixColumn > 3 )
		{
			cntrTetpixColumn = 0;
			cntrTetpixRow++;
		}
		if( tetraData & ( 1 << cntrTetpix ) )
		{
			color = PALETTE
                        [ ( tetraData >> 0x18 ) & 0xF ]
                        [ ( tetraData >> 0x10 ) & 0xF ];
			alpha =
                        ( ( ( tetraData >> 0x1C ) & 0x3 ) |
                        ( ( ( tetraData >> 0x1C ) & 0x3 ) << 0x2 ) ) |
                        ( ( ( ( tetraData >> 0x1C ) & 0x3 ) |
                        ( ( ( tetraData >> 0x1C ) & 0x3 ) << 0x2 ) ) << 0x4 );
		}
		else
		{
			color = PALETTE
                        [ ( tetraData >> 0x18 ) & 0xF ]
                        [ ( tetraData >> 0x14 ) & 0xF ];
			alpha =
                        ( ( ( tetraData >> 0x1E ) & 0x3 ) |
                        ( ( ( tetraData >> 0x1E ) & 0x3 ) << 0x2 ) ) |
                        ( ( ( ( tetraData >> 0x1E ) & 0x3 ) |
                        ( ( ( tetraData >> 0x1E ) & 0x3 ) << 0x2 ) ) << 0x4 );
		}
		SDL_SetRenderDrawColor( window_getRenderer(
                window_getPointer() ),
                ( color >> 0x10 ) & 0xFF,
                ( color >> 0x8 ) & 0xFF,
                color & 0xFF,
                alpha );
		SDL_RenderDrawPoint( window_getRenderer( window_getPointer() ),
                drawOrigin[0] + ( cntrImageWidth * 4 ) + cntrTetpixColumn,
                drawOrigin[1] + ( cntrImageHeight * 4 ) + cntrTetpixRow );
		cntrTetpixColumn++;
	}
}/*}}}*/

/* Draw the image */
void drawImage( int currentImageIndex )
/*{{{*//*{{{*//*
 * - Fetch image info and data imageData points to array: [0]length of image
 *   array, [1]x width of image, [2]y height of image ptr to image can't be
 *   returned with rest of array, so returned through ptr to tetraStream *(
 *   tetraStream + X ) is used to get the value of element out of the original
 *   image array
 * - Go through all the tetras in an image
 * - Tetra counters, which also get inserted to drawTetra
 * - Go through modus changes if flag isn't empty
 * - Draw tetra only if alpha isn't 0
 * - Drawing finished once counter caps full tetra amount
 * - Go to new tetra row if width counter touches real width (from image info)
 * - If alls good, height getting capped should coincide with tetra amount for
 *   main loop, not that there's any checks or anything...
 *//*}}}*/
{
	int* drawOrigin;
	int* tetraStream;
	int* imageData;
	int singleTetra;
	int modusFlags;
	int modusFlux;
	int cntrTetra;
	int cntrImageWidth;
	int cntrImageHeight;
	spriteList_getPosition( spriteList_getPointer(),
        currentImageIndex, &drawOrigin );
	imageData = ipGetImageData( &tetraStream,
        spriteList_getGraphic( spriteList_getPointer(), currentImageIndex ) );
	modusFlags = spriteList_getModusFlags( spriteList_getPointer(),
        currentImageIndex );
	modusFlux = spriteList_getModusFlux( spriteList_getPointer(),
        currentImageIndex );
	cntrTetra = 0;
	cntrImageWidth = 0;
	cntrImageHeight = 0;
	for( cntrTetra = 0; cntrTetra < *( imageData ); cntrTetra++ )
	{
		if( cntrImageWidth == *( imageData + 1 ) )
		{
			cntrImageWidth =
			0; cntrImageHeight++;
		}
		if( cntrImageHeight < *( imageData + 2 ) )
		{
			singleTetra = *( tetraStream + cntrTetra );
			if( modusFlags )
			{
				applyModus( &singleTetra,
                                currentImageIndex, modusFlags, modusFlux );
			}
			if( singleTetra & 0xF0000000 )
			{
				drawTetra( singleTetra, drawOrigin, cntrTetra,
                                cntrImageWidth, cntrImageHeight );
			}
			cntrImageWidth++;
		}
	}
}/*}}}*/

/* Draw to the screen */
void vDrawScreen( void )
/*{{{*//*{{{*//*
 * - Set screen color. Screencolor points to array: [0]color index,
 *   [1]palette color, [2]alpha
 * - Clear screen
 * - Execute image drawing. Currently segfaults if goes over 1
 * TODO figure safe way to walk sSprites[]
 * - Update the surface
 *//*}}}*/
{
	int cntrSprites;
	int* screenColor = ipGetScreenColor();
	SDL_SetRenderDrawColor( window_getRenderer( window_getPointer() ),
        ( *( screenColor + 0 ) >> 0x10 ) & 0xFF,
        ( *( screenColor + 0 ) >> 0x8 ) & 0xFF,
        *( screenColor + 0 ) & 0xFF,
        *( screenColor + 2 ) );
	SDL_RenderClear( window_getRenderer( window_getPointer() ));
	for( cntrSprites = 0; cntrSprites < 2; cntrSprites++ )
	{
		drawImage( cntrSprites );
	}
	SDL_RenderPresent( window_getRenderer( window_getPointer() ) );
}/*}}}*/
