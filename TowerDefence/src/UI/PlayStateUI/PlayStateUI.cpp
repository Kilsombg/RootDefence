#include "../../../include/UIHeaders/PlayStateUIHeaders/PlayStateUI.h"

#include "../../../include/EntitiesHeaders/TowerUpgradedButton.h"
#include "../../../include/EntitiesHeaders/TowerButton.h"

#include "../../../include//UIHeaders/CommonHeaders/InteractivePanel.h"

#include "../../../include//UIHeaders/PlayStateUIHeaders/TowerUpgradePanel.h"
#include "../../../include//UIHeaders/PlayStateUIHeaders/TowersPanel.h"

#include "../../../include/UtilsHeaders/StateParser.h"
#include "../../../include/UtilsHeaders/TextureManager.h"

PlayStateUI::PlayStateUI(std::string stateID) : StateUI(stateID)
{
}

void PlayStateUI::draw()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		m_panels[i]->draw();
	}
}

void PlayStateUI::load()
{
	// load state objects and textures
	StateParser stateParser;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	stateParser.parseState("./src/test.xml", s_stateID, &gameObjects, &m_textureIDList);

	// load panels
	loadPanels(std::move(gameObjects));

	// load panels callbacks and play state towers
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		if (TowerInteractivePanel* towerInteractivePanel = dynamic_cast<TowerInteractivePanel*>(m_panels[i].get()))
		{
			towerInteractivePanel->setPlayStateTowers(m_playStateTowers);
			towerInteractivePanel->loadCallbacks();
			towerInteractivePanel = nullptr;
		}
	}
}

void PlayStateUI::handleEvents()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		if (InteractivePanel* interactivePanel = dynamic_cast<InteractivePanel*>(m_panels[i].get()))
		{
			interactivePanel->handleEvents();
		}
	}
}

void PlayStateUI::update()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		m_panels[i]->update();
	}
}

void PlayStateUI::clean()
{
	// cleaning textures
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
}

void PlayStateUI::setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers)
{
	m_playStateTowers = playStateTowers;
}

void PlayStateUI::setLevel(std::shared_ptr<Level> level)
{
	pLevel = level;
}

void PlayStateUI::loadPanels(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load panels
	loadPanel<TowerUpgradedButton, TowerUpgradePanel>(gameObjects);
	loadPanel<TowerButton, TowersPanel>(gameObjects);

	// set level to TowersPanel
	auto towersPanel = getPanel<TowersPanel>();
	towersPanel->setLevel(pLevel);
	towersPanel->getClickToPlaceTowerHandler()->setLevel(pLevel);
	towersPanel = nullptr;

	// clear objects
	gameObjects.clear();
}
