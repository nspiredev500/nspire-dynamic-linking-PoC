
#include <os.h>
#include "include/osext.h"





int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	void (*test)() = requestLibrary_r("testlib.lib");
	if (test != 0)
		test();
	
	return 0;
}














