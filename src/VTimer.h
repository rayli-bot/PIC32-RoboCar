
#ifndef VTIMER_H_
#define VTIMER_H_



class VTimer{
public:
	VTimer();
	void setDelay(int x);
	int tick();
private:
	int period;
	int count;
};

#endif /* VTIMER_H_ */
