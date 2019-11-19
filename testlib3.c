
#include <os.h>

#include "include/osext.h"


void test()
{
	
}




int main(int argsn, char *argc)
{
	initRecursiveDynlinker();
	registerLibrary_r("testlib3",test);
	bkpt();
	nl_set_resident();
	
	return 0;
}














