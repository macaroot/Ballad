/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 */
#pragma once
#ifndef GAME_H
#define GAME_H
/*
 * Variable declarations
 */
// Track game state
// Used by input.c, loop.c
typedef enum eGameState
{
	QUIT,
	PLAY
} eGameState;
extern eGameState eCurrentState;

/*
 * Function declarations
 */
// Used by main.c
extern void runGame();

#endif

