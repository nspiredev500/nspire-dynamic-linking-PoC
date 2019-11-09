#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <os.h>
#include <nspireio2.h>



typedef struct Library Library;
struct Library
{
	char *name;
	void *functiontable;
	Library *next;
};
struct Library *libs;
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



int main()
{
	extendSWIHandler();
	
	initDynlinker();
	
	nl_set_resident();
	clear_cache();
	return 0;
}