#include "../../../include/UIHeaders/LevelUpUIHeaders/LevelUpStateUI.h"

#include "../../../include/UIHeaders/LevelUpUIHeaders/LevelUpPanel.h"

LevelUpStateUI::LevelUpStateUI(std::string stateID) : StateUI(stateID)
{
}

void LevelUpStateUI::load()
{
	StateUI::load();

	// setting up level up panel
	auto levelUPPanel = getPanel<LevelUpPanel>();
	levelUPPanel->setTowerUnlockID(m_towerUnlockID);
	levelUPPanel = nullptr;
}

void LevelUpStateUI::setTowerUnlockID(std::string name)
{
	m_towerUnlockID = name;
}
