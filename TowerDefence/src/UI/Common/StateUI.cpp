#include "../../../include/UIHeaders/CommonHeaders/StateUI.h"

#include "../../../include/UIHeaders/CommonHeaders/InteractivePanel.h"

#include "../../../include/UtilsHeaders/TextureManager.h"
#include "../../../include/UtilsHeaders/StateParser.h"

StateUI::StateUI(std::string stateID)
{
	s_stateID = stateID;
}

void StateUI::draw()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		m_panels[i]->draw();
	}
}

void StateUI::update()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		m_panels[i]->update();
	}
}

void StateUI::load()
{
	// load state objects and textures
	StateParser stateParser;
	stateParser.parseState("./src/test.xml", s_stateID, &m_textureIDList, &m_panels);
}

void StateUI::clean()
{
	// cleaning textures
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	// Cleaning panels
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		m_panels[i]->clean();
	}
}

void StateUI::handleEvents()
{
	for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size(); i++)
	{
		if (InteractivePanel* interactivePanel = dynamic_cast<InteractivePanel*>(m_panels[i].get()))
		{
			interactivePanel->handleEvents();
		}
	}
}
