#ifndef __MainMenuStateUI__
#define __MainMenuStateUI__

#include "../CommonHeaders/StateUI.h"

#include<string>

/**
* StateUI for MainMenuState.
*/
class MainMenuStateUI : public StateUI
{
public:
	MainMenuStateUI(std::string stateID) : StateUI(stateID) {}
};

#endif // !__MainMenuStateUI__
