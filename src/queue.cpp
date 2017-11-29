#include <p32mx250f128d.h>
#include "queue.h"
#include "PID.h"
#include "Decode.h"
#include "state.h"
#include "compute.h"
#include "VTimer.h"
#include "control_wheel.h"
#include "WheelCounter.h"
#include "motor.h"
#include "queue.h"

int target= 80 >> 2 ;  // 139.2 / 2^3 = 17.4
int rt, lt,control_track,changeFlag,motorcount;

PID pid_speed(1000,0,0,0), pid_track(150,0.4,0.1,80);
Counter left,right;
VTimer v_timer;
VTimer p_timer;
Counter w_count;
ControlWheel c_wheel;

unsigned getLeft(void) { return left.getCount(); }
unsigned getRight(void) { return right.getCount(); }
void sample(void){ right.sample(TMR2);left.sample(TMR4); }


void Move(int Error,int dir){		//dir=0 : Forward; dir=1 : Backward;
	rt = right.getCount();
	lt = left.getCount();
	int track=Error;
	int control_speed = pid_speed.control(rt + lt, target);
	if (++motorcount== 8) {							// 25 Hz For Wheel Counter Sampling
		motorcount=0;
		right.sample(TMR2);
		left.sample(TMR4);
		control_track = pid_track.control(rt - lt, track);
	}
	if(!dir){
	setPWM_A(bound(control_speed + control_track));
	setPWM_B(bound(control_speed - control_track));
	}else{
		setPWM_A(-bound(control_speed - control_track));
		setPWM_B(-bound(control_speed + control_track));
	}
}

void procedure1(){
	if(changeFlag){ v_timer.setDelay(400); }
	else{
		c_wheel.run();
	}
	if(!v_timer.tick()){ changeFlag=0; c_wheel.init(3,35000,100); }
}
void procedure2(){
	static int backFlag;
	if(changeFlag){ v_timer.setDelay(400);}
	else{
		if(!overhead(25) && !backFlag) Move(-ShootError(656,216,70),0);
		else if(overhead(25) && !backFlag) { backFlag=1; p_timer.setDelay(800); }
		if(backFlag) Move(-ShootError(656,216,-100),1);
		if(!p_timer.tick()) backFlag=0;
	}
	if(!v_timer.tick()){ changeFlag=0;}
}
void procedure3(){		//Just Backward
	if(changeFlag){ changeFlag=0; }
	Move(-PointError(519,91),1);
}
void procedure4(){
	//Move to shooting point
	if(changeFlag){ changeFlag=0; }
	Move(-PointError(873,75),1);
}
void procedure5(){
	//Shoot from Launch 1
	static int backFlag;
	if(changeFlag){ v_timer.setDelay(200);}
	else{
		if(CheckDistance(getX(0),getY(0),getX(3),getY(3),75)){
			if(!overhead(-20) && !backFlag) Move(-ShootError(271,215,70),0);
			else if(overhead(-20)&& !backFlag){ backFlag=1; p_timer.setDelay(600); }
			if(backFlag) Move(-ShootError(271,215,-100),1);
			if(p_timer.tick()) backFlag=0;
			c_wheel.init(3,40000,60);
		}
		else{
			c_wheel.run();
		}
	}
	if(!v_timer.tick()){ changeFlag=0;}
}
void procedure6A(){
	// Car 1 Go to Start Point
	if(changeFlag){ changeFlag=0; }
	Move(-PointError(100,100),0);
}
void procedure6B(){
	// Car 2 touch ball
	if(changeFlag){ changeFlag=0; }
	if(CheckDistance(getX(1),getY(1),getX(3),getY(3),100)){
		Move(-ShootError(656,216,70),0);
	}
	else { setPWM_A(0);setPWM_B(0); }
}
void procedure7(){
	// Car 2 backward with slope
	if(changeFlag){ v_timer.setDelay(500);}
	else{
		Move(-ShootError(656,216,-100),1);
	}
	if(!v_timer.tick()){ changeFlag=0;}
}
void procedure8(){
	// Car 2 Shoot
	static int backFlag;
	if(changeFlag){ v_timer.setDelay(200);}
	else{
		if(CheckDistance(getX(1),getY(1),getX(3),getY(3),75)){
			if(!overhead(20) && !backFlag) Move(-ShootError(656,216,70),0);
			else if(overhead(20)&& !backFlag){ backFlag=1; p_timer.setDelay(600); }
			if(backFlag) Move(-ShootError(656,216,-100),1);
			if(p_timer.tick()) backFlag=0;
			c_wheel.init(3,40000,60);
		}
		else{
			c_wheel.run();
		}
	}
	if(!v_timer.tick()){ changeFlag=0;}
}
void procedure9(){
	// Car 3 go catch ball
	if(changeFlag){ changeFlag=0; }
	Move(PointError(getX(3),getY(3)),0);
}
void procedure10(){
	if(changeFlag){ v_timer.setDelay(200); changeFlag=0;}
	if(!v_timer.tick()){
		LATAINV=1;
		v_timer.setDelay(200);
	}
}

void stationary(){ setPWM_A(0);setPWM_B(0); }

void procedureSwitch(int state){
	int ID=getID();
	if(state<0) { state=-state; changeFlag=1; }
	switch(state){
	case 1:
		if(!ID){procedure1();break;}
		else {stationary();break;}
	case 2:
		if(!ID){procedure2();break;}
		else {stationary();break;}
	case 3:
		if(!ID){procedure3();break;}
		else {stationary();break;}
	case 4:
		if(!ID){procedure4();break;}
		else{stationary();break;}
	case 5:
		if(!ID){procedure5();break;}
		else{stationary();break;}
	case 6:
		if(!ID){procedure6A();break;}
		else if(ID==1){procedure6B();break;}
		else{stationary();break;}
	case 7:
		if(ID==1){procedure7();break;}
		else{stationary();break;}
	case 8:
		if(ID==1){procedure8();break;}
		else{stationary();break;}
	case 9:
		if(ID==2){procedure9();break;}
		else{stationary();break;}
	case 10:
		procedure10();break;
	default: break;
	}
}


