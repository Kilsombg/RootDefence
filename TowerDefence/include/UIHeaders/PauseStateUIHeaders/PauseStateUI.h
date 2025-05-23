#ifndef __PauseStateUI__
#define __PauseStateUI__

#include "../CommonHeaders/StateUI.h"

#include<string>

class PauseStateUI : public StateUI
{
public:
	PauseStateUI(std::string stateID);

	void draw() override;
	void update() override;
	void load() override;
	void handleEvents() override;

	void clean() override;
};

#endif // !__PauseStateUI__
