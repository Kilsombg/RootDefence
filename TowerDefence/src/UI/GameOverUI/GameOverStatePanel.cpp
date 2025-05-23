#include "../../../include/UIHeaders/GameOverUIHeaders/GameOverStatePanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/GameStateHeaders/MainMenuState.h"
#include "../../../include/GameStateHeaders/PlayState.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

GameOverStatePanel::GameOverStatePanel() : MenuInteractivePanel()
{
}

void GameOverStatePanel::draw()
{
	// draw background
	m_backgroundTexture->draw();

	// draw buttons
	MenuInteractivePanel::draw();

	// draw labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->draw();
	}
}

void GameOverStatePanel::update()
{
	// update buttons
	MenuInteractivePanel::update();

	// update dynamic labels
	updateDynamicLabel();
}

void GameOverStatePanel::clean()
{
	MenuInteractivePanel::clean();
}

void GameOverStatePanel::handleEvents()
{
	MenuInteractivePanel::handleEvents();
}

void GameOverStatePanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load buttons
		if (std::unique_ptr<MenuButton> pButton = std::unique_ptr<MenuButton>(dynamic_cast<MenuButton*>(gameObjects[i].get())))
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
	}

	// load callbacks
	loadCallbacks();
}

void GameOverStatePanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::mainMenuButtonCallbackID] = s_gameOverToMain;
	m_callbacks[LoaderParamsConsts::restartButtonCallbackID] = s_restartPlay;

	setCallbacks();
}

void GameOverStatePanel::setCurrentWaveID(int currentWaveID)
{
	m_currentWaveID = currentWaveID;
}

void GameOverStatePanel::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<MainMenuState>());
}

void GameOverStatePanel::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<PlayState>());
}

void GameOverStatePanel::updateDynamicLabel()
{
	// update values
	std::string waveLevel = "Wave " + std::to_string(m_currentWaveID);
	m_labelsMap[UIConsts::gameOverWaveLabel]->setMessage(waveLevel);

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->update();
	}
}

std::unique_ptr<Panel> GameOverStatePanelCreator::create() const
{
	return std::make_unique<GameOverStatePanel>();
}
