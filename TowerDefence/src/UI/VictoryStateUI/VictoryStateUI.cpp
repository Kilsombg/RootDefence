#include "../../../include/UIHeaders/VictoryStateUIHeaders/VictoryStateUI.h"

VictoryStateUI::VictoryStateUI(std::string stateID) : StateUI(stateID)
{
}

void VictoryStateUI::draw()
{
	StateUI::draw();
}

void VictoryStateUI::update()
{
	StateUI::update();
}

void VictoryStateUI::load()
{
	StateUI::load();
}

void VictoryStateUI::handleEvents()
{
	StateUI::handleEvents();
}

void VictoryStateUI::clean()
{
	StateUI::clean();
}

void VictoryStateUI::setCurrentWaveID(int currentWaveID)
{
	m_currentWaveID = currentWaveID;
}
