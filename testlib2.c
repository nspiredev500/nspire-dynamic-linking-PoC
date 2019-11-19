
#include <os.h>

#include "include/osext.h"

void (*test3)() = 0;
void test()
{
	bkpt();
}





int main(int argsn, char *argc)
{
	//bkpt();
	initRecursiveDynlinker();
	//bkpt();
	registerLibrary_r("testlib2",test);
	//test3 = requestLibrary_r("testlib3");
	//bkpt();
	nl_set_resident();
	
	return 0;
}














