/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 */
#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
/*
 * Variable declarations
 */
// SDL2 window pointer
// Used by window.c
// !! SDL2 pointers: sdl -prefix
extern SDL_Window* sdlWindow;

/*
 * Function declarations
 */
// Initialize SDL2, it's subsystems and OpenGL
// Used by game.c
extern void systemInit();

// Quit OpenGL, SDL2 and it's subsystems
// Used by game.c
extern void systemQuit();

#endif
