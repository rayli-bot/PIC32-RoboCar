
// Packet P : Ball Orange Red Blue

#include <p32mx250f128d.h>
#include "Decode.h"

int h2d(char d, int t){
	int temp=0,m=4;
	if(d>='0' && d <='9') temp = ( d & 15 );
	else if ( d>='a' && d <= 'f' ) temp = (( d & 15 ) + 9 );
	m*=t;
	return temp << m;
}



int location::getX(){ return this->x; }
int location::getY(){ return this->y; }
int location::getPrevX(){ return this->prevX; }
int location::getPrevY(){ return this->prevY; }
void location::setX(char *a){ for(int i=0;i<3;i++) this->x+=h2d(a[i],2-i); }
void location::setY(char *a){for(int i=0;i<3;i++) this->y+=h2d(a[i],2-i);}
void location::empty(){this->prevX=x;this->prevY=y;this->x=this->y=0;}


int getPrevX(int a){
	switch(a){
		case 0: return CAR[a].getPrevX();break;
		case 1: return CAR[a].getPrevX();break;
		case 2: return CAR[a].getPrevX();break;
		case 3: return BALL.getPrevX();break;
		case 4: return START.getPrevX();break;
		case 5: return GOAL.getPrevX();break;
		default: return 0;break;
	}
}
int getPrevY(int a){
	switch(a){
		case 0: return CAR[a].getPrevY();break;
		case 1: return CAR[a].getPrevY();break;
		case 2: return CAR[a].getPrevY();break;
		case 3: return BALL.getPrevY();break;
		case 4: return START.getPrevY();break;
		case 5: return GOAL.getPrevY();break;
		default: return 0;break;
	}
}
int getX(int a){
	switch(a){
		case 0: return CAR[a].getX();break;
		case 1: return CAR[a].getX();break;
		case 2: return CAR[a].getX();break;
		case 3: return BALL.getX();break;
		case 4: return START.getX();break;
		case 5: return GOAL.getX();break;
		default: return 0;break;
	}
}
int getY(int a){
	switch(a){
		case 0: return CAR[a].getY();break;
		case 1: return CAR[a].getY();break;
		case 2: return CAR[a].getY();break;
		case 3: return BALL.getY();break;
		case 4: return START.getY();break;
		case 5: return GOAL.getY();break;
		default: return 0;break;
	}
}
void setLocation(int a, char *b, char *c){
	switch(a){
		case 1: CAR[a-1].setX(b);CAR[a-1].setY(c);break;
		case 2: CAR[a-1].setX(b);CAR[a-1].setY(c);break;
		case 3: CAR[a-1].setX(b);CAR[a-1].setY(c);break;
		case 0: BALL.setX(b);BALL.setY(c);break;
		case 4: START.setX(b);START.setY(c);break;
		case 5: GOAL.setX(b);GOAL.setY(c);break;
		default: break;
	}
}
void empty(int a){
	switch(a){
		case 0: CAR[a].empty();break;
		case 1: CAR[a].empty();break;
		case 2: CAR[a].empty();break;
		case 3: BALL.empty();break;
		case 4: START.empty();break;
		case 5: GOAL.empty();break;
		default: break;
	}
}


// Ball=4, Car= 0~2, Start=5, Goal=6
void Raw2Locate(char *d){
	char x[4][3],y[4][3];			// Four for demo 5 three CAR and BALL
	int ptr=4;
	if(d[0]=='P'){
		char checksum=d[ptr];
		for(int i=ptr+1;i<ptr+24;i++){
			checksum ^= d[i];
		}
		char AH=checksum >> 4;
		AH = AH<10 ? AH+'0' : AH+'a'-10;
		char AL=checksum & 15;
		AL = AL<10 ? AL+'0' : AL+'a'-10;
		if(AH==d[ptr+24] && AL==d[ptr+25]){				//checksum
			for(int i=0;i<4;i++) empty(i);
			for(int i=0;i<3;i++) {

				x[0][i]=d[ptr];			//Ball
				y[0][i]=d[ptr+3];
				x[1][i]=d[ptr+6];		//Car 1
				y[1][i]=d[ptr+9];
				x[2][i]=d[ptr+12];		//Car 2
				y[2][i]=d[ptr+15];
				x[3][i]=d[ptr+18];		//Car 3
				y[3][i]=d[ptr+21];
				ptr++;
			}
			for(int i=0;i<4;i++) setLocation(i,x[i],y[i]);
		}
	}
	else if(d[0]=='A'){
		char checksum=d[ptr];
		for(int i=ptr+1;i<ptr+12;i++){
			checksum ^= d[i];
		}
		char AH=checksum >> 4;
		AH = AH<10 ? AH+'0' : AH+'a'-10;
		char AL=checksum & 15;
		AL = AL<10 ? AL+'0' : AL+'a'-10;
		if(AH==d[ptr+12] && AL==d[ptr+13]){				//checksum
			empty(4);empty(5);
			for(int i=0;i<3;i++) {
				x[0][i]=d[ptr];			//Goal
				y[0][i]=d[ptr+3];
				x[1][i]=d[ptr+6];		//Start
				y[1][i]=d[ptr+9];
				ptr++;
			}
			setLocation(4,x[1],y[1]);
			setLocation(5,x[0],y[0]);
		}
	}
}

