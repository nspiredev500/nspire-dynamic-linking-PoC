#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <os.h>
#include <nspireio2.h>
#include <libndls.h>


typedef struct Library Library;
struct Library
{
	char *name;
	void *functiontable;
	Library *next;
};
struct Library *libs = NULL;
typedef struct
{
	char *name;
	char *translation;
} TranslationEntry;

bool s_addLibrary();
void* s_requestLibrary();
bool loadLibrary(char *name);
Library* searchLibrary(char * name);
void initDynlinker();
void addLibraryEntry(char *name, void *functiontable);


void setSyscall(int syscall_number,unsigned int address);
void extendSWIHandler();

#include "addsyscalls.h"
#include "dynlinker.h"



int main(int argsn, char ** argv)
{
	uart_printf("argsn: %d\n",argsn);
	
	for (int i = 0;i<argsn;i++)
	{
		uart_printf("argv[%d]: %s\n",i,argv[i]);
	}
	
	
	
	// values aren't shared because osext is run again, communication has to be done through syscalls
	if (argsn > 1 && argv[1] != NULL) 
	{
		return fileExtensionTriggered(argv[1]);
	}
	
	
	//needs ndless.cfg.tns to work
	//creating it doesn't seem to work
	//an empty config file has to be transferred to the calc once it seems
	
	
	cfg_register_fileext("libp","osext");
	cfg_register_fileext("lib","osext");
	
	
	
	extendSWIHandler();
	
	initDynlinker();
	
	nl_set_resident();
	clear_cache();
	return 0;
}