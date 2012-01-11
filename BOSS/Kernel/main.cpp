#include "Kernel/Kernel.h"
#include "API/systemCalls.h"
#include "HAL/Audio/audio.h"
#include "Loader/TasksHex/TestBytes.h"

#include "Video/graphics.h"
#include "Video/video.h"

void leerlauf(void)  {
	while(1);
}

int printBOSS();

int main() {
	_disable_interrupts();

	// Audio Test -> "berühr dass, und deine Zahnbürste fährt morgens ins Leere!"
	Audio* audio = new Audio();
	audio->playSample();
	delete audio;

	printBOSS();

	Kernel* kernel = new Kernel();

	// Dummy Task
	Task* leerlaufTask = kernel->getTaskManager()->create("leerlauf\0", false, 0);
	leerlaufTask->codeLocation = (address)((void*)leerlauf);
	leerlaufTask->pageCount = 1;

	// Start Services
	kernel->getServiceManager()->startServices();

	// Start Test-Task to toggle LED's
	Task* task = kernel->getTaskManager()->create("test", false);
	TestBytes tb;
	kernel->getLoader()->loadTaskCode(task, tb.getCodeBytes());

	// Init
	_enable_interrupts();
	asm("\t CPS 0x10");
	leerlauf();

	while(1);
}


#define WIDTH 1024
#define HEIGHT 768
#define RES_WIDTH 1024
#define RES_HEIGHT 768
#define FBADDR ((char *)0x83000000)

