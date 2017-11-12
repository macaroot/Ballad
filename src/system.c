/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#include "system.h"
#include "visuals.h"
#include "state.h"

static int init_modules()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		goto fail;
	state.videoCreated = 1;
	return 1;
fail:
	printf("SDL could not be initialized! SDL_Error: %s\n",
SDL_GetError());
	return 0;
}

static void init_window(struct Window **p)
{
	int c;
	c = state.windowCount;
	if(c == 0)
		*p = malloc(sizeof(struct Window));
	else
		*p = realloc(*p, (c+1)*sizeof(struct Window));
	p[c]->context = 0;
	p[c]->renderer = 0;
	p[c]->contextCreated = 0;
	p[c]->rendererCreated = 0;
	p[c]->width = 0x438;
	p[c]->height = 0x2d0;
	++state.windowCount;
}

static int init_window_context(struct Window **p)
{
	int c;
	c = state.windowCount-1;
	p[c]->context = SDL_CreateWindow("Ballad", SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED, p[c]->width, p[c]->height, SDL_WINDOW_SHOWN);
	if(!p[c]->context)
		goto fail;
	p[c]->contextCreated = 1;
	return 1;
fail:
	printf("SDL could not create window! SDL_Error: %s\n",
SDL_GetError());
	return 0;
}

static int init_window_renderer(struct Window **p)
{
	int c;
	c = state.windowCount-1;
	p[c]->renderer = SDL_CreateRenderer(p[c]->context, -1,
SDL_RENDERER_ACCELERATED);
	if(!p[c]->renderer)
		goto fail;
	p[c]->rendererCreated = 1;
	return 1;
fail:
	printf("SDL could not create renderer! SDL_Error: %s\n",
SDL_GetError());
	return 0;
}

static int init_window_blend(struct Window **p)
{
	int c;
	c = state.windowCount-1;
	if(SDL_SetRenderDrawBlendMode(p[c]->renderer, SDL_BLENDMODE_BLEND) !=
0)
		goto fail;
	return 1;
fail:
	printf("SDL could not enable blend mode! SDL_Error: %s\n",
SDL_GetError());
	return 0;
}

static int generate_window(struct Window **p)
{
	init_window(p);
	if(!init_window_context(p))
		goto fail;
	if(!init_window_renderer(p))
		goto fail;
	if(!init_window_blend(p))
		goto fail;
	return 1;
fail:
	return 0;
}

static int start_visuals(void)
{
	state.videoCreated = 0;
	state.windowCount = 0;
	if(!init_modules())
		goto fail;
	if(!generate_window(&windows))
		goto fail;
	SDL_ShowCursor(SDL_DISABLE);
	return 1;
fail:
	return 0;
}

static void stop_visuals(void)
{
	int i;
	for(i = 0; i < state.windowCount; ++i) {
		if(windows[i].rendererCreated) {
			SDL_DestroyRenderer(windows[i].renderer);
			windows[i].renderer = 0;
		}
		if(windows[i].contextCreated) {
			SDL_DestroyWindow(windows[i].context);
			windows[i].context = 0;
		}
	}
	if(state.videoCreated)
		SDL_Quit();
	if(state.windowCount != 0)
		free(windows);
}

/* Hooks */
int begin_system(void)
{
	if(!start_visuals())
		goto fail;
	return 1;
fail:
	return 0;
}

int terminate_system(void)
{
	stop_visuals();
	if(0)
		goto fail;
	return 1;
fail:
	return 0;
}
