#ifndef TASKS_H_
#define TASKS_H_

#define MAX_TASKS 256

#include <stdlib.h>

typedef int TID_t;
enum Status { Ready, Running, Blocked };

// interrupt
#pragma SWI_ALIAS(48);
int swi();

typedef struct {
	
	// id of task
	TID_t id;
	// name of task
	char* name;
	// status of task
	Status status;
	// priority of task (from 0 to 20 -> higher = more important)
	int priority;
	// registers
	int stackPointer;
	// entry
	int initAddr;
	// already started
	bool hasBeenStarted;
} Task;

// logic variables
Task* _tasks[MAX_TASKS];
int nextTask = 0;
int activeTask = -1;


// create Task
TID_t createTask(char* name, int priority, int initAddress) {

	Task* t = (Task*) malloc(sizeof(Task));
	// init Task
	t->id = nextTask;
	t->name = name;
	t->priority = priority;
	t->initAddr = initAddress;
	t->hasBeenStarted = false;
	t->status = Ready;
	t->stackPointer = 0x8200A000 + (nextTask + 1) * 0x00010000;
	
	// add Task
	_tasks[nextTask] = t;

	// increase nextOne
	nextTask++;
	
	// return TaskID
	return t->id;	
}

// Scheduler - get next Task to Run
void scheduleNextTask() {

	while (_tasks[++activeTask % MAX_TASKS] == 0) {	
	}
	activeTask = activeTask % MAX_TASKS;
}

void initTasks() {

	int i = 0;
	for (i = 0; i < MAX_TASKS; i++) {
	
		_tasks[i] = NULL;	
	}	
}














asm(	"\t .bss _stack_pointer_interrupted, 4 \n" \
		"\t .bss _stack_pointer_restored, 4 \n" \
		"\t .bss _stack_pointer_task_manager, 4 \n" \
		"\t .bss _return_address, 4 \n" \
		"\t .bss _function_pointer, 4 \n" \
		
		"\t .global _stack_pointer_interrupted \n" \
		"\t .global _stack_pointer_restored \n" \
		"\t .global _stack_pointer_task_manager \n" \
		"\t .global _return_address \n" \
		"\t .global _function_pointer \n" \

		"function_pointer .field _function_pointer, 32 \n" \
		"stack_pointer_interrupted .field _stack_pointer_interrupted, 32 \n" \
		"stack_pointer_restored .field _stack_pointer_restored, 32 \n" \
		"stack_pointer_task_manager .field _stack_pointer_task_manager, 32 \n" \
		"return_address .field _return_address, 32");

extern int stack_pointer_interrupted;
extern int stack_pointer_restored;
extern int stack_pointer_task_manager;
extern int return_address;
extern int function_pointer;

// Interrupt Handler
#pragma TASK
#pragma INTERRUPT (SWI) ;
extern "C" void c_intSWI()  {
	
	// TODO HANDLE INTERRUPT
	// TODO when starting a new process, what's the return register?

	// we are now in the supervisor mode 0x13
	// we must save the return address of the supervisor mode
	// (lr) to return to the user process

	// then we save all registers on the process stack
	// then we schedule the next process

	// if the scheduled process hasn't been started yet
	// 		start the process
	// otherwise
	//		restore the context of the process (registers)

	// the stack frame looks like this:
	// TOP OF STACK 		return address
	// TOP OF STACK -1		cpsr
	// IN BETWEEN			r0 - r11
	// BOTTOM OF STACK		r12
	
	// store the return address
	asm("\t PUSH {r0} \n" \
		"\t LDR r0, return_address \n" \
		"\t STR lr, [r0] \n" \
		"\t POP {r0} \n");

	// to save the process context we can switch in the system
	// mode, because system mode has the same stack
	asm("\t CPS 0x1F");
	
	if(activeTask != -1) {
	
		// now save all registers inclusive CPSR
		asm("\t STMFD sp!, {r0-r12} \n" \
			"\t MRS r5, cpsr \n" \
			"\t STMFD sp!, {r5}");
	
		// save the new return address
		asm("\t LDR r0, return_address \n" \
			"\t LDR r0, [r0] \n" \
			"\t STMFD sp!, {r0}");
	
		// the new stack pointer of the process has to be saved
		// to restore the process
		asm("\t LDR r0, stack_pointer_interrupted \n" \
			"\t STR sp, [r0]");
	
		// the register r0 to r12 and the cpsr plus the new return address
		// are now on the process stack
		
		// load the context of the task manager
		// TODO load the cpsr register?
		asm("\t LDR sp, stack_pointer_task_manager \n" \
			"\t LDR sp, [sp] \n" \
			"\t LDMFD sp!, {r0-r12}");

		// save the new stack pointer of the interrupted task
		_tasks[activeTask]->stackPointer = stack_pointer_interrupted;
	}
	
	// schedule next task
	scheduleNextTask();

	// check if the task has been started
	if(_tasks[activeTask]->hasBeenStarted == false) {
		_tasks[activeTask]->hasBeenStarted = true;
		
		// the process hasn't been started yet
		// we have to start the process in the user mode
		// therefore we can't just call the function pointer
		// and we have to leave the interrupt handler correctly
		// (either with return or with the LDMFD assembler instruction

		// to start the process we simply set the return address
		// of the handler to the process start (function pointer address)

		function_pointer = _tasks[activeTask]->initAddr;

		// the new process has its own stack and we have to set
		// the stack pointer of it
		stack_pointer_interrupted = _tasks[activeTask]->stackPointer;
		
		
		// save taskmanager context
		asm("\t STMFD sp!, {r0-r12} \n" \
			"\t LDR r0, stack_pointer_task_manager \n" \
			"\t STR sp, [r0, #0]");
		
		
		// switch to task stack
		asm("\t LDR sp, stack_pointer_interrupted \n" \
			"\t LDR sp, [sp]");

		// switch back to the interrupt handler
		asm("\t CPS 0x13");

		// set the new return address
		asm("\t LDR lr, function_pointer \n" \
			"\t LDR lr, [lr]");

	} else {

		// restore the context of the next process
		// to restore the context we have to switch to the
		// process stack
		// therefore we set the stack pointer of the process
		stack_pointer_restored = _tasks[activeTask]->stackPointer;
		
		
		// save taskmanager context
		asm("\t STMFD sp!, {r0-r12} \n" \
			"\t LDR r0, stack_pointer_task_manager \n" \
			"\t STR sp, [r0, #0]");
		
		
		// switch to task stack
		asm("\t LDR sp, stack_pointer_restored \n" \
			"\t LDR sp, [sp]");

		// the return address is at the top of the stack so we need
		// to read it first
		asm("\t LDR r0, function_pointer \n" \
			"\t LDR r1, [sp, #0] \n" \
			"\t STR r1, [r0, #0] \n" \
			// move stack pointer to the register r0-r12
			"\t ADD sp, sp, #4");

		// now read the cpsr register
		asm("\t LDMFD sp!, {r0} \n" \
			"\t MSR SPSR_cxsf, r0");

		// now read the registers r0-r12
		asm("\t LDMFD sp!, {r0-r12}");

		// switch back to the interrupt handler
		asm("\t CPS 0x13");

		// set the new return address
		asm("\t LDR lr, function_pointer \n" \
			"\t LDR lr, [lr]");
	}
	
	
}


#endif /*TASKS_H_*/