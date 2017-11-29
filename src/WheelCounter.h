
#ifndef WHEELCOUNTER_H_
#define WHEELCOUNTER_H_

class Counter {
public:
	Counter(void);
	void sample(short i);
	int getCount(void);
private:
	short last;
	int counts;		// holds 8 pcs of 4-bit samples
};

#endif /* WHEELCOUNTER_H_ */
