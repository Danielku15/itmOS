#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include <list>
#include "Task/Task.h"
#include "Scheduler/Scheduler.h"

#define SAVEREG 	asm ("\t push {r0,r1,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15}");
#define LOADREG		asm ("\t pop {r0,r1,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15}");
#define MAX_TASKS 10

using namespace std;

extern int registers[16];

#pragma SWI_ALIAS(48);
int swi ();

void save(int* regs);

extern int stackPointer;

class TaskManager {
public:
	TaskManager();
	virtual ~TaskManager();
	
	// create a new Task
	Task* createTask(void(*function)(void));
	
	// deletes an existing Task
	int deleteTask(Task* task);
	
	// schedules a task called by interrupt
	void schedule();
	
	// run all the tasks (this should be the start routine)
	void run();
	
	// getter/setter
	list<Task*> getTasks() const { return _tasks; }
	
	Scheduler* getScheduler() const { return _scheduler; }
	void setScheduler(Scheduler* scheduler) { _scheduler = scheduler; }
	
	Task* getActiveTask() const { return _activeTask; }
	void setActiveTask(Task* activeTask) { _activeTask = activeTask; }
	
private:
	// list of all tasks waiting to be executed
	list<Task*> _tasks;
	
	// Scheduler for deciding, which task is the CHOSEN ONE
	Scheduler* _scheduler;
	
	// this is the active Task - we need to save for later reuse
	Task* _activeTask;

	// returns the next free TaskID
	TID_t getNextTaskID();

	// array of all task ids
	TID_t _tids[MAX_TASKS];
};

#endif /*TASKMANAGER_H_*/
