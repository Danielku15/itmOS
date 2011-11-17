
#include "API/systemCalls.h"
#include "API/serviceCalls.h"
#include "softwareInterrupt.h"

void performServiceCall(int params[]) {
    performSyscall(SERVICE_CALL, params);
}

void performSyscall(int syscallId, int parameters[]) {
    swi(syscallId, parameters);
}
