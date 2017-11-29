
#include <p32mx250f128d.h>
#include "PID.h"
#include "queue.h"
#include "state.h"
#include "WheelCounter.h"
#include "VTimer.h"
#include "control_wheel.h"
//#include "state.h"
//#include "functions.h"

// Public functions for other modules

VTimer testtime;

extern "C"
{
void __attribute__ ((interrupt)) t3ISR(void) {
	procedureSwitch(StatusListener());
	LATCSET = 1<<9;				// turn on LED
	TMR5 = 0;					// reset delay timer
	T5CONbits.ON = 1;
	IEC0bits.T5IE = 1;


	IFS0bits.T3IF = 0;
}
} // ISRs


