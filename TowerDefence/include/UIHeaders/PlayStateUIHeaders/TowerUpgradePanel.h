#ifndef __TowerUpgradePanel__
#define __TowerUpgradePanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../../include/Constants/ColorsConsts.h"

#include "../../EntitiesHeaders/Tower.h"
#include "../../EntitiesHeaders/Texture.h"
#include "../../EntitiesHeaders/Text.h"
#include "../../EntitiesHeaders/TowerUpgradedButton.h"

#include "../../EventHandlersHeaders/SellTowerHandler.h"

#include "../../MapHeaders/Level.h"

#include<memory>
#include<string>
#include<map>
#include<array>

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
	/**
	* draw buttons and corresponding objects inside them
	*/
	void drawButtons();
	/**
	* Set selected tower to coresponding tower dependent objects in panel
	*/
	void setSelectedTowerToObjects(std::shared_ptr<Tower> selectedTower);
	/**
	* set parameter images to tower upgrade buttons.
	*/
	void setTowerUpgradeButtonsImages();
	void setTowerUpgradedButtonCallbacks();
	void setSellTowerButtonCallbacks();
	/**
	* update static labels' value.
	*/
	void updateStaticLabel();
	/**
	* update dynamic labels' value.
	*/
	void updateDynamicLabel();
	/**
	* when mouse is on upgrade button, then update with new value coresponding parameter.
	*/
	void updateUpgradeParameterLabels(TowerUpgradedButton* pUpgradeButton);
	/**
	* set visibilty of labels and icons.
	* 
	* @param mode - if true hide upgrade labels and icons and show max upgrade label and vice versa if false.
	*/
	void updateMaxUpgradeButtons(bool mode, int upgradeID);

	std::shared_ptr<Tower> m_selectedTower;

	std::map<std::string, TowerUpgradedCallback> m_towerUpgradedButtonCallbacks;
	std::map<std::string, SellTowerCallback> m_sellTowerButtonCallbacks;

	std::shared_ptr<SellTowerHandler> m_sellTowerHandler;

	std::shared_ptr<Level> pLevel;

	Texture m_towerImage; // icon of tower
	Texture m_towerSellResourceImage; // resource image for sell button
	std::array<Texture, 2> m_towerUpgradeImages; // image of tower's paramater for upgrade tower
	std::array<Texture, 2> m_towerUpgradeButtonCantAffordImages; // tower upgrade button background image, when can't be afforded
	std::array<bool, 2> m_cantBuyTowerUpgrade; // flags for affordable tower upgrade buttons
	std::array<Texture, 2> m_towerUpgradeCostResourceImages; // image of tower upgrade cost resource
	std::array<float, 2> m_towerUpgradeProgressLevel; // level progress of upgrades

	ColorsConsts::Color m_upgradeFontColor; // font color of parameter, when mouse is on upgrade button.

	bool m_mouseOverRadiusUpgrade; // flag for drawing upgrade radius on screen
	int m_nextRadiusUpgradeValue; // needed radius for drawing on screen
};


class TowerUpgradePanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;
};

#endif // !__TowerUpgradePanel__
