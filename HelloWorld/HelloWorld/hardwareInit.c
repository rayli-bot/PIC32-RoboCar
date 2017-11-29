/*
 * hardwareInit.c
 *
 *  Created on: 12 Nov, 2016
 *      Author: sylam
 */

#include <p32mx250f128d.h>

void hardwareInit(void) {

	SYSKEY = 0;				// ensure OSCCON is locked
	SYSKEY = 0xAA996655;	// unlock sequence
	SYSKEY = 0x556699AA;
	CFGCONbits.IOLOCK = 0;	// allow write

	//PPS CONFIGURATION

	CFGCONbits.IOLOCK = 1;	// forbidden write
	SYSKEY = 0;				// relock

	//GPIO CONFIGURATION
	TRISACLR = LATACLR = 1;		// RA0: LED

    //MISCELLANEOUS
	T3CON = 0x8000;				//timer3, no prescaler
	PR3 = 49999;				//timer3 = 400 Hz

	//ENABLE INTERRUPTS
	IPC3bits.T3IP = 1;			//timer3
	IEC0bits.T3IE = 1;

	//TURN ON PERIPHERAL MODULES
}

