# Tetra Editor
## Editor for tetra image format

### Description
Tetra is a crude image format whose uncompressed size is ~16
times smaller than regular uncompressed 8bit rgba image formats.
This is acchieved by several limitations. Images consist of 4x4 pixel grids
(which are called tetras), each pixel in the tetra can be either foreground or
background, and both foreground and background of each tetra can be one of
64 colors and one of 4 levels of alpha. Images have built-in frames, which
can be used for animation.

### Legal
This code is open-source.
Images are copyrighted by Lasse Ilmonen / ilmoj (2016),
and may not be used for commercial use without written permission.
Fair Use applies, naturally.
