
#include <os.h>
#include "include/osext.h"





int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	void (*test)() = requestLibrary_r("testlib");
	if (test != 0)
		test();
	requestLibrary_r("testlib2");
	requestLibrary_r("testlib3");
	
	return 0;
}














