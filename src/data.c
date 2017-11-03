/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
/*	SDL2 includes */
#include <SDL.h>
/*	Standard C includes */
#include <stdio.h>
/*	.h includes */
#include "data.h"

/*****************************************************************************
 * Makeshift image data collection                                           *
 *****************************************************************************/

/*{{{*//*
 * 4 bytes to define a single 4x4 grid. Example:
 * F0D85A0F =
 * 1111 0000 | 1101 1000 | 0101 1010 | 0000 1111
 * alp. pal.   bg   fg     4th- 3rd-   2nd- 1st line,
 * Left side of row is right side of that binary presentation.
 * Alpha byte is a flagbyte, which is converted to 4 levels of alpha for
 * both fg and bg
 * Corresponding alpha levels    Alp=0x00  Alp=0x55  Alp=0xaa  Alp=0xff
 * Foreground alpha only       = 0 (0000), 1 (0001), 2 (0010), 3 (0011)
 * Background alpha only       = 0 (0000), 4 (0100), 8 (1000), C (1100)
 * Both same alpha             = 0 (0000), 5 (0101), A (1010), F (1111)
 *
 * First element of image array has some image info.
 * Example:
 * 00020002 =
 * 0000 0000 | 0000 0002 | 0000 0000 | 0000 0002
 * Amount of grids in y-   Amount of grids in x direcion. Currently really empty
 *//*}}}*/
int imgCursor[10];
int imgSquare[2];
/* Screen color info: alpha, palette index, color index */
int screenRegular[1];

void vReadFiles()
{
	FILE* filePointer;
	filePointer = fopen( "../include/visual/cursor.tetimg", "rb" );
	fread( imgCursor, sizeof( imgCursor ), 1, filePointer );
	fclose( filePointer );
	filePointer = fopen( "../include/visual/square.tetimg", "rb" );
	fread( imgSquare, sizeof( imgSquare ), 1, filePointer );
	fclose( filePointer );
	filePointer = fopen( "../include/visual/regular.tetscrn", "rb" );
	fread( screenRegular, sizeof( screenRegular ), 1, filePointer );
	fclose( filePointer );
}
