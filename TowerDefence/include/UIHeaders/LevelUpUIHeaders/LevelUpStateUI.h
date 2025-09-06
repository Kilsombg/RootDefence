#ifndef __LevelUpStateUI__
#define __LevelUpStateUI__

#include "../CommonHeaders/StateUI.h"

#include<string>

/**
* UI for LevelUpState.
*/
class LevelUpStateUI : public StateUI
{
public:
	LevelUpStateUI(std::string stateID);

	virtual void load() override;

	// getters and setters

	void setTowerUnlockID(std::string name);

private:
	std::string m_towerUnlockID;
};

#endif // !__LevelUpStateUI__
