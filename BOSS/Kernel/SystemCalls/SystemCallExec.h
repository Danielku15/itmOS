#ifndef SYSTEMCALLEXEC_H_
#define SYSTEMCALLEXEC_H_

#include "Kernel/Kernel.h"
#include "Kernel/Task/TaskManager.h"
#include "API/systemCalls.h"

class Kernel;

class SystemCallExec
{
	private:
		Kernel* _kernel;
		TaskManager* _taskmanager;
		
        bool semaphore(bool enterOrLeave, int semaphoreType, int id);
	public:
		SystemCallExec(Kernel* kernel, TaskManager* taskmanager);
		virtual ~SystemCallExec();
		
		// returns true if context switch is needed
		// does SystemCall Action
		bool execute(int swiNumber, int params[]);
};

#endif /*SYSTEMCALLEXEC_H_*/
