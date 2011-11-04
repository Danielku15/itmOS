#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include <list>

#include "globals.h"
#include "Task/Task.h"
#include "Scheduler/Scheduler.h"

#pragma SWI_ALIAS(48);
int swi ();


class TaskManager {
public:
	TaskManager();
	virtual ~TaskManager();
	
	// create a new Task
	Task* createTask(std::string name, void(*function)(void));
	
	// deletes an existing Task
	int deleteTask(Task* task);
	
	// shows all runnig tasks
	void showTasks();
	
	// run all the tasks (this should be the start routine)
	void run();
	
	// getter/setter
	Task** getTasks() { return _tasks; }
	
	Scheduler* getScheduler() { return _scheduler; }
	void setScheduler(Scheduler* scheduler) { _scheduler = scheduler; }
	
	Task* getActiveTask() { return _activeTask; }
	void setActiveTask(Task* activeTask) { _activeTask = activeTask; }
	
private:
	// list of all tasks waiting to be executed
	Task* _tasks[MAX_TASKS];
	int pos;
	
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
