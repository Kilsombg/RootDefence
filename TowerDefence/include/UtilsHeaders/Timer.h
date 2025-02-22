#ifndef __Timer__
#define __Timer__

class Timer
{
public:
	Timer();
	Timer(float setTimeSMax, float setTimeSCurrent = 0.0f);

	void countUp(float dT);
	void countDown(float dT);
	void resetToZero();
	void resetToMax();
	bool timeSIsZero();
	bool timeSIsGreaterThanOrEqualTo(float timeSCheck);


private:
	float timeSMax;
	float timeSCurrent;
};

#endif // !__Timer__
