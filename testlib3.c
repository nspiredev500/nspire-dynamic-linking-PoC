
#include <os.h>

#include "include/osext.h"


void test()
{
	bkpt();
}





int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	registerLibrary_r("testlib3.lib",test);
	nl_set_resident();
	
	return 0;
}














