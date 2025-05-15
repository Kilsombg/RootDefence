#include "../../../include/UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/EntitiesHeaders/TowerUpgradedButton.h"
#include "../../../include/EntitiesHeaders/SelectedTowerButton.h"
#include "../../../include/EntitiesHeaders/SellTowerButton.h"

#include "../../../include/EventHandlersHeaders/TowerUpgradeHandlers.h"


#include "../../../include/ManagersHeaders/SellManager.h"

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

		for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}

		// draw buttons
		InteractivePanel::draw();
	}
}

void TowerUpgradePanel::update()
{
	// update buttons
	if (isSelected())
	{
		for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
		{
			m_buttonObjects[i]->update();

			// set selected tower into upgrade buttons
			if (SelectedTowerButton* selectedTowerButton = dynamic_cast<SelectedTowerButton*>(m_buttonObjects[i].get()))
			{
				selectedTowerButton->setSelectedTower(m_selectedTower);
				selectedTowerButton = nullptr;
			}
		
			// set selected tower to sell manager
			TheSellManager::Instance()->setSelectedTower(m_selectedTower);
		}
	}
	else // there is no selected tower
	{
		for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
		{
			// remove relected pointer
			if (SelectedTowerButton* selectedTowerButton = dynamic_cast<SelectedTowerButton*>(m_buttonObjects[i].get()))
			{
				selectedTowerButton->setSelectedTower(nullptr);
				selectedTowerButton = nullptr;
			}

			// set selected tower to sell manager
			TheSellManager::Instance()->setSelectedTower(nullptr);
		}
	}

	// set selected tower to TowerUpgradePanel
	updateSelectedTower();
}

void TowerUpgradePanel::clean()
{
	// clean background texture
	m_backgroundTexture->clean();

	// clean objects texture
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
}

void TowerUpgradePanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		if (std::unique_ptr<SelectedTowerButton> pButton = std::unique_ptr<SelectedTowerButton>(dynamic_cast<SelectedTowerButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::move(pButton));
			pButton = nullptr;
			gameObjects[i].release();
		}
		else
		{
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

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
			m_selectedTower = (*m_playStateTowers)[i];
			return;
		}
	}
	m_selectedTower.reset();
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

std::unique_ptr<Panel> TowerUpgradePanelCreator::create() const
{
	return std::make_unique<TowerUpgradePanel>();
}
