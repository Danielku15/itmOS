
#ifndef TESTTASK_H_
#define TESTTASK_H_

#include "Tasks/UserModeTask.h"
#include "API/LED.h"

class TestTask : public UserModeTask {

public:

	TestTask();
	virtual ~TestTask();

	virtual MessageQueue* getQueue();
	virtual void executeMessage(Message* message);

	void start();
};

#endif /* TESTTASK_H_ */