#include "DisplayService.h"

DisplayService::DisplayService() : Service(), _currentTaskId(-1) {	
	// Background
	_driver.moveTo(0, 0);
	_driver.setColor(0xFF007F);
	_driver.drawRect(WIDTH, HEIGHT);

	// ASCII Image
	_driver.setColor(0x00000000);
	_driver.moveTo(20, 20);
	_driver.drawString("                         8888  8888888\n                  888888888888888888888888\n               8888:::8888888888888888888888888\n             8888::::::8888888888888888888888888888\n            88::::::::888:::8888888888888888888888888\n          88888888::::8:::::::::::88888888888888888888\n        888 8::888888::::::::::::::::::88888888888   888\n           88::::88888888::::m::::::::::88888888888    8\n         888888888888888888:M:::::::::::8888888888888\n        88888888888888888888::::::::::::M88888888888888\n        8888888888888888888888:::::::::M8888888888888888\n         8888888888888888888888:::::::M888888888888888888\n        8888888888888888::88888::::::M88888888888888888888\n      88888888888888888:::88888:::::M888888888888888   8888\n     88888888888888888:::88888::::M::;o*M*o;888888888    88\n    88888888888888888:::8888:::::M:::::::::::88888888    8\n   88888888888888888::::88::::::M:;:::::::::::888888888     \n  8888888888888888888:::8::::::M::aAa::::::::M8888888888       8\n  88   8888888888::88::::8::::M:::::::::::::888888888888888 8888\n 88  88888888888:::8:::::::::M::::::::::;::88:88888888888888888\n 8  8888888888888:::::::::::M::\"@@@@@@@\"::::8w8888888888888888\n  88888888888:888::::::::::M:::::\"@a@\":::::M8i888888888888888\n 8888888888::::88:::::::::M88:::::::::::::M88z88888888888888888 \n8888888888:::::8:::::::::M88888:::::::::MM888!888888888888888888\n888888888:::::8:::::::::M8888888MAmmmAMVMM888*88888888   88888888\n888888 M:::::::::::::::M888888888:::::::MM88888888888888   8888888\n8888   M::::::::::::::M88888888888::::::MM888888888888888    88888\n 888   M:::::::::::::M8888888888888M:::::mM888888888888888    8888\n  888  M::::::::::::M8888:888888888888::::m::Mm88888 888888   8888\n   88  M::::::::::::8888:88888888888888888::::::Mm8   88888   888\n   88  M::::::::::8888M::88888::888888888888:::::::Mm88888    88\n   8   MM::::::::8888M:::8888:::::888888888888::::::::Mm8     4\n       8M:::::::8888M:::::888:::::::88:::8888888::::::::Mm    2\n      88MM:::::8888M:::::::88::::::::8:::::888888:::M:::::M\n     8888M:::::888MM::::::::8:::::::::::M::::8888::::M::::M\n    88888M:::::88:M::::::::::8:::::::::::M:::8888::::::M::M\n   88 888MM:::888:M:::::::::::::::::::::::M:8888:::::::::M:\n   8 88888M:::88::M:::::::::::::::::::::::MM:88::::::::::::M\n     88888M:::88::M::::::::::*88*::::::::::M:88::::::::::::::M             \n    888888M:::88::M:::::::::88@@88:::::::::M::88::::::::::::::M\n    888888MM::88::MM::::::::88@@88:::::::::M:::8::::::::::::::*8\n    88888  M:::8::MM:::::::::*88*::::::::::M:::::::::::::::::88@@\n    8888   MM::::::MM:::::::::::::::::::::MM:::::::::::::::::88@@\n     888    M:::::::MM:::::::::::::::::::MM::M::::::::::::::::*8\n     888    MM:::::::MMM::::::::::::::::MM:::MM:::::::::::::::M\n      88     M::::::::MMMM:::::::::::MMMM:::::MM::::::::::::MM\n       88    MM:::::::::MMMMMMMMMMMMMMM::::::::MMM::::::::MMM\n        88    MM::::::::::::MMMMMMM::::::::::::::MMMMMMMMMM\n         88   8MM::::::::::::::::::::::::::::::::::MMMMMM\n          8   88MM::::::::::::::::::::::M:::M::::::::MM\n              888MM::::::::::::::::::MM::::::MM::::::MM\n             88888MM:::::::::::::::MMM:::::::mM:::::MM\n             888888MM:::::::::::::MMM:::::::::MMM:::M\n            88888888MM:::::::::::MMM:::::::::::MM:::M\n           88 8888888M:::::::::MMM::::::::::::::M:::M\n           8  888888 M:::::::MM:::::::::::::::::M:::M:\n              888888 M::::::M:::::::::::::::::::M:::MM\n             888888  M:::::M::::::::::::::::::::::::M:M\n             888888  M:::::M:::::::::@::::::::::::::M::M\n             88888   M::::::::::::::@@:::::::::::::::M::M\n            88888   M::::::::::::::@@@::::::::::::::::M::M\n           88888   M:::::::::::::::@@::::::::::::::::::M::M\n          88888   M:::::m::::::::::@::::::::::Mm:::::::M:::M\n          8888   M:::::M:::::::::::::::::::::::MM:::::::M:::M\n         8888   M:::::M:::::::::::::::::::::::MMM::::::::M:::M\n        888    M:::::Mm::::::::::::::::::::::MMM:::::::::M::::M\n      8888    MM::::Mm:::::::::::::::::::::MMMM:::::::::m::m:::M\n     888      M:::::M::::::::::::::::::::MMM::::::::::::M::mm:::M\n  8888       MM:::::::::::::::::::::::::MM:::::::::::::mM::MM:::M:\n             M:::::::::::::::::::::::::M:::::::::::::::mM::MM:::Mm\n            MM::::::m:::::::::::::::::::::::::::::::::::M::MM:::MM\n            M::::::::M:::::::::::::::::::::::::::::::::::M::M:::MM         \n           MM:::::::::M:::::::::::::M:::::::::::::::::::::M:M:::MM\n           M:::::::::::M88:::::::::M:::::::::::::::::::::::MM::MMM\n           M::::::::::::8888888888M::::::::::::::::::::::::MM::MM\n           M:::::::::::::88888888M:::::::::::::::::::::::::M::MM\n           M::::::::::::::888888M:::::::::::::::::::::::::M::MM\n           M:::::::::::::::88888M:::::::::::::::::::::::::M:MM\n           M:::::::::::::::::88M::::::::::::::::::::::::::MMM\n           M:::::::::::::::::::M::::::::::::::::::::::::::MMM\n           MM:::::::::::::::::M::::::::::::::::::::::::::MMM\n            M:::::::::::::::::M::::::::::::::::::::::::::MMM\n            MM:::::::::::::::M::::::::::::::::::::::::::MMM\n             M:::::::::::::::M:::::::::::::::::::::::::MMM\n             MM:::::::::::::M:::::::::::::::::::::::::MMM\n              M:::::::::::::M::::::::::::::::::::::::MMM\n              MM:::::::::::M::::::::::::::::::::::::MMM\n               M:::::::::::M:::::::::::::::::::::::MMM  \n               MM:::::::::M:::::::::::::::::::::::MMM\n                M:::::::::M::::::::::::::::::::::MMM\n                MM:::::::M::::::::::::::::::::::MMM\n                 MM::::::M:::::::::::::::::::::MMM\n                 MM:::::M:::::::::::::::::::::MMM\n                  MM::::M::::::::::::::::::::MMM\n                  MM:::M::::::::::::::::::::MMM\n                   MM::M:::::::::::::::::::MMM\n                   MM:M:::::::::::::::::::MMM\n                    MMM::::::::::::::::::MMM\n                    MM::::::::::::::::::MMM\n                     M:::::::::::::::::MMM\n                    MM::::::::::::::::MMM\n                    MM:::::::::::::::MMM\n                    MM::::M:::::::::MMM:\n                    mMM::::MM:::::::MMMM\n                     MMM:::::::::::MMM:M\n                     mMM:::M:::::::M:M:M\n                      MM::MMMM:::::::M:M\n                      MM::MMM::::::::M:M\n                      mMM::MM::::::::M:M\n                       MM::MM:::::::::M:M\n                       MM::MM::::::::::M:m\n                       MM:::M:::::::::::MM\n                       MMM:::::::::::::::M:\n                       MMM:::::::::::::::M:\n                       MMM::::::::::::::::M\n                       MMM::::::::::::::::M\n                       MMM::::::::::::::::Mm\n                        MM::::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                         MM::::::::::::::MMM\n                         MMM:::::::::::::MM\n                         MMM:::::::::::::MM\n                         MMM::::::::::::MM\n                          MM::::::::::::MM\n                          MM::::::::::::MM\n                          MM:::::::::::MM\n                          MMM::::::::::MM\n                          MMM::::::::::MM\n                           MM:::::::::MM\n                           MMM::::::::MM\n                           MMM::::::::MM\n                            MM::::::::MM\n                            MMM::::::MM\n                            MMM::::::MM\n                             MM::::::MM\n                             MM::::::MM\n                              MM:::::MM\n                              MM:::::MM:\n                              MM:::::M:M\n                              MM:::::M:M\n                              :M::::::M:\n                             M:M:::::::M\n                            M:::M::::::M\n                           M::::M::::::M\n                          M:::::M:::::::M\n                         M::::::MM:::::::M\n                         M:::::::M::::::::M\n                         M;:;::::M:::::::::M\n                         M:m:;:::M::::::::::M\n                         MM:m:m::M::::::::;:M\n                          MM:m::MM:::::::;:;M\n                           MM::MMM::::::;:m:M\n                            MMMM MM::::m:m:MM\n                                  MM::::m:MM\n                                   MM::::MM\n                                    MM::MM", 1);

	// BOSS Text
	_driver.moveTo(580, 300);
	_driver.drawString("This is the", 6);
	_driver.moveTo(650, 470);
	_driver.drawString("BOSS", 10);
	_driver.moveTo(650, 530);
	_driver.drawString("Project", 6);
}

