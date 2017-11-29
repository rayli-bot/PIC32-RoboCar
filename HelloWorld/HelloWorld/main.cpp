/*
 * main.cpp
 *
 *  Created on: 12 Nov, 2016
 *      Author: sylam
 */

#include <p32mx250f128d.h>

extern "C" { // function provided by cdc stack

void USBDeviceInit(void);
void USBDeviceTasks(void);
void CDCDeviceTasks(void);
void putsUSBUSART(char *data);	// including trailing zero

} //extern "C"

extern "C"	// handlers required by cdc stack
{
void CDCRxChars(char *c, int length) {}		// you got a message from cdc
void CDCTxReadyNotify(void) {}				// you may send message to cdc
}//extern


void USBTasks(void) {
	USBDeviceTasks();
	U1OTGIR = 0xFF;
	IFS1bits.USBIF = 0;
	CDCDeviceTasks();
}

int t3FLAG;

int main(void) {
	USBDeviceInit();
	while (1) {
		USBTasks();
		if (t3FLAG) {
			putsUSBUSART((char*)"Hello World!\r\n");
			t3FLAG = 0;			// Watch out! Here lies a bug.
		}
	}
}

extern "C" void __attribute__ ((interrupt)) t3ISR(void) {
	static int count;
	if (++count == 800) {	// 2 second
		count = 0;
		t3FLAG = 1;			// cannot print string at interrupt leve
							// so set a flag and let main() print the message
		LATAINV=1;			// toggle LED
	}
	IFS0bits.T3IF = 0;
}
