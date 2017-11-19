/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#ifndef STATE_H
#define STATE_H

enum Mode {
	QUIT,
	NORMAL,
	FGM_MENU,
	BGM_MENU,
	FGC_MENU,
	BGC_MENU,
	FGA_MENU,
	BGA_MENU
} mode;

enum Tool {
	T_NONE,
	T_PIN
} tool;

enum Key {
	K_NONE,
	K_RETURN,
	K_SPACE,
	K_LEFT,
	K_UP,
	K_RIGHT,
	K_DOWN,
	K_Q,
	K_F,
	K_B,
	K_M,
	K_C,
	K_A
} key, prevKey;

struct State {
	int videoCreated;
	int windowCount;
	int xcursor;
	int ycursor;
	int xtetra;
	int ytetra;
	int tetraField[0x10e][0xa4];
	int curTetra;
	int futTetra;
	int fgMapSel;
	int bgMapSel;
	int fgColSel;
	int bgColSel;
	int fgAlpSel;
	int bgAlpSel;
	int clicked;
} state;

#endif
