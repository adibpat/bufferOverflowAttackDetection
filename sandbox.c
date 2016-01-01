#include <signal.h>
#include <sys/ucontext.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
extern void readString(char *s, int r);
int expectedReturn=0;
void SEGV_handler(int signum, siginfo_t * info, void * context)
{
	ucontext_t *ucontext = (ucontext_t*)context;
	int faultAt = ((unsigned int *)(info->si_addr)); /*The address on accessing which, SEGV occurs. Address of the called module with no EXEC rights*/
	if(expectedReturn != 0)
	{
		if (expectedReturn != faultAt)
		{	/*The return address is not as per expected hence it has been overwritten by a bufferoverflow*/
			printf("malicious buffer overflow detected, will exit!\n");
			exit(1);
		}
	}
	/*Get the location at which the reutrn address is stored*/
	long location = (long)(((ucontext_t *)(context))->uc_mcontext.gregs[15]);
	
	int address = *((int *)location); /*Return address for the called module*/
	expectedReturn = address; /*Set this address as the expected address for next SEGV*/
	
	
	/*Set protection such that the adress that caused segfault (called module) can now execute */
	mprotect((void*)(faultAt & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE | PROT_EXEC ); // can execute !!!
	/*Calling module cannot execute*/
	mprotect((void*)(address & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE) ; //   cannot execute !!!
	return;
}

void init_sandbox()
{
	mprotect((void*)((unsigned int)readString & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE /* | PROT_EXEC */); // cannot execute !!!

	struct sigaction segv_handle, old_action;
	segv_handle.sa_sigaction = SEGV_handler;
	sigemptyset(&segv_handle.sa_mask);
	segv_handle.sa_flags = SA_RESTART | SA_SIGINFO;
  	sigaction(SIGSEGV,&segv_handle,&old_action); /* Set signal handler for SIGSEGV to SEGV_handler */
}
