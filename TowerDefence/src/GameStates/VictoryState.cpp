#include "../../include/GameStateHeaders/VictoryState.h"

#include "../../include/UtilsHeaders/TextureManager.h"

#include "../../include/Game.h"

VictoryState::VictoryState()
{
	s_stateID = "VICTORY";	
}

void VictoryState::update()
{
	// update UI
	m_victoryStateUI->update();
}

void VictoryState::render()
{
	// dimming underneath
	TheTextureManager::Instance()->dimBackground(TheGame::Instance()->getWindow(), TheGame::Instance()->getRenderer());

	// draw UI
	m_victoryStateUI->draw();
}

bool VictoryState::onEnter()
{
	// load UI
	m_victoryStateUI = std::make_unique<VictoryStateUI>(s_stateID);
	m_victoryStateUI->setRewardValue(m_rewardValue);
	m_victoryStateUI->load();

	std::cout << "entering VictoryState\n";
	return true;
}

bool VictoryState::onExit()
{
	// cleaning textures
	for (std::vector<std::string>::size_type i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	// clean ui
	m_victoryStateUI->clean();

	std::cout << "exiting VictoryState\n";
	return true;
}

void VictoryState::handleEvents()
{
	// handle UI
	m_victoryStateUI->handleEvents();
}

bool VictoryState::drawUnderneath()
{
	return true;
}

std::string VictoryState::getStateID() const
{
	return s_stateID;
}

void VictoryState::setRewardValue(int rewardValue)
{
	m_rewardValue = rewardValue;
}
