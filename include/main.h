/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
#ifndef MAIN_H
#define MAIN_H

/*****************************************************************************
 * Getset declarations                                                       *
 *****************************************************************************/

typedef struct sWindowEntity WINDOW;
/*{{{*/
/* WINDOW* window_create( void ); */
/* void window_free( WINDOW* ); */
void* window_getPointer( void );
void window_setPointer( WINDOW* );
int window_getWidth( WINDOW* );
void window_setWidth( WINDOW*, int );
int window_getHeight( WINDOW* );
void window_setHeight( WINDOW*, int );
/* int window_getTetraRow( WINDOW* ); */
void window_setTetraRow( WINDOW*, int );
/* int window_getTetraColumn( WINDOW* ); */
void window_setTetraColumn( WINDOW*, int );
/* int window_getTetpixSize( WINDOW* ); */
void window_setTetpixSize( WINDOW*, int );
void* window_getContext( WINDOW* );
void window_setContext( WINDOW*, SDL_Window* );
void* window_getRenderer( WINDOW* );
void window_setRenderer( WINDOW*, SDL_Renderer* );/*}}}*/

/*****************************************************************************
 * Function declarations                                                     *
 *****************************************************************************/

#endif

