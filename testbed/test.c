#include "stdio.h"
int main( int argc, char *argv[] )
{
	int sprite[] = { 0x80D8A501 };

	int alpha = ( ( ( sprite[0] >> 0x1C ) & 0x3 ) | ( ( ( sprite[0] >> 0x1C ) & 0x3 ) << 0x2 ) ) | \
				( ( ( ( sprite[0] >> 0x1C ) & 0x3 ) | ( ( ( sprite[0] >> 0x1C ) & 0x3 ) << 0x2 ) ) << 0x4 );

	printf( "%04x\n", alpha);

	return 0;
}
