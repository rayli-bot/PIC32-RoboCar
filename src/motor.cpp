#include <p32mx250f128d.h>
#include "motor.h"


#define PERIOD 49999
#define APHASE 2		// RC1
#define BPHASE 4		// RC2


void setPWM_A(int w){
	if(w<0){
		w=-w;
		LATCSET = APHASE;
	} else LATCCLR = APHASE;
	OC1RS = w > PERIOD ? PERIOD : w;
}

void setPWM_B(int w){
	if(w<0){
		w=-w;
		LATCSET = BPHASE;
	} else LATCCLR = BPHASE;
	OC2RS = w > PERIOD ? PERIOD : w;
}

unsigned short bound(int control) {
	if (control < 0) return 0;
	return control > PERIOD ? PERIOD : control;
}
