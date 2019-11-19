
#include <os.h>

#include "include/osext.h"

void (*test3)() = 0;
void test()
{
	if (test3 != 0)
	{
		test3();
	}
}





int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	registerLibrary_r("testlib2.lib",test);
	test3 = requestLibrary_r("testlib3.lib");
	nl_set_resident();
	
	return 0;
}














