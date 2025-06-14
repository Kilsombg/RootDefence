#ifndef __PlayStateUI__
#define __PlayStateUI__

#include "../CommonHeaders/StateUI.h"

#include "../../DataHeaders/GameSessionData.h"

#include "../../EntitiesHeaders/Tower.h"

#include "../../MapHeaders/Level.h"

#include<vector>
#include<string>
#include<memory>

/**
* StateUI for PlayState.
* 
* It contains TowersPanel, TipsPanel and TowerUpgradePanel.
*/
class PlayStateUI : public StateUI
{
public:
	PlayStateUI(std::string stateID);

	void draw() override;
	void update() override;
	void load() override;
	void handleEvents() override;

	void clean() override;

	// getters and setters

	void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers);

	void setLevel(std::shared_ptr<Level> level);
	
	void setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData);

private:
	std::shared_ptr<Level> pLevel;

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_playStateTowers;

	std::shared_ptr<GameSessionData> m_gameSessionData;
};

#endif // !__PlayStateUI__