/* This code is open-source.
 * Images and music are copyrighted by Lasse Ilmonen / ilmoj (2016),
 * and may not be used for commercial use without written permission.
 * Fair Use applies, naturally.
 */
/* .h includes */
#include "system.h"
#include "logic.h"

int main(int argc, char *argv[])
{
	if(!begin_system())
		goto fail;
	run_loop();
	if(!terminate_system())
		goto fail;
	return 0;
fail:
	return 1;
}
