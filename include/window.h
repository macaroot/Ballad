/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 */
#pragma once
#ifndef WINDOW_H
#define WINDOW_H
/*
 * Variable declarations
 */
// Screen dimension constants
// Used by system.c
// !! Constants: all caps with underscores
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

/*
 * Function declarations
 */
// Draw to the screen
// Used by game.c
extern void drawScreen();

#endif

