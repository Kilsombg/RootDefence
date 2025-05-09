#include "../../../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../../include/EntitiesHeaders/TowerButton.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

TowersPanel::TowersPanel() : TowerInteractivePanel()
{
	m_clickToPlaceTowerHandler = std::make_shared<ClickToPlaceTowerHandler>();
}

void TowersPanel::draw()
{
	InteractivePanel::draw();

	// render shadow tower
	if (m_clickToPlaceTowerHandler->getShadowObject())
	{
		m_clickToPlaceTowerHandler->render();
	}
}

void TowersPanel::update()
{
	// update tower buttons
	for (std::vector<std::unique_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->update();
	}

	// update m_clickToPlaceTowerHandler state
	m_clickToPlaceTowerHandler->update(m_playStateTowers);
}

void TowersPanel::loadCallbacks()
{
	// setting up create tower buttons
	m_towerButtonCallbacks[LoaderParamsConsts::createTowerCallbackID] = std::bind(&ClickToPlaceTowerHandler::handleEvent, m_clickToPlaceTowerHandler, std::placeholders::_1);
	setTowerButtonCallbacks();
	setTowerButtonLevel();
}

std::shared_ptr<ClickToPlaceTowerHandler> TowersPanel::getClickToPlaceTowerHandler()
{
	return m_clickToPlaceTowerHandler;
}

void TowersPanel::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
}

void TowersPanel::setTowerButtonCallbacks()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (TowerButton* pButton = dynamic_cast<TowerButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_towerButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
	}
}

void TowersPanel::setTowerButtonLevel()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (TowerButton* pButton = dynamic_cast<TowerButton*>(m_buttonObjects[i].get()))
		{
			pButton->setLevel(pLevel);
			pButton = nullptr;
		}
	}
}
