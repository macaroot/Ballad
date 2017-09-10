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
 * Corresponding alpha levels    Alp=0x00  Alp=0x55  Alp=0xAA  Alp=0xFF
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
int imgCursor[] = {
	0x00030003,
	0xF08E111F, 0x308EF731, 0x008E0000,
	0x308E8CEF, 0xF08EA5A5, 0x308E3100,
	0x008E0000, 0x308E008C, 0x308E0033
};
int imgSquare[] = {
	0x00010001,
	0xF0A5A5A5
};
/* Screen color info: alpha, palette index, color index */
int screenRegular[] = { 0xF07 };
