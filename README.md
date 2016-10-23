# Ballad
## Game Project

### Description
Ballad is a personal project to increase my understanding in C
and create a game at the same time. SDL2 and OpenGL are the basic
libraries used.

### Legal
This code is open-source.
Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
and may not be used for commercial use without written permission.
Fair Use applies, naturally.

### Coding practices
**Variables and functions**
Major variables and function are defined separate, with variables
at the top of the file.

**.h**
Headers are used only for declaring extern types. Each variable
and function includes a comment about its use and what source uses
them. Every header is accompanied by a source which defines its
declarations.

**.c**
Sources are named after the header that most influences them.
Variables and functions initialized in the source should be at
the top of the file, if possible. Sources have only the necessary
includes.

**Naming conventions**
The following rules don't apply to things specifically derived from
SDL2 and OpenGL, these have sdl and gl -prefixes respectively.
Everything mentioned is a prefix. Camelcase is used for everything
but constants, which are uppercase with underscores.

p -pointer
i -int
c -char
f -float
ir/cr/sr -int array/char array/string array
S -struct
e -enum
U -union
