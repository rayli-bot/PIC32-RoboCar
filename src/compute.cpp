#include <p32mx250f128d.h>
#include "compute.h"
#include "Decode.h"
#include "state.h"

int ID=getID();

int Angle(int x1,int y1,int x2,int y2){
    int comX = x1 && x2 ? 1 : 0;            //0001
    int comY = y1 && y2 ? 2 : 0;            //0010
    int com2X = x1 > x2 ? 4 : 0;            //0100
    int com2Y = y1 > y2 ? 8 : 0;            //1000
    int com = comX+comY+com2X+com2Y;
    int det=0;
    switch(com){
        case 0b1001 : return 270;
        case 0b0110 : return 180;
        case 0b0001 : return  90;
        case 0b0010 : return   0;
        case 0b1100 : det=2;break;
        case 0b0000 : det=1;break;
        case 0b0100 : det=2;break;
        case 0b1000 : det=3;break;
        default : LATAINV=1;return 0;
    }
    y1=-y1;y2=-y2;
    double temp= (y1-y2)/(x1-x2);
    int slope=temp*100;
    if(slope>2864) return  90;
    else if(slope<-2864) return  -90;
    else{
        int ptr=0;
        do{
            ptr++;
        }while(ptr<44 || (slope<arctanLUT[ptr][2] && slope>=arctanLUT[ptr][1]));
        switch(det){
            case 1 : return arctanLUT[ptr][0];
            case 2 : return 180 + arctanLUT[ptr][0];
            case 3 : return 360 + arctanLUT[ptr][0];
            default : LATAINV=1;return 0;
        }
    }
}

int Root(int x){
    if(x<100) return rootLUT[x];
    else{
        int a,b;
        b=x;
        a=x=0x3f;   // 64
        x = b/x;
        a=x=(x+a) >> 1;
        x = b/x;
        a=x=(x+a) >> 1;
        x = b/x;
        x=(x+a) >> 1;
        return(x);
    }
}

int Distance(int x1,int y1,int x2,int y2){
    y1=-y1;y2=-y2;
    int squared=((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
    return Root(squared);
}
int ShootError(int x,int y,int z){
    int ballX=getX(3);
    int ballY=getY(3);
    int dirA = ((getX(ID) + z - x)*(y - ballY) / (x - ballX)) + y;
    int Output = z>0? (Angle(getX(ID),getY(ID),getPrevX(ID),getPrevY(ID))-Angle(getX(ID) + z,dirA,getX(ID),getY(ID))) : (Angle(getPrevX(ID),getPrevY(ID),getX(ID),getY(ID))-Angle(getX(ID),getY(ID),getX(ID)+z,dirA));
    return Output;
}


int overhead(int a){        // If a=1 : go right, a=0 : go left
    int ballX=getX(3);
    int Output;
    if(getX(ID)+a < ballX) Output= a>0 ? 0:1; 
    else Output= a>0 ? 1:0;   
    return Output;               
    // return : 0 = correct
    //          1 = overhead
}

int PointError(int tarX,int tarY){
    int Output = getX(ID)>tarX ? (Angle(getPrevX(ID),getPrevY(ID),getX(ID),getY(ID))-Angle(getX(ID),getY(ID),tarX,tarY)) : (Angle(getX(ID),getY(ID),getPrevX(ID),getPrevY(ID))-Angle(tarX,tarY,getX(ID),getY(ID)));
    return Output;
}

int CheckDistance(int x1,int y1, int x2,int y2,int dis){
    int Output = Distance(x1,y1,x2,y2) >= dis ? 1 : 0;
    return Output;
}
