
#include <os.h>

#include "include/osext.h"

void (*test2)() = 0;

void test()
{
	if (test2 != 0)
		test2();
}


int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	registerLibrary_r("testlib.lib",test);
	test2 = requestLibrary_r("testlib2.lib");
	
	
	
	nl_set_resident();
	
	return 0;
}














