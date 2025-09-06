#ifndef __LevelUpState__
#define __LevelUpState__

#include "GameState.h"

#include "../UIHeaders/LevelUpUIHeaders/LevelUpStateUI.h"

#include<memory>

/**
* State when player level up.
*/
class LevelUpState : public GameState
{
public:
	LevelUpState();

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual void handleEvents() override;

	virtual bool drawUnderneath() override;

	// getters and setters

	void setTowerUnlockedID(std::string name);

private:
	std::unique_ptr<LevelUpStateUI> m_levelUpStateUI;
	std::string m_towerUnlockedID;
};

#endif // !__LevelUpState__
