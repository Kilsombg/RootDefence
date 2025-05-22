#ifndef __TowersPanel__
#define __TowersPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Tower.h"
#include "../../EntitiesHeaders/Text.h"
#include "../../EntitiesHeaders/Texture.h"

#include "../../DataHeaders/GameSessionData.h"

#include "../../MapHeaders/Level.h"

#include "../../EventHandlersHeaders/ClickToPlaceTowerHandler.h"

#include<map>
#include<string>
#include<memory>

class TowersPanel : public TowerInteractivePanel
{
public:
	TowersPanel();
	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;
	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;
	/**
	* Load needed dependencies not included from StateParser.
	*/
	void loadDependencies(std::shared_ptr<Level> level, std::shared_ptr<GameSessionData> gameSessionData);

	void loadCallbacks() override;

	// getters and setters
	std::shared_ptr<ClickToPlaceTowerHandler> getClickToPlaceTowerHandler();

	void setLevel(std::shared_ptr<Level> level);

	void setGameSeesionData(std::shared_ptr<GameSessionData> gameSessionData);

private:
	void setTowerButtonCallbacks();
	/**
	* set a pointer to the level for each tower button.
	*/
	void setTowerButtonLevel();
	/**
	* update labels' value.
	*/
	void updateLabel(Text* pText);

	static void s_playToPause();

	typedef std::function<void(Button*)> TowerButtonCallback;
	std::map<std::string, TowerButtonCallback> m_towerButtonCallbacks; // callbacks for creating tower buttons

	typedef void(*ButtonCallback)();
	std::map<std::string, ButtonCallback> m_buttonCallbacks; // callbacks for start wave and settings button

	std::shared_ptr<TowerButton> m_selectedTowerButton;

	std::shared_ptr<ClickToPlaceTowerHandler> m_clickToPlaceTowerHandler;
	std::shared_ptr<Level> pLevel;

	std::shared_ptr<GameSessionData> m_gameSessionData;
	std::map<std::string, int> m_towersCosts; // map of each tower with their cost
};


class TowersPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;

};

#endif // !__TowersPanel__
