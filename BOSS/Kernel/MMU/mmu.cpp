#include "API/dataTypes.h"
#include "mmu.h"

address taskMasterTableAddresses[MAX_TASKS] = {(address)0x0};

void mmu_initMemoryForTask(int taskId) {
    address taskMasterTableAddress = taskMasterTableAddresses[taskId];
    if (taskMasterTableAddress == (address)0x0) {
        if (taskId == 0) {
            unsigned int i;
            address tableAddress = (address)0x40200000;
            taskMasterTableAddress = tableAddress;
            // Set Domain Access control register to 0101 0101 0101 0101 0101 0101 0101 0111 
            asm("\t MOV r1, #0x5557\n");
            asm("\t MOVT r1, #0x5555\n");
            asm("\t MCR p15, #0, r1, c3, c0, #0\n");
            
            // Set the Master Table Pointer to the internal ram
            asm("\t MOV r1, #0x0000\n");
            asm("\t MOVT r1, #0x4020\n");
            asm("\t MCR p15, #0, r1, c2, c0, #0\n");
            
            // Initialize Master Table
            for (i = 0x00000000; i < 0xFFF00000; i += 0x00100000) {
                *tableAddress = i | 0xC12;
                tableAddress++;
            }
            *tableAddress = 0xFFF00C12;
            
            // Enable MMU
            asm("\t MRC p15, #0, r1, c1, c0, #0\n");
            asm("\t ORR r1, r1, #0x1\n");
            asm("\t MCR p15, #0, r1, c1, c0, #0\n");
        } else {
            // TODO init task memory
        }
    } else {
        // TODO switch master table
    }
    taskMasterTableAddresses[taskId] = taskMasterTableAddress;
}
void mmu_loadPage(int pageNumber) {
    //TODO
}