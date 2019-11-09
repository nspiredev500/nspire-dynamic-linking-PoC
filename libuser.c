
#include <os.h>
#include "include/osext.h"
#include "include/osext.h"





int main(int argsn, char *argc)
{
	void (*test)() = requestLibrary("testlib");
	test();
	
	
	
	return 0;
}














