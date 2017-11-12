/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#include <stdio.h>
#include "system.h"
#include "state.h"
#include "visuals.h"

static void fetch_file(char *path, int img[], size_t size)
{
	FILE *fp;
	fp = fopen(path, "rb");
	if(!fp) {
		printf("Couldn't open file\n");
		goto fail;
	}
	fread(img, size, 1, fp);
	fclose(fp);
fail:{}
}

void manage_input()
{
	SDL_Event event;
	SDL_GetMouseState(&state.xcursor, &state.ycursor);
	state.clicked = 0;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT)
			mode = QUIT;
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
			case SDLK_ESCAPE :
				mode = QUIT;
				break;
			default:
				return;
			}
		}
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			state.clicked = 1;
		}
	}
}

static void print_reference_palette(void)
{
	int temp;
	int xgrid;
	int ygrid;
	int cntr;
	for(ygrid = 0; ygrid < 0x4; ++ygrid) {
		for(xgrid = 0; xgrid < 0x10; ++xgrid) {
			temp = 0xc0+cntr;
			draw_rectangle(&windows[0], temp, 0x28, 0x28,
xgrid*0x28, ygrid*0x28);
			++cntr;
		}
	}
}

/* Hooks */
void run_loop(void)
{
	struct Window mainWin;
	int cursor[0x5];
	int tetras[0x10e][0xa4] = {0};
	int curTetra;
	int futTetra;
	int xtetras;
	int ytetras;
	mainWin = windows[0];
	curTetra = 0xc0c00000;
	futTetra = 0xc5c50000;
	fetch_file("include/visual/test.timg", cursor, sizeof(cursor));
	mode = PLAY;
	while(mode != QUIT) {
		SDL_Delay(0x64);
		manage_input();
		draw_screen_base(&mainWin, 0x3a);
		draw_rectangle(&mainWin, 0xbf, 0x438, 0x40, 0, 0);
		draw_rectangle(&mainWin, 0xfe, 0x438, 0x290, 0, 0x40);
		display_tetra_selector(&mainWin, curTetra, 0x10, 0x18);
		display_tetra_selector(&mainWin, futTetra, 0x50, 0x18);
		display_alpha_selector(&mainWin, curTetra, 0x10, 0x1);
		display_alpha_selector(&mainWin, futTetra, 0x50, 0x1);
		if(state.clicked && state.ycursor > 0x40) {
			int x = state.xcursor/4;
			int y = state.ycursor/4;
			tetras[x][y] = futTetra;
		}
		for(ytetras = 0; ytetras < 0x10e; ++ytetras) {
			for(xtetras = 0; xtetras < 0xa4; ++xtetras) {
				if(tetras[xtetras][ytetras])
					draw_tetra(&mainWin,
tetras[xtetras][ytetras], xtetras*0x4, ytetras*0x4);
			}
		}
		draw_image(&mainWin, cursor, 0, state.xcursor,
state.ycursor);
		update_screen();
	}
}
