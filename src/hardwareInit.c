
#include <p32mx250f128d.h>

void hardwareInit(void) {

	SYSKEY = 0;				// ensure OSCCON is locked
	SYSKEY = 0xAA996655;	// unlock sequence
	SYSKEY = 0x556699AA;
	CFGCONbits.IOLOCK = 0;	// allow write

	//PPS CONFIGURATION
	T2CKR = 0b0001;			// RB3 - T2CK (wheel counter)
	T4CKR = 0b0100;			// RB2 - T4CK (wheel counter)
	RPB4R = RPA8R = 0b101;		// OC1 AENABL  OC2 BENBL - MOTOR (DRV8834PWP)
	U2RXR = 0b0111;			// RA9 - U2RX
	RPC4R = 0b0010;			// RC4 - U2TX

	CFGCONbits.IOLOCK = 1;	// forbidden write
	SYSKEY = 0;				// relock

	//GPIO CONFIGURATION
	TRISASET = 2;							// RA1: tact switch
	LATACLR = TRISACLR = 1;					// RA0: LED indicator
    ANSELBCLR = 0b1100;			// RB3 & RB2 - wheel counters
    LATCCLR = TRISCCLR =  0b111; // RC2, RC1, RC0 - MOTOR(DRV8834PWP)

    //MISCELLANEOUS
	U2BRG = 10;					// baud rate 115200
	U2STASET = 0x1400;			// URXEN & UTXEN

	OC1CON = OC2CON = 0x800e;	//timer3, PWM w/o fault
	PR3 = 49999;				//timer3 = 400 Hz (2.5 ms)
	T3CON = 0x8000;				//timer3, no prescaler

	// wheel counter
	PR2 = PR4 = 0xffff;
	T2CON = T4CON = 0x8002;		//External clock, no prescaler

	//ENABLE INTERRUPTS
	IPC3bits.T3IP = 1;			// timer3
	IEC0bits.T3IE = 1;
	IPC9bits.U2IP = 1;			// uart2
	IEC1bits.U2RXIE = 1;

	//TURN ON PERIPHERAL MODULES
	U2MODEbits.ON = 1;			// turn on uart engine
}
