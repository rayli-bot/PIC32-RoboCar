
#ifndef PID_H_
#define PID_H_


class PID{
public:
	PID(int p, int in, int id, int d);
	void reset(void);
	double control(int x, int target);
private:
	int P, In, Id, D, acc, last;
};


#endif /* PID_H_ */
