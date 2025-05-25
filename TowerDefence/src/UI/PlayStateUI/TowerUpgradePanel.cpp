#include "../../../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/ColorsConsts.h"
#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/GameObjectConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/SelectedTowerButton.h"
#include "../../../include/EntitiesHeaders/SellTowerButton.h"
#include "../../../include/EntitiesHeaders/FreezeTower.h"

#include "../../../include/EventHandlersHeaders/TowerUpgradeHandlers.h"

#include "../../../include/ManagersHeaders/SellManager.h"
#include "../../../include/ManagersHeaders/PurchaseManager.h"

#include "../../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../../include/UtilsHeaders/TextFormatter.h"
#include "../../../include/UtilsHeaders/TextureManager.h"

#include<functional>

TowerUpgradePanel::TowerUpgradePanel() : TowerInteractivePanel()
{
}

void TowerUpgradePanel::draw()
{
	if (isSelected())
	{
		//  draw background
		m_backgroundTexture->draw();

		// draw tower iamge
		m_towerImage.draw();

		if (m_mouseOverRadiusUpgrade)
		{
			// draw tower upgrade radius
			float centerX, centerY;
			centerX = m_selectedTower->getPosition().getX() + m_selectedTower->getWidth() / 2;
			centerY = m_selectedTower->getPosition().getY() + m_selectedTower->getHeight() / 2;

			TheTextureManager::Instance()->drawFilledCircle(centerX, centerY, m_nextRadiusUpgradeValue,
				{ ColorsConsts::lightGreen.r, ColorsConsts::lightGreen.g, ColorsConsts::lightGreen.b, ColorsConsts::lightGreen.a },
				TheGame::Instance()->getRenderer());
		}

		// draw tower parameter textures
		for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}

		// draw buttons
		drawButtons();

		// draw labels
		for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
		{
			it->second->draw();
		}
	}
}

void TowerUpgradePanel::update()
{
	if (isSelected())
	{
		// update buttons
		for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
		{
			m_buttonObjects[i]->update();

			// update upgraded parameter value when mouse is on upgrade button
			if (TowerUpgradedButton* pUpgradeButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
			{
				updateUpgradeParameterLabels(pUpgradeButton);
				pUpgradeButton = nullptr;
			}
		}

		// update dynamic labels
		updateDynamicLabel();
	}

	// set selected tower to TowerUpgradePanel
	updateSelectedTower();
}

void TowerUpgradePanel::clean()
{
	TowerInteractivePanel::clean();
}

void TowerUpgradePanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		if (std::unique_ptr<SelectedTowerButton> pButton = std::unique_ptr<SelectedTowerButton>(dynamic_cast<SelectedTowerButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::move(pButton));
			gameObjects[i].release();
		}
		else if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_labelsMap[pText->getLabelID()] = std::move(pText);
			gameObjects[i].release();
		}
		else
		{
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load upgrade font color
	m_upgradeFontColor = ColorsConsts::green;

	// load callbacks
	loadCallbacks();
}

void TowerUpgradePanel::handleEvents()
{
	if (isSelected())
	{
		TowerInteractivePanel::handleEvents();
	}
}

void TowerUpgradePanel::loadDependencies(std::shared_ptr<Level> level)
{
	setLevel(level);
}

void TowerUpgradePanel::loadCallbacks()
{
	// load tower upgrade buttons callbacks
	TowerUpgradeHandlers towerUpgradeHandlers;
	m_towerUpgradedButtonCallbacks[LoaderParamsConsts::towerUpgradeCallbackID] = std::bind(&TowerUpgradeHandlers::handleUpgradeEvent, towerUpgradeHandlers, std::placeholders::_1, std::placeholders::_2);
	setTowerUpgradedButtonCallbacks();

	// load sell tower buttons callbacks
	m_sellTowerHandler = std::make_shared<SellTowerHandler>();
	m_sellTowerButtonCallbacks[LoaderParamsConsts::sellTowerCallbackID] = std::bind(&SellTowerHandler::handleSellTowerEvent, m_sellTowerHandler, std::placeholders::_1);
	setSellTowerButtonCallbacks();
}

void TowerUpgradePanel::setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers)
{
	TowerInteractivePanel::setPlayStateTowers(playStateTowers);

	m_sellTowerHandler->setPlayStateTowers(m_playStateTowers);
}

