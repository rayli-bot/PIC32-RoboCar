#include <p32mx250f128d.h>
#include "VTimer.h"


VTimer::VTimer(){ count=period=0;}
void VTimer::setDelay(int x){ count=0;period=x;}
int VTimer::tick(){ count++; if((period>0 && count>period) || count==0) { period=0; count=0; return 0;} else return 1;}

