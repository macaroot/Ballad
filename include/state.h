/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#ifndef STATE_H
#define STATE_H

enum Mode {
	PLAY,
	QUIT
} mode;

struct State {
	int videoCreated;
	int windowCount;
	int xcursor;
	int ycursor;
	int clicked;
} state;

#endif