void TowerUpgradePanel::setSelectedTower(std::shared_ptr<Tower> selectedTower)
{
	m_selectedTower = selectedTower;
}

void TowerUpgradePanel::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
	m_sellTowerHandler->setLevel(level);
}

bool TowerUpgradePanel::isSelected()
{
	if (m_selectedTower.get())
	{
		return m_selectedTower->isSelected();
	}
	return false;
}

void TowerUpgradePanel::updateSelectedTower()
{
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_playStateTowers->size(); i++)
	{
		if ((*m_playStateTowers)[i]->isSelected())
		{
			// no need to update if selected tower is not changed
			if (m_selectedTower == (*m_playStateTowers)[i]) return;

			m_selectedTower = (*m_playStateTowers)[i];
			setSelectedTowerToObjects(m_selectedTower);
			return;
		}
	}

	m_selectedTower.reset();
	setSelectedTowerToObjects(nullptr);
}

void TowerUpgradePanel::drawButtons()
{
	InteractivePanel::draw();

	// draw not affordable tower upgrade button background if needed
	for (std::array<Texture, 2>::size_type i = 0; i < m_towerUpgradeButtonCantAffordImages.size(); i++)
	{
		if (m_cantBuyTowerUpgrade[i])
		{
			m_towerUpgradeButtonCantAffordImages[i].draw();
		}
	}

	// draw upgrade buttons paramater icons
	for (std::array<Texture, 2>::size_type i = 0; i < m_towerUpgradeImages.size(); i++)
	{
		m_towerUpgradeImages[i].draw();
	}

	// draw cost icons
	for (std::array<Texture, 2>::size_type i = 0; i < m_towerUpgradeCostResourceImages.size(); i++)
	{
		m_towerUpgradeCostResourceImages[i].draw();
	}

	// draw progress bar
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (TowerUpgradedButton* pUpgradeButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
		{
			TheTextureManager::Instance()->drawProgressBar(pUpgradeButton->getPosition().getX(), pUpgradeButton->getPosition().getY() + pUpgradeButton->getHeight() + 5,
				pUpgradeButton->getWidth(), 5,
				{ ColorsConsts::black.r, ColorsConsts::black.g,ColorsConsts::black.b,ColorsConsts::black.a },
				{ ColorsConsts::green.r, ColorsConsts::green.g,ColorsConsts::green.b,ColorsConsts::green.a },
				m_towerUpgradeProgressLevel[pUpgradeButton->getUpgradeID()], TheGame::Instance()->getRenderer());
			pUpgradeButton = nullptr;
		}
	}

	// draw sell resource icon
	m_towerSellResourceImage.draw();
}

void TowerUpgradePanel::setSelectedTowerToObjects(std::shared_ptr<Tower> selectedTower)
{
	// set tower image
	if (selectedTower != nullptr)
	{
		// update tower image
		m_towerImage.loadAttributes(m_selectedTower->getTexureID(),
			(float)60 - m_selectedTower->getWidth() / 2, (float)490 - m_selectedTower->getHeight() / 2,
			m_selectedTower->getWidth(), m_selectedTower->getHeight());

		// update tower upgrade image
		setTowerUpgradeButtonsImages();

		// update textures
		for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
		{
			if (Texture* pTexture = dynamic_cast<Texture*>(m_gameObjects[i].get()))
			{
				if (pTexture->getTextureID() == "slowPercentageIcon")
				{
					pTexture->setHidden(m_selectedTower->getName() != "Frozen Bush");
				}
			}
		}

		// update static labels
		updateStaticLabel();
	}

	// set selected tower into upgrade buttons
	for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (SelectedTowerButton* selectedTowerButton = dynamic_cast<SelectedTowerButton*>(m_buttonObjects[i].get()))
		{
			selectedTowerButton->setSelectedTower(selectedTower);
			selectedTowerButton = nullptr;
		}
	}

	// set selected tower to sell manager
	TheSellManager::Instance()->setSelectedTower(selectedTower);
}

