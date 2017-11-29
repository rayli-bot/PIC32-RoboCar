
#include <p32mx250f128d.h>
#ifndef DECODE_H_
#define DECODE_H_

int h2d(char d, int t);

static class location{
private:
	int x;
	int y;
	int prevX;
	int prevY;
public:
	int getX();
	int getY();
	int getPrevX();
	int getPrevY();
	void setX(char *a);
	void setY(char *a);
	void empty();
}CAR[3],BALL,GOAL,START;

int getX(int a);
int getY(int a);
int getPrevX(int a);
int getPrevY(int a);

void setLocation(int a, char *b, char *c);
void empty(int a);


void Raw2Locate(char *d);
#endif /* DECODE_H_ */