int printBOSS()  {

//	_enable_interrupts();

	int i = 0;
	int x, y, u;
	RastPort *rp;

	video_init(); // --> video.c
	rp = graphics_init(FBADDR, RES_WIDTH, RES_HEIGHT, BM_RGB16); // graphics.c
	omap_attach_framebuffer(0, rp->drawable.bitmap); // --> video.c

	moveTo(rp, 0, 0);
	setColour(rp, 0xFF007F);
	drawRect(rp, WIDTH, HEIGHT);

	int l = 0;
	setColour(rp, 0x00000000);
//	while (1)  {
//		int j = 0;
//		while (j < 80000) {
//			j++;
//		}
//		moveTo(rp, 20, 300*l);
//		drawString(rp, "Gugus!0123445 6 7 \n test 7 8 8", 4);
//		l++;
//	}

	moveTo(rp, 20, 20);
	drawString(rp, "                         8888  8888888\n                  888888888888888888888888\n               8888:::8888888888888888888888888\n             8888::::::8888888888888888888888888888\n            88::::::::888:::8888888888888888888888888\n          88888888::::8:::::::::::88888888888888888888\n        888 8::888888::::::::::::::::::88888888888   888\n           88::::88888888::::m::::::::::88888888888    8\n         888888888888888888:M:::::::::::8888888888888\n        88888888888888888888::::::::::::M88888888888888\n        8888888888888888888888:::::::::M8888888888888888\n         8888888888888888888888:::::::M888888888888888888\n        8888888888888888::88888::::::M88888888888888888888\n      88888888888888888:::88888:::::M888888888888888   8888\n     88888888888888888:::88888::::M::;o*M*o;888888888    88\n    88888888888888888:::8888:::::M:::::::::::88888888    8\n   88888888888888888::::88::::::M:;:::::::::::888888888     \n  8888888888888888888:::8::::::M::aAa::::::::M8888888888       8\n  88   8888888888::88::::8::::M:::::::::::::888888888888888 8888\n 88  88888888888:::8:::::::::M::::::::::;::88:88888888888888888\n 8  8888888888888:::::::::::M::\"@@@@@@@\"::::8w8888888888888888\n  88888888888:888::::::::::M:::::\"@a@\":::::M8i888888888888888\n 8888888888::::88:::::::::M88:::::::::::::M88z88888888888888888 \n8888888888:::::8:::::::::M88888:::::::::MM888!888888888888888888\n888888888:::::8:::::::::M8888888MAmmmAMVMM888*88888888   88888888\n888888 M:::::::::::::::M888888888:::::::MM88888888888888   8888888\n8888   M::::::::::::::M88888888888::::::MM888888888888888    88888\n 888   M:::::::::::::M8888888888888M:::::mM888888888888888    8888\n  888  M::::::::::::M8888:888888888888::::m::Mm88888 888888   8888\n   88  M::::::::::::8888:88888888888888888::::::Mm8   88888   888\n   88  M::::::::::8888M::88888::888888888888:::::::Mm88888    88\n   8   MM::::::::8888M:::8888:::::888888888888::::::::Mm8     4\n       8M:::::::8888M:::::888:::::::88:::8888888::::::::Mm    2\n      88MM:::::8888M:::::::88::::::::8:::::888888:::M:::::M\n     8888M:::::888MM::::::::8:::::::::::M::::8888::::M::::M\n    88888M:::::88:M::::::::::8:::::::::::M:::8888::::::M::M\n   88 888MM:::888:M:::::::::::::::::::::::M:8888:::::::::M:\n   8 88888M:::88::M:::::::::::::::::::::::MM:88::::::::::::M\n     88888M:::88::M::::::::::*88*::::::::::M:88::::::::::::::M             \n    888888M:::88::M:::::::::88@@88:::::::::M::88::::::::::::::M\n    888888MM::88::MM::::::::88@@88:::::::::M:::8::::::::::::::*8\n    88888  M:::8::MM:::::::::*88*::::::::::M:::::::::::::::::88@@\n    8888   MM::::::MM:::::::::::::::::::::MM:::::::::::::::::88@@\n     888    M:::::::MM:::::::::::::::::::MM::M::::::::::::::::*8\n     888    MM:::::::MMM::::::::::::::::MM:::MM:::::::::::::::M\n      88     M::::::::MMMM:::::::::::MMMM:::::MM::::::::::::MM\n       88    MM:::::::::MMMMMMMMMMMMMMM::::::::MMM::::::::MMM\n        88    MM::::::::::::MMMMMMM::::::::::::::MMMMMMMMMM\n         88   8MM::::::::::::::::::::::::::::::::::MMMMMM\n          8   88MM::::::::::::::::::::::M:::M::::::::MM\n              888MM::::::::::::::::::MM::::::MM::::::MM\n             88888MM:::::::::::::::MMM:::::::mM:::::MM\n             888888MM:::::::::::::MMM:::::::::MMM:::M\n            88888888MM:::::::::::MMM:::::::::::MM:::M\n           88 8888888M:::::::::MMM::::::::::::::M:::M\n           8  888888 M:::::::MM:::::::::::::::::M:::M:\n              888888 M::::::M:::::::::::::::::::M:::MM\n             888888  M:::::M::::::::::::::::::::::::M:M\n             888888  M:::::M:::::::::@::::::::::::::M::M\n             88888   M::::::::::::::@@:::::::::::::::M::M\n            88888   M::::::::::::::@@@::::::::::::::::M::M\n           88888   M:::::::::::::::@@::::::::::::::::::M::M\n          88888   M:::::m::::::::::@::::::::::Mm:::::::M:::M\n          8888   M:::::M:::::::::::::::::::::::MM:::::::M:::M\n         8888   M:::::M:::::::::::::::::::::::MMM::::::::M:::M\n        888    M:::::Mm::::::::::::::::::::::MMM:::::::::M::::M\n      8888    MM::::Mm:::::::::::::::::::::MMMM:::::::::m::m:::M\n     888      M:::::M::::::::::::::::::::MMM::::::::::::M::mm:::M\n  8888       MM:::::::::::::::::::::::::MM:::::::::::::mM::MM:::M:\n             M:::::::::::::::::::::::::M:::::::::::::::mM::MM:::Mm\n            MM::::::m:::::::::::::::::::::::::::::::::::M::MM:::MM\n            M::::::::M:::::::::::::::::::::::::::::::::::M::M:::MM         \n           MM:::::::::M:::::::::::::M:::::::::::::::::::::M:M:::MM\n           M:::::::::::M88:::::::::M:::::::::::::::::::::::MM::MMM\n           M::::::::::::8888888888M::::::::::::::::::::::::MM::MM\n           M:::::::::::::88888888M:::::::::::::::::::::::::M::MM\n           M::::::::::::::888888M:::::::::::::::::::::::::M::MM\n           M:::::::::::::::88888M:::::::::::::::::::::::::M:MM\n           M:::::::::::::::::88M::::::::::::::::::::::::::MMM\n           M:::::::::::::::::::M::::::::::::::::::::::::::MMM\n           MM:::::::::::::::::M::::::::::::::::::::::::::MMM\n            M:::::::::::::::::M::::::::::::::::::::::::::MMM\n            MM:::::::::::::::M::::::::::::::::::::::::::MMM\n             M:::::::::::::::M:::::::::::::::::::::::::MMM\n             MM:::::::::::::M:::::::::::::::::::::::::MMM\n              M:::::::::::::M::::::::::::::::::::::::MMM\n              MM:::::::::::M::::::::::::::::::::::::MMM\n               M:::::::::::M:::::::::::::::::::::::MMM  \n               MM:::::::::M:::::::::::::::::::::::MMM\n                M:::::::::M::::::::::::::::::::::MMM\n                MM:::::::M::::::::::::::::::::::MMM\n                 MM::::::M:::::::::::::::::::::MMM\n                 MM:::::M:::::::::::::::::::::MMM\n                  MM::::M::::::::::::::::::::MMM\n                  MM:::M::::::::::::::::::::MMM\n                   MM::M:::::::::::::::::::MMM\n                   MM:M:::::::::::::::::::MMM\n                    MMM::::::::::::::::::MMM\n                    MM::::::::::::::::::MMM\n                     M:::::::::::::::::MMM\n                    MM::::::::::::::::MMM\n                    MM:::::::::::::::MMM\n                    MM::::M:::::::::MMM:\n                    mMM::::MM:::::::MMMM\n                     MMM:::::::::::MMM:M\n                     mMM:::M:::::::M:M:M\n                      MM::MMMM:::::::M:M\n                      MM::MMM::::::::M:M\n                      mMM::MM::::::::M:M\n                       MM::MM:::::::::M:M\n                       MM::MM::::::::::M:m\n                       MM:::M:::::::::::MM\n                       MMM:::::::::::::::M:\n                       MMM:::::::::::::::M:\n                       MMM::::::::::::::::M\n                       MMM::::::::::::::::M\n                       MMM::::::::::::::::Mm\n                        MM::::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                        MMM:::::::::::::::MM\n                         MM::::::::::::::MMM\n                         MMM:::::::::::::MM\n                         MMM:::::::::::::MM\n                         MMM::::::::::::MM\n                          MM::::::::::::MM\n                          MM::::::::::::MM\n                          MM:::::::::::MM\n                          MMM::::::::::MM\n                          MMM::::::::::MM\n                           MM:::::::::MM\n                           MMM::::::::MM\n                           MMM::::::::MM\n                            MM::::::::MM\n                            MMM::::::MM\n                            MMM::::::MM\n                             MM::::::MM\n                             MM::::::MM\n                              MM:::::MM\n                              MM:::::MM:\n                              MM:::::M:M\n                              MM:::::M:M\n                              :M::::::M:\n                             M:M:::::::M\n                            M:::M::::::M\n                           M::::M::::::M\n                          M:::::M:::::::M\n                         M::::::MM:::::::M\n                         M:::::::M::::::::M\n                         M;:;::::M:::::::::M\n                         M:m:;:::M::::::::::M\n                         MM:m:m::M::::::::;:M\n                          MM:m::MM:::::::;:;M\n                           MM::MMM::::::;:m:M\n                            MMMM MM::::m:m:MM\n                                  MM::::m:MM\n                                   MM::::MM\n                                    MM::MM", 1);

	moveTo(rp, 580, 300);
	drawString(rp, "This is the", 6);
	moveTo(rp, 650, 470);
	drawString(rp, "BOSS", 10);
	moveTo(rp, 650, 530);
	drawString(rp, "Project", 6);

//	while(1);
}
