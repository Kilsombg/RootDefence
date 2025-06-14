#ifndef __Timer__
#define __Timer__

/**
* Timer determines elapsed time.
* 
* Set max time and check when the time is out.
* 
* Call countUp() or countDown() on each frame.
*/
class Timer
{
public:
	Timer();
	/**
	* @param setTimeSMax - max timer in seconds.
	* @param setTimeSCurrent - current time of timer. Default value 0.0f
	*/
	Timer(float setTimeSMax, float setTimeSCurrent = 0.0f);
	/**
	* Increase current timer. When exceeds, sets to max.
	*/
	void countUp(float dT);
	/**
	* Decrease current timer. If below 0, then set to 0.
	*/
	void countDown(float dT);
	/**
	* Set current time to 0.
	*/
	void resetToZero();
	/**
	* Reset current time value to max.
	*/
	void resetToMax();
	/**
	* Check if current time value is 0.
	*/
	bool timeSIsZero();
	/**
	* Check if current time is >= timeSCheck.
	* 
	* @param timeSCheck - time in seconds.
	*/
	bool timeSIsGreaterThanOrEqualTo(float timeSCheck);


private:
	float timeSMax; // max timer value in seconds.
	float timeSCurrent; // current timer value in seconds.
};

#endif // !__Timer__
