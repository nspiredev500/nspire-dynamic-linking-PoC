#ifndef ADDSYSCALLS_H
#define ADDSYSCALLS_H

#define OS_BASE_ADDRESS 0x10000000


static const unsigned int OSEXT_SIGNATURE = 0xe81;

//from ndless ints.c
//#define INTS_SWI_HANDLER_ADDR 0x28
static const unsigned int INTS_SWI_HANDLER_ADDR = 0x28;
static const unsigned int INTS_INIT_HANDLER_ADDR = 0x20;
#define SYSCALL_TABLE_SIZE 400
unsigned int my_syscall_table[SYSCALL_TABLE_SIZE];

extern unsigned int OSExt_sign;
extern unsigned int syscall_table;
extern unsigned int swi_handler;
extern unsigned int next_sig;
extern unsigned int next_ptr;
extern unsigned int ndless_swi_asm;
unsigned int *ndless_swi;

static const unsigned int mysyscall_mask = 0x70000;






void setSyscall(int syscall_number,unsigned int address)
{
	
	my_syscall_table[syscall_number] = address;
}



void extendSWIHandler()
{
	
	
	unsigned int *swi_handler_adrs = (unsigned int*) (OS_BASE_ADDRESS + INTS_SWI_HANDLER_ADDR);
	
	
	
	ndless_swi = (unsigned int*) *swi_handler_adrs; // saving ndless swi handler for calling
	
	
	ndless_swi_asm = (unsigned int) ndless_swi;
	syscall_table = (unsigned int) my_syscall_table;
	
	
	next_sig = (int) *(ndless_swi-2); // copy N-ext-signature to my swi handler
	next_ptr = (int) *(ndless_swi-1);
	OSExt_sign = OSEXT_SIGNATURE;
	
	
	
	
	void **adr_ptr = (void**)INTS_INIT_HANDLER_ADDR;
	*adr_ptr = *(void**)(OS_BASE_ADDRESS + INTS_INIT_HANDLER_ADDR);
	*(adr_ptr + 2) = &swi_handler;
	*(void**)(OS_BASE_ADDRESS + INTS_SWI_HANDLER_ADDR) = &swi_handler;
	
	
}

asm("OSExt_sign: .long 0\n" // r0 = syscall number, r2 = spsr
"next_sig: .long 0\n"
"next_ptr: .long 0\n"
"swi_handler:\n" // parts from ndless ints.c
" stmfd	sp!, {r0-r2, r3} \n" 
" mrs	r2, spsr \n"
" tst	r2, #0b100000\n"// my syscalls can't be called from thumb
" beq arm_state\n" 
" ldr r1, ndless_swi_asm\n"
" str r1, [sp, #12]\n" // put the address of the ndless swi handler on the stack
" msr spsr, r2\n" // restore original spsr
" ldmfd sp!, {r0-r2, pc}\n" // call ndless swi handler
" arm_state: ldr r0, [lr, #-4]\n" // thumb syscalls relayed to ndless swi handler, now only arm syscalls
" bic	r0, r0, #0xFF000000\n" // extract the comment field of the swi instruction
" mov r1, r0\n"
" and	r1, #0x70000   @ keep the flag \n" 
" bic	r0, #0x70000   @ clear the flag \n"
" cmp r1, #0x70000\n" // check for my flag
" beq my_syscall\n"
" ldr r0, ndless_swi_asm\n" //relay to ndless swi handler 
" str r0, [sp, #12]\n"
" msr spsr, r2\n" // restore original spsr
" ldmfd sp!, {r0-r2, pc}\n" // relaying other syscalls works
" my_syscall: \n" // filtering out my syscalls works
" ldr r1, saved_lr\n"
" cmp  r1, #0\n"
" adreq r1, saved_spsr\n" // use 2nd values if first are used for 1-level recursion
" adrne r1, saved_spsr2\n"
" str r2, [r1]\n" // save lr and spsr
" str lr, [r1, #4]\n"
" ldr r1, syscall_table\n"
" ldr r0, [r1, r0, lsl #2]\n" // get syscall address
" str r0, [sp, #12]\n"
//" bkpt\n"
" mov lr, pc\n" // save return address
" ldmfd sp!, {r0-r2, pc}\n" // jump to syscall
" back_from_syscall: \n"
" stmfd	sp!, {r0-r3} \n"
" mrs	r0, cpsr \n"
" adr	r2, saved_spsr2 \n"
" ldr	r1, [r2] \n"
" cmp	r1, #0 \n" // Returning from level-1 recursion?
" ldreq	r1, [r2, #-8]! \n" // No, use saved_spsr
" mov	r3, #0 \n"
" str	r3, [r2], #4 \n" // Update the recursion level, and point to saved_lr(2)
" ldr	lr, [r2] \n" // Read from saved_lr(2)
" and	r1, #0xFFFFFF3F \n" // Remove the mask
" and	r0, #0x80 \n" // Keep the IRQ mask (FIQ always enabled for lcd_compat)
" orr	r1, r0 \n" // Keep the new mask
" msr	cpsr, r1 \n" // swi *must* restore cpsr. GCC may optimize with a cmp just after the swi for instance
" ldmfd	sp!, {r0-r3} \n"
" bx	lr \n" // Back to the caller
"saved_spsr: .long 0 \n"
"saved_lr: .long 0 \n" // For 1-level recursion (syscall calling a syscall) if not null, in level-1 recursion \n"
"saved_spsr2: .long 0 \n"
"saved_lr2: .long 0 \n"
"ndless_swi_asm: .long 0\n" // address of the ndless swi handler
"syscall_table: .long 0\n");
#endif