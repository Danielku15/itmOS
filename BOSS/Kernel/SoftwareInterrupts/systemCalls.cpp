
#include "API/systemCalls.h"
#include "API/serviceCalls.h"
#include "SoftwareInterrupt.h"

void performServiceCall(int params[]) {
    performSyscall(SERVICE_CALL, params);
}

void performSyscall(int syscallId, int parameters[]) {
    swi(syscallId, parameters);
}
