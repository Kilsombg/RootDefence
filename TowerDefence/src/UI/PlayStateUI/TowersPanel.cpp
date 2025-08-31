#include "../../../include/UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/TowerButton.h"
#include "../../../include/EntitiesHeaders/Text.h"
#include "../../../include/EntitiesHeaders/MenuButton.h"

#include "../../../include/GameStateHeaders/PauseState.h"

#include "../../../include/UtilsHeaders/TowerFactory.h"
#include "../../../include/UtilsHeaders/GameStateMachine.h"
#include "../../../include/UtilsHeaders/InputHandler.h"
#include "../../../include/UtilsHeaders/TextureManager.h"

#include "../../../include/WaveHeaders/WaveManager.h"

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
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		// disable start wave button, if wave already started
		if (MenuButton* menuButton = dynamic_cast<MenuButton*>(m_buttonObjects[i].get()))
		{
			if (menuButton->getCallbackID() == LoaderParamsConsts::startWaveCallbackID)
			{
				menuButton->setCurrentRow(TheWaveManager::isActivePlayButton() ? MenuMode::ACTIVE : MenuMode::DISABLED);
			}
			menuButton = nullptr;
		}

		m_buttonObjects[i]->draw();
	}

	// draw level progress bar
	TheTextureManager::Instance()->drawProgressBar(
		59, 23, 78, 17,
		{ ColorsConsts::levelBG.r, ColorsConsts::levelBG.g, ColorsConsts::levelBG.b, ColorsConsts::levelBG.a },
		{ ColorsConsts::green.r, ColorsConsts::green.g, ColorsConsts::green.b, ColorsConsts::green.a },
		(float)TheGame::Instance()->getProgressManager()->getGameProgress()->level_xp / TheGame::Instance()->getLevelManager()->getNextLevelXP(),
		TheGame::Instance()->getRenderer()
	);

	// draw textures
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// draw labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->draw();
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
	updateDynamicLabel();
}

void TowersPanel::clean()
{
	TowerInteractivePanel::clean();
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

	// handle input

	// change wave with SPACE
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		TheWaveManager::s_activateWave();
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
		else if (std::unique_ptr<MenuButton> pButton = std::unique_ptr<MenuButton>(dynamic_cast<MenuButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<MenuButton>(std::move(pButton.get())));
			gameObjects[i].release();
		}
		// load labels
		else if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_labelsMap[pText->getLabelID()] = std::move(pText);
			gameObjects[i].release();
		}
		else
		{
			// load textures
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load static labels
	//updateStaticLabel();

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

	// setting up start and settings button callbacks
	m_buttonCallbacks[LoaderParamsConsts::startWaveCallbackID] = TheWaveManager::Instance()->s_activateWave;
	m_buttonCallbacks[LoaderParamsConsts::pauseStateCallbackID] = s_playToPause;

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
		// load tower button callbacks
		if (TowerButton* pButton = dynamic_cast<TowerButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_towerButtonCallbacks.at(pButton->getCallbackID()));
			pButton = nullptr;
		}
		// load start wave and settings button callbacks
		else if (MenuButton* pButton = dynamic_cast<MenuButton*>(m_buttonObjects[i].get()))
		{
			pButton->setCallback(m_buttonCallbacks.at(pButton->getCallbackID()));
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

void TowersPanel::updateStaticLabel()
{
	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		if (!it->second->getDynamic())
		{
			it->second->update();
		}
	}
}

void TowersPanel::updateDynamicLabel()
{
	m_labelsMap[UIConsts::healthLabelID]->setMessage(std::to_string(m_gameSessionData->gameHealth));
	m_labelsMap[UIConsts::waveValueLabel]->setMessage(std::to_string(m_gameSessionData->currentWaveLevel));

	// resources
	m_labelsMap[UIConsts::agateResourceLabelID]->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::GREEN].value));
	m_labelsMap[UIConsts::amberResourceLabelID]->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::YELLOW].value));
	m_labelsMap[UIConsts::rubyResourceLabelID]->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::RED].value));
	m_labelsMap[UIConsts::sapphireResourceLabelID]->setMessage(std::to_string(m_gameSessionData->resources[ResourceType::BLUE].value));
	
	// level label
	m_labelsMap[UIConsts::levelLabelID]->setMessage(std::to_string(TheGame::Instance()->getProgressManager()->getGameProgress()->level));
	m_labelsMap[UIConsts::levelLabelID]->centerText();

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		if (it->second->getDynamic())
		{
			it->second->update();
		}
	}
}

void TowersPanel::s_playToPause()
{
	TheGameStateMachine::Instance()->pushState(std::make_shared<PauseState>());
}

std::unique_ptr<Panel> TowersPanelCreator::create() const
{
	return std::make_unique<TowersPanel>();
}
