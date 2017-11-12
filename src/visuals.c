/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#include <stdlib.h>
#include "visuals.h"
#include "system.h"

/* Timg
 * 0xf0d85a0f
 *    1111    0000 | 1101 1000 | 0101 1010 | 0000 1111
 * balp><bcol     falp><fcol     4th-  3rd-   2nd- 1st highest line
 *
 * line direction:
 *    0    1    0    1
 * rightmost -> leftmost, so c literal's least significant is origin point
 *                        of tetra: upper left corner
 *
 * Timg info portion
 * 0x00020403
 * 0000 0000 | 0000 0010 | 0000 0100 | 0000 0011
 * frames                  width       height
 *
 * binary conversion example, 8 byte ints
 * hex in c:	0000 0101 ; f0d8 8421
 * hex in file:	0101 0000 ; 2184 d8f0
 *
 * ToneTimg
 * 0xd8
 *   1101 1000
 * alp><color
 */

static const int ALPHA[0x4] = {
	0x00, 0x3d, 0x80, 0xff
};

static const int PALETTER[0xc0] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0xff,
	0x00, 0x60, 0x00, 0x00, 0x60, 0xa0, 0x00, 0x60, 0xff,
	0x00, 0x9c, 0x00, 0x00, 0x9c, 0xa0, 0x00, 0x9c, 0xff,
	0x00, 0xd0, 0x00, 0x00, 0xd0, 0xa0, 0x00, 0xd0, 0xff,
	0x00, 0xff, 0x00, 0x00, 0xff, 0xa0, 0x00, 0xff, 0xff,
	0x3d, 0x3d, 0x3d,
	0x70, 0x00, 0x00, 0x70, 0x00, 0xa0, 0x70, 0x00, 0xff,
	0x70, 0x60, 0x00, 0x70, 0x60, 0xa0, 0x70, 0x60, 0xff,
	0x70, 0x9c, 0x00, 0x70, 0x9c, 0xa0, 0x70, 0x9c, 0xff,
	0x70, 0xd0, 0x00, 0x70, 0xd0, 0xa0, 0x70, 0xd0, 0xff,
	0x70, 0xff, 0x00, 0x70, 0xff, 0xa0, 0x70, 0xff, 0xff,
	0x70, 0x70, 0x70,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0xa0, 0xc0, 0x00, 0xff,
	0xc0, 0x60, 0x00, 0xc0, 0x60, 0xa0, 0xc0, 0x60, 0xff,
	0xc0, 0x9c, 0x00, 0xc0, 0x9c, 0xa0, 0xc0, 0x9c, 0xff,
	0xc0, 0xd0, 0x00, 0xc0, 0xd0, 0xa0, 0xc0, 0xd0, 0xff,
	0xc0, 0xff, 0x00, 0xc0, 0xff, 0xa0, 0xc0, 0xff, 0xff,
	0xa8, 0xa8, 0xa8,
	0xff, 0x00, 0x00, 0xff, 0x00, 0xa0, 0xff, 0x00, 0xff,
	0xff, 0x60, 0x00, 0xff, 0x60, 0xa0, 0xff, 0x60, 0xff,
	0xff, 0x9c, 0x00, 0xff, 0x9c, 0xa0, 0xff, 0x9c, 0xff,
	0xff, 0xd0, 0x00, 0xff, 0xd0, 0xa0, 0xff, 0xd0, 0xff,
	0xff, 0xff, 0x00, 0xff, 0xff, 0xa0, 0xff, 0xff, 0xff,
	0xd7, 0xd7, 0xd7
};

/* Hooks */
void display_tetra_selector(struct Window *wp, int tetra, int xorig,
int yorig)
{
	SDL_Rect rect;
	int fgcol;
	int bgcol;
	int fgcols[0x3];
	int bgcols[0x3];
	int fgalp;
	int bgalp;
	int xgrid;
	int ygrid;
	int cntr;
	rect.w = 0x8;
	rect.h = 0x8;
	fgcol = (tetra >> 0x10 & 0x3f)*0x3;
	bgcol = (tetra >> 0x18 & 0x3f)*0x3;
	fgcols[0] = PALETTER[fgcol];
	fgcols[0x1] = PALETTER[fgcol+0x1];
	fgcols[0x2] = PALETTER[fgcol+0x2];
	bgcols[0] = PALETTER[bgcol];
	bgcols[0x1] = PALETTER[bgcol+0x1];
	bgcols[0x2] = PALETTER[bgcol+0x2];
	fgalp = ALPHA[tetra >> 0x16 & 0x3];
	bgalp = ALPHA[tetra >> 0x1e & 0x3];
	cntr = 0;
	for(ygrid = 0; ygrid < 0x4; ++ygrid) {
		for(xgrid = 0; xgrid < 0x4; ++xgrid) {
			rect.x = xorig+xgrid*0xa;
			rect.y = yorig+ygrid*0xa;
			if((tetra >> cntr) & 0x1)
				SDL_SetRenderDrawColor(wp->renderer,
fgcols[0x0], fgcols[0x1], fgcols[0x2], fgalp);
			else
				SDL_SetRenderDrawColor(wp->renderer,
bgcols[0x0], bgcols[0x1], bgcols[0x2], bgalp);
			SDL_RenderFillRect(wp->renderer, &rect);
			++cntr;
		}
	}
}

