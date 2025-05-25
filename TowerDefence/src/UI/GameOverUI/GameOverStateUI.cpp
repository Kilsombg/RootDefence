#include "../../../include/UIHeaders/GameOverUIHeaders/GameOverStateUI.h"

#include "../../../include/UIHeaders/GameOverUIHeaders/GameOverStatePanel.h"

GameOverStateUI::GameOverStateUI(std::string stateID) : StateUI(stateID)
{
}

void GameOverStateUI::draw()
{
	StateUI::draw();
}

void GameOverStateUI::update()
{
	StateUI::update();
}

void GameOverStateUI::load()
{
	StateUI::load();

	auto pGameOverPanel = getPanel<GameOverStatePanel>();
	pGameOverPanel->setCurrentWaveID(m_currentWaveID);
	pGameOverPanel = nullptr;

}

void GameOverStateUI::handleEvents()
{
	StateUI::handleEvents();
}

void GameOverStateUI::clean()
{
	StateUI::clean();
}

void GameOverStateUI::setCurrentWaveID(int currentWaveID)
{
	m_currentWaveID = currentWaveID;
}