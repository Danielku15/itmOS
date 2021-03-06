#ifndef SYSTEMCALLS_H_
#define SYSTEMCALLS_H_

//--------------------------------System - Calls ----------------------
#define EXIT                0x1
#define KILL                0x2
#define EXEC                0x3
#define FORK                0x4
#define YIELD               0x5

#define WRITE               0x6
#define WRITE_RESPONSE      0x7

#define SUSPEND	            0x8
#define SEMAPHORE           0x9
#define NOTIFY              0xA
#define WAIT                0xB

//--------------------------------Semaphore IDs-------------------------
#define SELF 0x0
#define SERVICE_ID 0x1
#define TASK_ID 0x2

//--------------------------------Service- IDs--------------------------
#define TIMER_SERVICE_ID 0x60
#define BUTTON_SERVICE_ID 0xB
#define LED_SERVICE_ID 0xED
#define SERIAL_SERVICE_ID 0x11
#define DISPLAY_SERVICE_ID 0xD1
#define SHELL_SERVICE_ID 0x01
#define AUDIO_SERVICE_ID 0xA

//--------------------------------SWI to Kernel------------------------
#pragma SWI_ALIAS(0);
void swi(int swiNumber, int receiver, int length, int params[]);

void performSystemCall(int systemCallId);
void performSystemCall(int systemCallId, int length, int params[]);
void performServiceCall(int serviceId, int length, int params[]);
void performServiceResponse(int callerId, int length, int params[]);

#endif /*SYSTEMCALLS_H_*/
