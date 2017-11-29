
#ifndef CONTROL_WHEEL_H_
#define CONTROL_WHEEL_H_


class ControlWheel{
public:
	void init(int x, int p, int m);
	void run();
private:
	int type;
	int pwm;
	int max;
};


#endif /* CONTROL_WHEEL_H_ */
