#ifndef __TowerUpgradePanel__
#define __TowerUpgradePanel__

#include "../CommonHeaders/InteractivePanel.h"

#include "../../EntitiesHeaders/Tower.h"

#include<memory>
#include<string>
#include<map>

class TowerUpgradePanel : public TowerInteractivePanel
{
public:
	TowerUpgradePanel();

	typedef std::function<void(std::shared_ptr<Tower>)> TowerUpgradedCallback;

	void draw() override;
	void update() override;

	void loadCallbacks() override;

	/**
	* set tower to be upgraded
	* @param if selectedTower is nullptr then the panel won't draw
	*/
	void setSelectedTower(std::shared_ptr<Tower> selectedTower);
	bool isSelected();
	void updateSelectedTower();

private:
	void setTowerUpgradedButtonCallbacks();

	std::shared_ptr<Tower> m_selectedTower;

	std::map<std::string, TowerUpgradedCallback> m_towerUpgradedButtonCallbacks;
};

#endif // !__TowerUpgradePanel__
