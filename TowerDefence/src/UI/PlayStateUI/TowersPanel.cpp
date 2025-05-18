#include "../../../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/GameObjectConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/TowerButton.h"
#include "../../../include/EntitiesHeaders/Text.h"

#include "../../../include/UtilsHeaders/TowerFactory.h"

#include<iostream>

TowersPanel::TowersPanel() : TowerInteractivePanel()
{
	m_clickToPlaceTowerHandler = std::make_shared<ClickToPlaceTowerHandler>();
}

void TowersPanel::draw()
{
	// draw background
	m_backgroundTexture->draw();
	
	// draw buttons
	InteractivePanel::draw();

	// draw text labels
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// render shadow tower
	if (m_clickToPlaceTowerHandler->getShadowObject())
	{
		m_clickToPlaceTowerHandler->render();
	}
}

void TowersPanel::update()
{
	// get selected button
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		if (std::shared_ptr<TowerButton> towerButton = std::dynamic_pointer_cast<TowerButton>(m_buttonObjects[i]))
		{
			if (towerButton->isSelected())
			{
				m_selectedTowerButton = towerButton;
				break;
			}
		}

		m_selectedTowerButton.reset();
	}

	// update tower buttons
	InteractivePanel::update();

	// update m_clickToPlaceTowerHandler state
	m_clickToPlaceTowerHandler->update(m_playStateTowers);
	//set handler state to towers
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_playStateTowers->size(); i++)
	{
		(*m_playStateTowers)[i]->setClickToPlaceTowersHandlerState(m_clickToPlaceTowerHandler->getState());
	}

	// update labels
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		if (Text* pText = dynamic_cast<Text*>(m_gameObjects[i].get()))
		{
			if(pText->getDynamic()) updateLabel(pText);
		}
	}
}

void TowersPanel::clean()
{
	// Cleaning background texture
	m_backgroundTexture->clean();

	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		// Cleaning text textures
		m_gameObjects[i]->clean();
	}
}

void TowersPanel::handleEvents()
{
	// handle selected button if there is, otherwise handle all buttons
	if (m_selectedTowerButton != nullptr)
	{
		if (m_selectedTowerButton->isSelected())
		{
			m_selectedTowerButton->handleEvent();
		}
	}
	else
	{
		TowerInteractivePanel::handleEvents();
	}
}

void TowersPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// get towers' cost
	m_towersCosts = TheTowerFactory::Instance()->getTowersCostValue();

	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load buttons
		if (std::unique_ptr<TowerButton> pButton = std::unique_ptr<TowerButton>(dynamic_cast<TowerButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<TowerButton>(std::move(pButton.get())));
			gameObjects[i].release();
		}
		else
		{
			// load static texts
			if (Text* pText = dynamic_cast<Text*>(gameObjects[i].get()))
			{
				if (!pText->getDynamic()) updateLabel(pText);
			}

			m_gameObjects.push_back(std::move(gameObjects[i]));
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

void TowersPanel::updateLabel(Text* pText)
{
	std::string labelId =pText->getLabelID();

	if (labelId == "") return;

	if(labelId == UIConsts::healthLabelID) pText->setMessage(std::to_string(m_gameSessionData->gameHealth));
	else if(labelId == UIConsts::agateResourceLabelID) pText->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::GREEN].value));
	else if(labelId == UIConsts::amberResourceLabelID) pText->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::YELLOW].value));
	else if(labelId == UIConsts::rubyResourceLabelID) pText->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::RED].value));
	else if(labelId == UIConsts::agateStumpCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::stump]));
	else if(labelId == UIConsts::agatePineCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::pine]));
	else if(labelId == UIConsts::agateOakCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::oak]));
	else if (labelId == UIConsts::amberStumpCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::stump]));
	else if (labelId == UIConsts::amberPineCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::pine]));
	else if (labelId == UIConsts::amberOakCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::oak]));
	else if (labelId == UIConsts::rubyStumpCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::stump]));
	else if (labelId == UIConsts::rubyPineCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::pine]));
	else if (labelId == UIConsts::rubyOakCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::oak]));
	else if (labelId == UIConsts::frozenBushCostLabelID) pText->setMessage(std::to_string(m_towersCosts[GameObjectConsts::frozenBush]));
	else 
	{
		std::cout << "Could not found " << labelId << " labelID.\n";
	}

	pText->update();
	pText = nullptr;
}

std::unique_ptr<Panel> TowersPanelCreator::create() const
{
	return std::make_unique<TowersPanel>();
}
