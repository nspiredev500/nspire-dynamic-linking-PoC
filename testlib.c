
#include <os.h>

#include "include/osext.h"

#include <nspireio2.h>

void test()
{
	uart_printf("\ntest function called!\n");
}



int main(int argsn, char *argc)
{
	
	registerLibrary("testlib",test);
	
	nl_set_resident();
	
	return 0;
}














