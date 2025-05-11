#ifndef __TowerUpgradePanel__
#define __TowerUpgradePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Tower.h"

#include "../../EventHandlersHeaders/SellTowerHandler.h"

#include "../../MapHeaders/Level.h"

#include<memory>
#include<string>
#include<map>

class TowerUpgradePanel : public TowerInteractivePanel
{
public:
	TowerUpgradePanel();

	typedef std::function<void(std::shared_ptr<Tower>, int)> TowerUpgradedCallback;
	typedef std::function<void(std::shared_ptr<Tower>)> SellTowerCallback;

	void draw() override;
	void update() override;
	void clean() override;
	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;

	void handleEvents() override;

	/**
	* Load needed dependencies not included from StateParser.
	*/
	void loadDependencies(std::shared_ptr<Level> level);

	void loadCallbacks() override;
	
	// getters and setters
	
	void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers) override;

	/**
	* set tower to be upgraded
	* @param if selectedTower is nullptr then the panel won't draw
	*/
	void setSelectedTower(std::shared_ptr<Tower> selectedTower);

	void setLevel(std::shared_ptr<Level> level);


	bool isSelected();
	void updateSelectedTower();

private:
	void setTowerUpgradedButtonCallbacks();
	void setSellTowerButtonCallbacks();

	std::shared_ptr<Tower> m_selectedTower;

	std::map<std::string, TowerUpgradedCallback> m_towerUpgradedButtonCallbacks;
	std::map<std::string, SellTowerCallback> m_sellTowerButtonCallbacks;

	std::shared_ptr<SellTowerHandler> m_sellTowerHandler;

	std::shared_ptr<Level> pLevel;
};


class TowerUpgradePanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;
};

#endif // !__TowerUpgradePanel__
