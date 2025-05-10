#ifndef __TowerUpgradePanel__
#define __TowerUpgradePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Tower.h"

#include<memory>
#include<string>
#include<map>

class TowerUpgradePanel : public TowerInteractivePanel
{
public:
	TowerUpgradePanel();

	typedef std::function<void(std::shared_ptr<Tower>, int)> TowerUpgradedCallback;

	void draw() override;
	void update() override;
	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;

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


class TowerUpgradePanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;
};

#endif // !__TowerUpgradePanel__
