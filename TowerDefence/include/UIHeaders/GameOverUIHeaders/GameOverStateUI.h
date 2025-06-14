#ifndef __GameOverStateUI__
#define __GameOverStateUI__

#include "../CommonHeaders/StateUI.h"

#include<string>

/**
* Class that manages gameOver state panels.
*/
class GameOverStateUI : public StateUI
{
public:
	GameOverStateUI(std::string stateID);

	void draw() override;
	void update() override;
	void load() override;
	void handleEvents() override;

	void clean() override;

	void setCurrentWaveID(int currentWaveID);

private:
	int m_currentWaveID;
};

#endif // !__GameOverStateUI__
