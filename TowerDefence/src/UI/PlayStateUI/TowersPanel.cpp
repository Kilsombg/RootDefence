#include "../../../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/EntitiesHeaders/TowerButton.h"
#include "../../../include/EntitiesHeaders/Text.h"


TowersPanel::TowersPanel() : TowerInteractivePanel()
{
	m_clickToPlaceTowerHandler = std::make_shared<ClickToPlaceTowerHandler>();
}

void TowersPanel::draw()
{
	// draw buttons
	InteractivePanel::draw();

	// draw texts
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	m_healthText.draw();

	// render shadow tower
	if (m_clickToPlaceTowerHandler->getShadowObject())
	{
		m_clickToPlaceTowerHandler->render();
	}
}

void TowersPanel::update()
{
	// update tower buttons
	InteractivePanel::update();

	// update m_clickToPlaceTowerHandler state
	m_clickToPlaceTowerHandler->update(m_playStateTowers);

	// update labels
	m_healthText.setMessage(std::to_string(m_gameSessionData->gameHealth));
	m_healthText.update();
}

void TowersPanel::clean()
{
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		// Cleaning text textures
		if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(m_gameObjects[i].get())))
		{
			pText->clean();
			pText = nullptr;
		}
	}
	m_healthText.clean();
}

void TowersPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		if (std::unique_ptr<TowerButton> pButton = std::unique_ptr<TowerButton>(dynamic_cast<TowerButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::move(pButton));
			pButton = nullptr;
			gameObjects[i].release();
		}
		else if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_gameObjects.push_back(std::move(pText));
			pText = nullptr;
			gameObjects[i].release();
		}
	}
	
	// load callbacks
	loadCallbacks();
}

void TowersPanel::loadDependencies(std::shared_ptr<Level> level, std::shared_ptr<GameSessionData> gameSessionData)
{
	// load level
	setLevel(level);

	// load session data
	m_gameSessionData = gameSessionData;

	// load text labels
	m_healthText = Text(630, 100, 20, 20, "health", std::to_string(m_gameSessionData->gameHealth));
}

void TowersPanel::loadCallbacks()
{
	// setting up create tower buttons
	m_towerButtonCallbacks[LoaderParamsConsts::createTowerCallbackID] = std::bind(&ClickToPlaceTowerHandler::handleEvent, m_clickToPlaceTowerHandler, std::placeholders::_1);
	setTowerButtonCallbacks();
}

std::shared_ptr<ClickToPlaceTowerHandler> TowersPanel::getClickToPlaceTowerHandler()
{
	return m_clickToPlaceTowerHandler;
}

void TowersPanel::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
	m_clickToPlaceTowerHandler->setLevel(pLevel);
	setTowerButtonLevel();
}

void TowersPanel::setGameSeesionData(std::shared_ptr<GameSessionData> gameSessionData)
{
	m_gameSessionData = gameSessionData;
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

std::unique_ptr<Panel> TowersPanelCreator::create() const
{
	return std::make_unique<TowersPanel>();
}
