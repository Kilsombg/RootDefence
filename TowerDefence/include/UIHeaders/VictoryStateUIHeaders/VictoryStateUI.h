#ifndef __VictoryStateUI__
#define __VictoryStateUI__

#include "../CommonHeaders/StateUI.h"

#include<string>


class VictoryStateUI : public StateUI
{
public:
	VictoryStateUI(std::string stateID);

	void draw() override;
	void update() override;
	void load() override;
	void handleEvents() override;

	void clean() override;

	// getters and setters

	void setRewardValue(int rewardValue);

private:
	int m_rewardValue;
};


#endif // !__VictoryStateUI__
