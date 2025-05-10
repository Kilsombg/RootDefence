#ifndef __PlayStateUI__
#define __PlayStateUI__

#include "../CommonHeaders/StateUI.h"

#include "../../DataHeaders/GameSessionData.h"

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


	// getters and setters

	void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers);

	void setLevel(std::shared_ptr<Level> level);
	
	void setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData);

private:
	std::shared_ptr<Level> pLevel;

	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_playStateTowers;

	std::shared_ptr<GameSessionData> m_gameSessionData;
};

#endif // !__PlayStateUI__