/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#ifndef VISUALS_H
#define VISUALS_H
#include <SDL.h>

struct Window {
	SDL_Window *context;
	SDL_Renderer *renderer;
	int contextCreated;
	int rendererCreated;
	int width;
	int height;
} *windows;

void display_tetra_selector(struct Window *wp, int tetra, int xorig,
int yorig);
void display_alpha_selector(struct Window *wp, int tetra, int xorig,
int yorig);
void draw_screen_base(struct Window *wp, int flattone);
void draw_rectangle(struct Window *wp, int tone, int width, int height,
int xorig, int yorig);
void draw_tetra(struct Window *wp,int tetra, int xorig, int yorig);
void draw_image(struct Window *wp, int *timg, int frame, int xorig,
int yorig);
void draw_texture(struct Window *wp, int *timg, int frame, int xsize,
int ysize, int xorig, int yorig);
void update_screen(void);

#endif