void TowerUpgradePanel::setTowerUpgradeButtonsImages()
{
	for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		// set up tower ugprade buttons
		if (TowerUpgradedButton* pUpgradeButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
		{
			TowerUpgradeData upgradeData = m_selectedTower->getTowerUpgradesData()[pUpgradeButton->getUpgradeID()];
			if (upgradeData.statName.empty()) {
				pUpgradeButton = nullptr;
				continue;
			}

			// set parameter image
			int upgradeID = pUpgradeButton->getUpgradeID();
			int iconSize = 24;
			m_towerUpgradeImages[upgradeID].loadAttributes(upgradeData.statName + "Icon",
				470 + upgradeID * (pUpgradeButton->getWidth() + 10), 491,
				iconSize, iconSize);
			m_towerUpgradeImages[upgradeID].centerTexture();

			// set tower upgrade background for not affordable state
			m_towerUpgradeButtonCantAffordImages[upgradeID].loadAttributes(UIConsts::upgradeButtonNotAffordable,
				450 + upgradeID * (pUpgradeButton->getWidth() + 10), 475,
				pUpgradeButton->getWidth(), pUpgradeButton->getHeight());

			// set cost resource image
			std::string costTextureID = m_selectedTower->getTowerType(m_selectedTower->getColor()) + UIConsts::resourceIconSmall;
			int resourceIconSize = 16;
			m_towerUpgradeCostResourceImages[upgradeID].loadAttributes(costTextureID,
				504 + upgradeID * (pUpgradeButton->getWidth() + 10), 496,
				resourceIconSize, resourceIconSize);
			m_towerUpgradeCostResourceImages[upgradeID].centerTexture();

			pUpgradeButton = nullptr;
		}
		// set up sell Tower button
		else if (SellTowerButton* pSellButton = dynamic_cast<SellTowerButton*>(m_buttonObjects[i].get()))
		{
			// set resource icon
			std::string resourceTextureID = m_selectedTower->getTowerType(m_selectedTower->getColor()) + UIConsts::resourceIconSmall;
			int resourceIconSize = 16;
			m_towerSellResourceImage.loadAttributes(resourceTextureID,
				pSellButton->getPosition().getX() + 10, pSellButton->getPosition().getY() + 13,
				resourceIconSize, resourceIconSize);
		}
	}
}

void TowerUpgradePanel::setTowerUpgradedButtonCallbacks()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (TowerUpgradedButton* pButton = dynamic_cast<TowerUpgradedButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_towerUpgradedButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

void TowerUpgradePanel::setSellTowerButtonCallbacks()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (SellTowerButton* pButton = dynamic_cast<SellTowerButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_sellTowerButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

void TowerUpgradePanel::updateStaticLabel()
{
	m_labelsMap[UIConsts::towerNameLabel]->setMessage(m_selectedTower->getName());
	if (FreezeTower* freezeTower = dynamic_cast<FreezeTower*>(m_selectedTower.get()))
	{
		m_labelsMap[UIConsts::slowPercentageLabel]->setHidden(false);
	}
	else
	{
		m_labelsMap[UIConsts::slowPercentageLabel]->setHidden(true);
	}



	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->update();
	}
}

void TowerUpgradePanel::updateDynamicLabel()
{
	// update values
	m_labelsMap[UIConsts::damageValueLabel]->setMessage(TheTextFormatter::Instance()->trimFractionalPart(std::to_string(m_selectedTower->getDamage()), 2));
	m_labelsMap[UIConsts::attackSpeedValueLabel]->setMessage(TheTextFormatter::Instance()->trimFractionalPart(std::to_string(m_selectedTower->getAttackSpeed()), 2));
	m_labelsMap[UIConsts::radiusValueLabel]->setMessage(TheTextFormatter::Instance()->trimFractionalPart(std::to_string(m_selectedTower->getRadius()), 2));
	int spentResourceValue = m_selectedTower->getSpentResources().value * TheSellManager::Instance()->getBaseSellPercentage();
	m_labelsMap[UIConsts::sellValueLabel]->setMessage(std::to_string(spentResourceValue));

	// update special tower parameters
	if (FreezeTower* freezeTower = dynamic_cast<FreezeTower*>(m_selectedTower.get()))
	{
		m_labelsMap[UIConsts::slowPercentageValueLabel]->setMessage(TheTextFormatter::Instance()->extractPercentage(std::to_string(freezeTower->getFreezePercentage())));
		m_labelsMap[UIConsts::slowPercentageValueLabel]->setHidden(false);
		freezeTower = nullptr;
	}
	else
	{
		m_labelsMap[UIConsts::slowPercentageValueLabel]->setHidden(true);
	}

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		if (it->second->getFontColor() != m_upgradeFontColor)
		{
			it->second->update();
		}
	}
}

