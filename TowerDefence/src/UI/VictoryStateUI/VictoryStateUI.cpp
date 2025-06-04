#include "../../../include/UIHeaders/VictoryStateUIHeaders/VictoryStateUI.h"

#include "../../../include/UIHeaders/VictoryStateUIHeaders/VictoryStatePanel.h"

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
	// load panels
	StateUI::load();

	// load current wave
	auto pVictoryStateUIPanel = getPanel<VictoryStatePanel>();
	pVictoryStateUIPanel->setRewardValue(m_rewardValue);
}

void VictoryStateUI::handleEvents()
{
	StateUI::handleEvents();
}

void VictoryStateUI::clean()
{
	StateUI::clean();
}

void VictoryStateUI::setRewardValue(int rewardValue)
{
	m_rewardValue = rewardValue;
}
