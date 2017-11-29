#include <p32mx250f128d.h>
#include "Decode.h"
#include "state.h"
#include "compute.h"
#define ID 0

int Status;

int getID(){ return ID;}

void initStatus(){
	Status=0;
}

int StatusListener(){
	if(getX(0)<205 && getX(3)<205 && getY(0)<140 && getY(3)<140){
		if(Status==1) return Status;
		else{
			Status=1;
			return -Status;
		}
	}
	else if(Status==1 && getX(3)>205){		//Push Ball
		if(Status==2) return Status;
		else{
			Status=2;
			return -Status;
		}
	}
	else if(Status==2 && getX(3)>620){		//Car 1 Backward
		if(Status==3) return Status;
		else{
			Status=3;
			return -Status;
		}
	}
	else if(Status==3 && getX(0)<550){		//Car 1 go to Shooting Point
		if(Status==4) return Status;
		else{
			Status=4;
			return -Status;
		}
	}
	else if(Status==4 && getX(0)>810){		//Car 1 Start Shooting
		if(Status==5) return Status;
		else{
			Status=5;
			return -Status;
		}
	}
	else if(Status==5 && getX(3)<500){		//Car 1 go back Starting point; Car 2 touch ball
		if(Status==6) return Status;
		else{
			Status=6;
			return -Status;
		}
	}
	else if(Status==6 && !CheckDistance(getX(1),getY(1),getX(3),getY(3),100)){	//Car 2 Backward
		if(Status==7) return Status;
		else{
			Status=7;
			return -Status;
		}
	}
	else if(Status==7 && getX(1)<200){		//Car 2 Shoot Ball
		if(Status==8) return Status;
		else{
			Status=8;
			return -Status;
		}
	}
	else if(Status==8 && getX(3)>500){		//Car 3 Catch Ball
		if(Status==9) return Status;
		else{
			Status=9;
			return -Status;
		}
	}
	else if(Status==9 && !CheckDistance(getX(2),getY(2),getX(3),getY(3),60)){	//Finished
		if(Status==10) return Status;
		else{
			Status=10;
			return -Status;
		}
	}
}
