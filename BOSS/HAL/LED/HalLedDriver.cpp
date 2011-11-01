#include "HalLedDriver.h"

#include "../gpio.h"

#define LED1_REG 21
#define LED2_REG 22

HalLedDriver::HalLedDriver(): m_led1(GPIO_OE_GPIO5, GPIO_DATAOUT_GPIO5, GPIO_SETDATAOUT_GPIO5, GPIO_CLEARDATAOUT_GPIO5, LED1_REG), m_led2(GPIO_OE_GPIO5, GPIO_DATAOUT_GPIO5, GPIO_SETDATAOUT_GPIO5, GPIO_CLEARDATAOUT_GPIO5, LED2_REG) {
}

HalLedDriver::~HalLedDriver() {
}

LEDClass HalLedDriver::ledClassForEnum(LED ledEnum) {
	switch (ledEnum) {
		case LED1:
			return m_led1;
		case LED2:
			return m_led2;
		default:
			return m_led1;
	}
}

void HalLedDriver::init() {
}
void HalLedDriver::ledOn(LED led) {
	ledClassForEnum(led).switchOn();
}

void HalLedDriver::ledOff(LED led) {
	ledClassForEnum(led).switchOff();
}
void HalLedDriver::toggle(LED led) {
	ledClassForEnum(led).toggle();
}
bool HalLedDriver::isOn(LED led) {
	return ledClassForEnum(led).isOn();
}
