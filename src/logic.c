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

void fetch_input()
{
	SDL_Event event;
	SDL_GetMouseState(&state.xcursor, &state.ycursor);
	state.clicked = 0;
	if(key != K_NONE)
		prevKey = key;
	key = K_NONE;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT)
			mode = QUIT;
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
			case SDLK_ESCAPE :
				mode = QUIT;
				break;
			case SDLK_RETURN :
				key = K_RETURN;
				break;
			case SDLK_SPACE :
				key = K_SPACE;
				break;
			case SDLK_LEFT :
				key = K_LEFT;
				break;
			case SDLK_UP :
				key = K_UP;
				break;
			case SDLK_RIGHT :
				key = K_RIGHT;
				break;
			case SDLK_DOWN :
				key = K_DOWN;
				break;
			case SDLK_q :
				key = K_Q;
				break;
			case SDLK_f :
				key = K_F;
				break;
			case SDLK_b :
				key = K_B;
				break;
			case SDLK_m :
				key = K_M;
				break;
			case SDLK_c :
				key = K_C;
				break;
			case SDLK_a :
				key = K_A;
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


/*static void print_reference_palette(void)
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
*/

/*static void manage_mouse_menu(int *curTetra, int *futTetra)
{
	int x;
	int y;
	x = state.xcursor;
	y = state.ycursor;
	if((x > 0x10 && x < 0x18) && (y > 0x18 && y < 0x20)) {
		*curTetra = *curTetra ^ 0x1;
	} else if(x > 0x50 && x < 0x58) {
		*futTetra = *futTetra ^ 0x1;
	}
}
*/

static void key_input(void)
{
	if(mode == NORMAL) {
		switch(key) {
		case K_SPACE :
			state.tetraField[state.xtetra/0x4][state.ytetra/0x4] =
state.futTetra;
			break;
		case K_LEFT :
			if(state.xtetra > 0)
				state.xtetra -= 0x4;
			break;
		case K_UP :
			if(state.ytetra > 0x40)
				state.ytetra -= 0x4;
			break;
		case K_RIGHT :
			if(state.xtetra < 0x434)
				state.xtetra += 0x4;
			break;
		case K_DOWN :
			if(state.ytetra < 0x2cc)
				state.ytetra += 0x4;
			break;
		case K_M :
			if(prevKey == K_F)
				mode = FGM_MENU;
			if(prevKey == K_B)
				mode = BGM_MENU;
			break;
		case K_C :
			if(prevKey == K_F)
				mode = FGC_MENU;
			if(prevKey == K_B)
				mode = BGC_MENU;
			break;
		case K_A :
			if(prevKey == K_F)
				mode = FGA_MENU;
			if(prevKey == K_B)
				mode = BGA_MENU;
			break;
		default:
			break;
		}
	} else if(mode == FGM_MENU) {
		switch(key) {
		case K_SPACE :
			state.tetraField[state.xtetra/0x4][state.ytetra/0x4] =
state.futTetra;
			break;
		case K_LEFT :
			if(state.xtetra > 0)
				state.xtetra -= 0x4;
			break;
		case K_UP :
			if(state.ytetra > 0x40)
				state.ytetra -= 0x4;
			break;
		case K_RIGHT :
			if(state.xtetra < 0x434)
				state.xtetra += 0x4;
			break;
		case K_DOWN :
			if(state.ytetra < 0x2cc)
				state.ytetra += 0x4;
			break;
		case K_Q :
			mode = NORMAL;
			break;
		default:
			break;
		}
	} else if(mode == BGM_MENU) {
	} else if(mode == FGC_MENU) {
	} else if(mode == BGC_MENU) {
	} else if(mode == FGA_MENU) {
	} else if(mode == BGA_MENU) {
	}
}

/* Hooks */
void run_loop(void)
{
	struct Window mainWin;
	int plainCursor[0x5];
	int pinCursor[0xa];
	int xtetFcntr;
	int ytetFcntr;
	mainWin = windows[0];
	state.curTetra = 0xc0c30000;
	state.futTetra = 0xc5cd0000;
	fetch_file("include/visual/plain_cursor.timg", plainCursor,
sizeof(plainCursor));
	fetch_file("include/visual/pin_cursor.timg", pinCursor,
sizeof(pinCursor));
	state.xcursor = 0;
	state.ycursor = 0;
	state.xtetra = 0;
	state.ytetra = 0x40;
	key = K_NONE;
	prevKey = K_NONE;
	mode = NORMAL;
	while(mode != QUIT) {
		SDL_Delay(0x32);
		fetch_input();
		draw_screen_base(&mainWin, 0x3a);
		draw_rectangle(&mainWin, 0xbf, 0x438, 0x40, 0, 0);
		draw_rectangle(&mainWin, 0xfe, 0x438, 0x290, 0, 0x40);
		display_tetra_selector(&mainWin, state.curTetra, 0x10, 0x18);
		display_tetra_selector(&mainWin, state.futTetra, 0x50, 0x18);
		display_alpha_selector(&mainWin, state.curTetra, 0x10, 0x1);
		display_alpha_selector(&mainWin, state.futTetra, 0x50, 0x1);
		display_palette_selectors(&mainWin, 0x100, 0x100);
		if(state.clicked && state.ycursor > 0x40) {
			int x = state.xcursor/4;
			int y = state.ycursor/4;
			state.tetraField[x][y] = state.futTetra;
		} else if(key != K_NONE) {
			key_input();
		}
		for(ytetFcntr = 0; ytetFcntr < 0x10e; ++ytetFcntr) {
			for(xtetFcntr = 0; xtetFcntr < 0xa4; ++xtetFcntr) {
				if(state.tetraField[xtetFcntr][ytetFcntr])
					draw_tetra(&mainWin,
state.tetraField[xtetFcntr][ytetFcntr], xtetFcntr*0x4, ytetFcntr*0x4);
			}
		}
		draw_image(&mainWin, plainCursor, 0, state.xcursor,
state.ycursor);
		draw_image(&mainWin, pinCursor, 0, state.xtetra-0x4,
state.ytetra-0x4);
		update_screen();
	}
}
