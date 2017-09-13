/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#ifndef LOGIC_H
#define LOGIC_H

/*****************************************************************************
 * Getset declarations                                                       *
 *****************************************************************************/

typedef struct sSpriteList sSPRITELIST;
/*{{{*/
void* spriteList_getPointer( void );
int spriteList_getModusFlags( sSPRITELIST*, int );
void spriteList_setModusFlags( sSPRITELIST*, int, int );
int spriteList_getModusFlux( sSPRITELIST*, int );
void spriteList_setModusFlux( sSPRITELIST*, int, int );
void spriteList_getPosition( sSPRITELIST*, int, int** );
void spriteList_setPosition( sSPRITELIST*, int, int* );
int* spriteList_getGraphic( sSPRITELIST*, int );
void spriteList_setGraphic( sSPRITELIST*, int, int* );/*}}}*/

/*****************************************************************************
 * Function declarations                                                     *
 *****************************************************************************/

extern void vTheLoop();

#endif
