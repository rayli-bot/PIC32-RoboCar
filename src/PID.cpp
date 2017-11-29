#include <p32mx250f128d.h>
#include "PID.h"

PID::PID(int p, int in, int id, int d) {
	P = p;
	In = in; Id = id;	// I break "I" into two parts to avoid decimal
	D = d;
	acc = last = 0;
}

void PID::reset(void) {acc = last = 0;}


double PID::control(int x, int target) {
	int error = x - target;
	int diff = x - last;
	last = x;
	acc += error;
	if (acc > 2000000000) acc = 2000000000;
	if (acc < -2000000000) acc = -2000000000;
	return - P * error - In * (acc >> Id) - D * diff;
}