void display_alpha_selector(struct Window *wp, int tetra, int xorig,
int yorig)
{
	SDL_Rect rect;
	int fgcol;
	int bgcol;
	int fgcols[0x3];
	int bgcols[0x3];
	int fgalp;
	int bgalp;
	int xgrid;
	int cntr;
	rect.w = 0x8;
	rect.h = 0x8;
	fgcol = (tetra >> 0x10 & 0x3f)*0x3;
	bgcol = (tetra >> 0x18 & 0x3f)*0x3;
	fgcols[0] = PALETTER[fgcol];
	fgcols[0x1] = PALETTER[fgcol+0x1];
	fgcols[0x2] = PALETTER[fgcol+0x2];
	bgcols[0] = PALETTER[bgcol];
	bgcols[0x1] = PALETTER[bgcol+0x1];
	bgcols[0x2] = PALETTER[bgcol+0x2];
	fgalp = tetra >> 0x16 & 0x3;
	bgalp = tetra >> 0x1e & 0x3;
	cntr = 0;
	for(xgrid = 0; xgrid < 0x4; ++xgrid) {
		rect.y = yorig;
		rect.x = xorig+xgrid*0xa;
		SDL_SetRenderDrawColor(wp->renderer, fgcols[0x0], fgcols[0x1],
fgcols[0x2], ALPHA[xgrid]);
		SDL_RenderFillRect(wp->renderer, &rect);
		rect.y = yorig+0xa;
		SDL_SetRenderDrawColor(wp->renderer, bgcols[0x0], bgcols[0x1],
bgcols[0x2], ALPHA[xgrid]);
		SDL_RenderFillRect(wp->renderer, &rect);
		++cntr;
	}
	rect.w = 0xa;
	rect.h = 0xa;
	rect.y = yorig-0x1;
	rect.x = (xorig+fgalp*0xa)-0x1;
	SDL_SetRenderDrawColor(wp->renderer, 0x00, 0xcc, 0xee, 0xff);
	SDL_RenderDrawRect(wp->renderer, &rect);
	rect.y = yorig+0xa-1;
	rect.x = (xorig+bgalp*0xa)-0x1;
	SDL_SetRenderDrawColor(wp->renderer, 0x00, 0xcc, 0xee, 0xff);
	SDL_RenderDrawRect(wp->renderer, &rect);
}

void draw_screen_base(struct Window *wp, int flattone)
{
	int col;
	col = (flattone & 0x3f)*0x3;
	SDL_SetRenderDrawColor(wp->renderer, PALETTER[col], PALETTER[col+0x1],
PALETTER[col+0x2], 0xff);
	SDL_RenderClear(wp->renderer);
}

void draw_rectangle(struct Window *wp, int tone, int width, int height,
int xorig, int yorig)
{
	int col;
	int alp;
	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = xorig;
	rect.y = yorig;
	col = (tone & 0x3f)*0x3;
	alp = ALPHA[tone >> 0x6 & 0x3];
	SDL_SetRenderDrawColor(wp->renderer, PALETTER[col],
PALETTER[col+0x1], PALETTER[col+0x2], alp);
	SDL_RenderFillRect(wp->renderer, &rect);
}

void draw_tetra(struct Window *wp,int tetra, int xorig, int yorig)
{
	int fgcol;
	int bgcol;
	int fgcols[3];
	int bgcols[3];
	int fgalp;
	int bgalp;
	int xgrid;
	int ygrid;
	int cntr;
	fgcol = (tetra >> 0x10 & 0x3f)*0x3;
	bgcol = (tetra >> 0x18 & 0x3f)*0x3;
	fgcols[0] = PALETTER[fgcol];
	fgcols[0x1] = PALETTER[fgcol+0x1];
	fgcols[0x2] = PALETTER[fgcol+0x2];
	bgcols[0] = PALETTER[bgcol];
	bgcols[0x1] = PALETTER[bgcol+0x1];
	bgcols[0x2] = PALETTER[bgcol+0x2];
	fgalp = ALPHA[tetra >> 0x16 & 0x3];
	bgalp = ALPHA[tetra >> 0x1e & 0x3];
	cntr = 0;
	for(ygrid = 0; ygrid < 0x4; ++ygrid) {
		for(xgrid = 0; xgrid < 0x4; ++xgrid) {
			if((tetra >> cntr) & 0x1)
				SDL_SetRenderDrawColor(wp->renderer,
fgcols[0], fgcols[0x1], fgcols[0x2], fgalp);
			else
				SDL_SetRenderDrawColor(wp->renderer,
bgcols[0], bgcols[0x1], bgcols[0x2], bgalp);
			SDL_RenderDrawPoint(wp->renderer, xorig+xgrid,
yorig+ygrid);
			++cntr;
		}
	}
}

void draw_image(struct Window *wp, int *timg, int frame,
int xorig, int yorig)
{
	int height;
	int width;
	int xgrid;
	int ygrid;
	int cntr;
	height = timg[0] & 0xff;
	width = timg[0] >> 0x8 & 0xff;
	cntr = 0;
	for(ygrid = 0; ygrid < height; ++ygrid) {
		for(xgrid = 0; xgrid < width; ++xgrid) {
			draw_tetra(wp, timg[0x1+cntr+height*width*frame],
xorig+xgrid*0x4, yorig+ygrid*0x4);
			++cntr;
		}
	}
}

void draw_texture(struct Window *wp, int *timg, int frame,
int xsize, int ysize, int xorig, int yorig)
{
	int height;
	int width;
	int xgrid;
	int ygrid;
	height = (timg[0] & 0xff)*0x4;
	width = (timg[0] >> 0x8 & 0xff)*0x4;
	for(ygrid = 0; ygrid < ysize; ++ygrid) {
		for(xgrid = 0; xgrid < xsize; ++xgrid) {
			draw_image(wp, timg, frame, xorig+xgrid*width,
yorig+ygrid*height);
		}
	}
}

void update_screen(void)
{
	SDL_RenderPresent(windows->renderer);
}
