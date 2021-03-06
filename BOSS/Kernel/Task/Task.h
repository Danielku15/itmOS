#ifndef TASK_H_
#define TASK_H_

#include <list>
#include "API/dataTypes.h"
#include "Messaging/MemoryManager/MemoryManager.h"

class Semaphore;

typedef int TID_t;
enum Status { Ready, Running, Blocked, Wait, WaitForSemaphore };

/*
 *  This struct is a solid Task - everyone is solid @ Task Library
 *  - Task: Task itself
 *  - TCB: Task Control Block
 */
struct TCB {
    
    // all registers
    int CPSR;
    int restartAddress;
    int R0;
    int R1;
    int R2;
    int R3;
    int R4;
    int R5;
    int R6;
    int R7;
    int R8;
    int R9;
    int R10;
    int R11;
    int R12;
    int R13;
    int R14;
};

class Task {
    public:
        MemoryManager* memoryManager;
        
        address masterTableAddress;
        // id of task
        TID_t id;
        // name of task
        char* name;
        // status of task
        Status status;
        // priority of task (from 0 to 20 -> higher = more important)
        int priority;
        // registers
        TCB tcb;
        
        Semaphore* semaphore;
        
        // Code Location
        address codeLocation;
        
        // Pagecount
        int pageCount;
        
        // MMU Registers to map
        std::list<address>* taskRegisters;
        
        // parent/child
        Task* parent;
        Task* child;
            
    	Task();
    	virtual ~Task();
};

#endif /*TASK_H_*/