DisplayService::~DisplayService() {}

void DisplayService::executeMessage(Message* message)  {
	int* params = message->getParams();
    int response[] = {false};
    if (checkScreenRights(message->getTaskId())) {
    	DisplayServiceCommand command = (DisplayServiceCommand)params[0];
        response[0] = true;
    	switch (command) {
    		case SERVICE_SET_COLOR:
    			_driver.setColor(params[1]);
    			break;
    			
    		case SERVICE_MOVE_TO:
    			_driver.moveTo(params[1], params[2]);
    			break;
    			
    		case SERVICE_DRAW_PIXEL:
    			_driver.drawPixel();
    			break;
    			
    		case SERVICE_DRAW_RECT:
    			_driver.drawRect(params[1], params[2]);
    			break;
    			
    		case SERVICE_DRAW_CHAR:
    			_driver.drawChar(params[1], params[2]);
    			break;
    			
    		case SERVICE_DRAW_STRING:
    			_driver.drawString(((const char*)params + 2), params[1]);
    			break;
            case SERVICE_SWITCH_TASK:
                if ((message->getTaskId() == -1) && (params >= 0)) {
                    changeTo(params[1]);
                }
    	}
    } else {
        int* position = _driver.getPosition();
        int pos[] = {position[0], position[1]};
        unsigned int colour = _driver.getColour();
        
//        _driver.setColor(0x0);
//        _driver.moveTo(30, 48);
//        _driver.drawRect(153, 30);
        _driver.setColor(0xFFFFFF);
        _driver.moveTo(30, 60);
        char* infoString = "Task ";
        _driver.drawString(infoString, 2);
        
        _driver.moveTo(90, 60);
        char infoCharArray[] = {(char)(message->getTaskId() + (unsigned int)'0'), '\0'};
        if (infoCharArray[0] > 255) {
            infoCharArray[0] -= 256;
        }
        _driver.drawString(infoCharArray, 2);
        
        infoString = " wants the screen";
        _driver.moveTo(102, 60);
        _driver.drawString(infoString, 2);
        
        _driver.moveTo(pos[0], pos[1]);
        _driver.restoreColour(colour);
    }
    if (message->getTaskId() >= 0) {
        writeResponse(message->getTaskId(), 1, response);
    }
}

bool DisplayService::checkScreenRights(int taskId) {
    bool isCurrentTask = false;
    if (taskId < 0) {
        isCurrentTask = true;
    } else {
        if (_currentTaskId < 0) {
            changeTo(taskId);
            isCurrentTask = true;
        } else if (_currentTaskId == taskId) {
            isCurrentTask = true;
        }
    }
    return isCurrentTask;
}

void DisplayService::changeTo(int taskId) {
    std::memset(FBADDR, 0x0, 1024*768*4);
    _currentTaskId = taskId;
    
    int* position = _driver.getPosition();
    int pos[] = {position[0], position[1]};
    unsigned int colour = _driver.getColour();
    
//    _driver.setColor(0x0);
//    _driver.moveTo(994, 48);
//    _driver.drawRect(5, 30);
    _driver.setColor(0xFFFFFF);
    _driver.moveTo(994, 60);
    char infoCharArray[] = {(char)(taskId + (unsigned int)'0'), '\0'};
    if (infoCharArray[0] > 255) {
        infoCharArray[0] -= 256;
    }
    _driver.drawString(infoCharArray, 2);
    
    _driver.moveTo(pos[0], pos[1]);
    _driver.restoreColour(colour);

}
