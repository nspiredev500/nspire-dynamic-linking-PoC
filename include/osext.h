#ifndef OSEXT_H
#define OSEXT_H
// include this file if you want to use OSExt functions in your programm
#define OSEXT_SYSCALL_MASK 0x70000

bool registerLibrary(char* name,void *functiontable) // name should be the name of the library file and functiontable a table with all functions you want to export
{
	//unsigned int nr = OSEXT_SYSCALL_MASK | (5*20+10);
	unsigned int nr = OSEXT_SYSCALL_MASK | (5*20+10);
	register int r0 asm("r0") = (int) name;
	register int r1 asm("r1") = (int) functiontable;
	asm volatile(
		"swi %[nr]\n"
		: "=r" (r0)
		: [nr] "i" (nr)
		: "memory", "r2", "r3", "r4", "r12", "lr");
	return (bool) r0;
}

void* requestLibrary(char *name)
{
	//unsigned int nr = OSEXT_SYSCALL_MASK | (5*20+10+1);
	unsigned int nr = OSEXT_SYSCALL_MASK | (5*20+10+1);
	register int r0 asm("r0") = (int) name;
	asm volatile(
		"swi %[nr]\n"
		: "=r" (r0)
		: [nr] "i" (nr)
		: "memory", "r1", "r2", "r3", "r4", "r12", "lr");
	return (void*) r0;
}



bool osext_installed()
{
	unsigned int INTS_SWI_HANDLER_ADDR = 0x28;
	unsigned int *swi_handler_adrs = (unsigned int*) (OS_BASE_ADDRESS + INTS_SWI_HANDLER_ADDR);
	unsigned int *swi_handler = (unsigned int*) *swi_handler_adrs; // saving ndless swi handler for calling
	if (*(swi_handler-3) == 0xe81) // check OSExt signature
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif