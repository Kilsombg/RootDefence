#include "../../../include/UIHeaders/VictoryStateUIHeaders/VictoryStatePanel.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"
#include "../../../include/EntitiesHeaders/Text.h"

#include "../../../include/GameStateHeaders/PlayState.h"
#include "../../../include/GameStateHeaders/MainMenuState.h"

#include "../../../include/Game.h"

VictoryStatePanel::VictoryStatePanel()
{
}

void VictoryStatePanel::draw()
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

void VictoryStatePanel::update()
{
	// update buttons
	MenuInteractivePanel::update();
}

void VictoryStatePanel::clean()
{
	MenuInteractivePanel::clean();
}

void VictoryStatePanel::handleEvents()
{
	MenuInteractivePanel::handleEvents();
}

void VictoryStatePanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
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

	// update static labels
	updateStaticLabel();
	
	// load callbacks
	loadCallbacks();
}

void VictoryStatePanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::mainMenuButtonCallbackID] = s_victoryToMain;
	m_callbacks[LoaderParamsConsts::restartButtonCallbackID] = s_restartPlay;

	setCallbacks();
}

void VictoryStatePanel::setCurrentWaveID(int currentWaveID)
{
	m_currentWaveID = currentWaveID;
}

void VictoryStatePanel::s_victoryToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<MainMenuState>());
}

void VictoryStatePanel::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<PlayState>());
}

void VictoryStatePanel::updateStaticLabel()
{
	// update values
	std::string waveLevel = "Wave " + std::to_string(m_currentWaveID);
	m_labelsMap[UIConsts::victorWaveLabel]->setMessage(waveLevel);

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->update();
	}
}

std::unique_ptr<Panel> VictoryStatePanelCreator::create() const
{
	return std::make_unique<VictoryStatePanel>();
}
