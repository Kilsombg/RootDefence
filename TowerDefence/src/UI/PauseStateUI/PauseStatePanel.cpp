#include "../../../include/UIHeaders/PauseStateUIHeaders/PauseStatePanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/LoaderParamsConsts.h"

#include "../../../include/GameStateHeaders/MainMenuState.h"
#include "../../../include/GameStateHeaders/PlayState.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

PauseStatePanel::PauseStatePanel() : MenuInteractivePanel()
{
}

void PauseStatePanel::draw()
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

void PauseStatePanel::update()
{
	// update buttons
	MenuInteractivePanel::update();
}

void PauseStatePanel::clean()
{
	MenuInteractivePanel::clean();
}

void PauseStatePanel::handleEvents()
{
	MenuInteractivePanel::handleEvents();
}

void PauseStatePanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
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

void PauseStatePanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::mainMenuButtonCallbackID] = s_pauseToMain;
	m_callbacks[LoaderParamsConsts::restartButtonCallbackID] = s_restartPlay;
	m_callbacks[LoaderParamsConsts::resumeButtonCallbackID] = s_resumePlay;

	setCallbacks();
}

void PauseStatePanel::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<MainMenuState>());
}

void PauseStatePanel::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(std::make_shared<PlayState>());
}

void PauseStatePanel::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

std::unique_ptr<Panel> PauseStatePanelCreator::create() const
{
	return std::make_unique<PauseStatePanel>();
}
