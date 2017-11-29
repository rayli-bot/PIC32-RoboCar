#include <p32mx250f128d.h>
#include "WheelCounter.h"


Counter::Counter(void) { counts = last = 0; }
void Counter::sample(short i) {
	short d = i - last;
	counts <<= 4;			// shift out old data
	counts |= d;			// record new data
	last = i;
}
int Counter::getCount(void) {		// sum up data in "counts"
	int sum = 0, temp = counts;
	sum += temp & 15;
	temp >>= 4;
	return sum;
}
