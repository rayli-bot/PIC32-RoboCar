#include <p32mx250f128d.h>
#include "motor.h"
#include "control_wheel.h"

/*
Type :
  1 : Left
  2 : Right
  3 : Straight
 */
void ControlWheel::init(int x, int p, int m){
	TMR2=0;
	TMR4=0;
	type=x;
	pwm=p;
	max=m;
}

void ControlWheel::run(){
	switch(type){
	case 1:
		if(TMR4<max){
			setPWM_B(pwm);
			break;
		}
		else{
			setPWM_B(0);
			break;
		}
	case 2:
		if(TMR2<max){
			setPWM_A(pwm);
			break;
		}
		else{
			setPWM_A(0);
			break;
		}
	case 3:
		if(TMR2<max && TMR4<max){
			LATAINV=1;
			setPWM_A(pwm);setPWM_B(pwm);break;
		}
		else{
			setPWM_A(0);setPWM_B(0);break;
		}
	default:
		break;
	}
}
