#ifndef __PlayStateUI__
#define __PlayStateUI__

#include "../CommonHeaders/StateUI.h"

#include "../../EntitiesHeaders/Tower.h"
#include "../../EntitiesHeaders/Button.h"

#include "../../MapHeaders/Level.h"

#include<vector>
#include<string>
#include<memory>

class PlayStateUI : public StateUI
{
public:
	PlayStateUI(std::string stateID);

	void draw() override;
	void load() override;
	void handleEvents() override;
	
	void update();

	void clean() override;

	template <typename T>
	T* getPanel()
	{
		for (std::vector<std::unique_ptr<Panel>>::size_type i = 0; i < m_panels.size();i++)
		{
			if (T* panel = dynamic_cast<T*>(m_panels[i].get()))
			{
				return panel;
			}
		}

		return nullptr;
	};

	void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers);
	void setLevel(std::shared_ptr<Level> level);

private:
	std::shared_ptr<Level> pLevel;
	/**
	* load objects in all panels
	*/
	void loadPanels(std::vector<std::unique_ptr<GameObject>> gameObjects);
	/**
	* load panel's objects
	*/
	template <typename TButton, typename TPanel>
	void loadPanel(std::vector<std::unique_ptr<GameObject>>& gameObjects)
	{
		// declare object vector for each panel
		std::vector<std::unique_ptr<Button>> panelObjects;

		// load relevant objects to corresponding panel
		for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
		{
			if (std::unique_ptr<TButton> pButton = std::unique_ptr<TButton>(dynamic_cast<TButton*>(gameObjects[i].get())))
			{
				panelObjects.push_back(std::move(pButton));
				pButton = nullptr;
				gameObjects[i].release();
			}
		}

		// create the panel and load objects into them
		std::unique_ptr<TPanel> panel = std::make_unique<TPanel>();
		panel->setButtonObjects(std::move(panelObjects));


		// add panels into vector
		m_panels.push_back(std::move(panel));
	};

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_playStateTowers;
};

#endif // !__PlayStateUI__