void TowerUpgradePanel::updateUpgradeParameterLabels(TowerUpgradedButton* pUpgradeButton)
{
	int upgradeID = pUpgradeButton->getUpgradeID();
	TowerUpgradeData upgradeData = m_selectedTower->getTowerUpgradesData()[upgradeID];
	// if not set tower upgrade, then return
	if (upgradeData.statName.empty()) return;

	std::string upgradeValueLabelID = upgradeData.statName + UIConsts::valueLabelSuffix;
	m_mouseOverRadiusUpgrade = false;

	if (pUpgradeButton->isMouseOnButton() && upgradeData.nextLevel < upgradeData.maxLevel)
	{
		// change upgrade parameter when mouse on button if there is next level upgrade
		m_labelsMap[upgradeValueLabelID]->setFontColor(m_upgradeFontColor);
		if (upgradeValueLabelID == std::string(UIConsts::slowPercentageValueLabel))
		{
			m_labelsMap[upgradeValueLabelID]->setMessage(TextFormatter::Instance()->extractPercentage(std::to_string(upgradeData.values[upgradeData.nextLevel])));
		}
		else
		{
			m_labelsMap[upgradeValueLabelID]->setMessage(TextFormatter::Instance()->trimFractionalPart(std::to_string(upgradeData.values[upgradeData.nextLevel]), 2));
		}
		m_labelsMap[upgradeValueLabelID]->update();

		// update upgrade radius if upgrade would increase its radius
		m_mouseOverRadiusUpgrade = upgradeData.statName == LoaderParamsConsts::radius;
		if (m_mouseOverRadiusUpgrade) m_nextRadiusUpgradeValue = upgradeData.values[upgradeData.nextLevel];
	}
	else if (m_labelsMap[upgradeValueLabelID]->getFontColor() == m_upgradeFontColor)
	{
		// return the normal color of tower parameter
		m_labelsMap[upgradeValueLabelID]->setFontColor(ColorsConsts::white);
	}

	// set tower upgrade button background
	m_cantBuyTowerUpgrade[upgradeID] = !ThePurchaseManager::Instance()->canPurchaseUpgrade(upgradeData, m_selectedTower->getColor());

	// set cost label
	if (upgradeData.nextLevel < upgradeData.maxLevel)
	{
		std::string upgradeCostLabelID = UIConsts::upgradeButtonCostPrefix + std::to_string(upgradeID) + UIConsts::upgradeButtonCostSufix;
		m_labelsMap[upgradeCostLabelID]->setMessage(std::to_string(upgradeData.costs[upgradeData.nextLevel]));
		updateMaxUpgradeButtons(false, upgradeID);
	}
	else
	{
		updateMaxUpgradeButtons(true, upgradeID);
	}

	// update upgrade bar prgoress
	m_towerUpgradeProgressLevel[upgradeID] = (float)upgradeData.nextLevel / upgradeData.maxLevel;
}

void TowerUpgradePanel::updateMaxUpgradeButtons(bool mode, int upgradeID)
{
	std::string upgradeCostLabelID = UIConsts::upgradeButtonCostPrefix + std::to_string(upgradeID) + UIConsts::upgradeButtonCostSufix;
	std::string upgradeTextLabelID = UIConsts::upgradeButtonTextPrefix + std::to_string(upgradeID) + UIConsts::upgradeButtonTextSufix;
	std::string maxUpgradeButtonLabelID = "maxUpgrade" + std::to_string(upgradeID) + "Button";

	m_labelsMap[upgradeCostLabelID]->setHidden(mode);
	m_labelsMap[upgradeTextLabelID]->setHidden(mode);
	m_labelsMap[maxUpgradeButtonLabelID]->setHidden(!mode);
	m_towerUpgradeCostResourceImages[upgradeID].setHidden(mode);
}

std::unique_ptr<Panel> TowerUpgradePanelCreator::create() const
{
	return std::make_unique<TowerUpgradePanel>();
}
