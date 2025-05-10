#ifndef __TowersPanel__
#define __TowersPanel__

#include "../CommonHeaders/InteractivePanel.h"
#include "../CommonHeaders/PanelCreator.h"

#include "../../EntitiesHeaders/Tower.h"

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
	void load(std::vector<std::unique_ptr<GameObject>> gameObjects) override;

	void loadCallbacks() override;

	std::shared_ptr<ClickToPlaceTowerHandler> getClickToPlaceTowerHandler();

	void setLevel(std::shared_ptr<Level> level);

private:
	void setTowerButtonCallbacks();
	/**
	* set a pointer to the level for each tower button.
	*/
	void setTowerButtonLevel();

	typedef std::function<void(Button*)> TowerButtonCallback;
	std::map<std::string, TowerButtonCallback> m_towerButtonCallbacks;

	std::shared_ptr<ClickToPlaceTowerHandler> m_clickToPlaceTowerHandler;
	std::shared_ptr<Level> pLevel;
};


class TowersPanelCreator : public PanelCreator
{
	virtual std::unique_ptr<Panel> create() const override;

};

#endif // !__TowersPanel__
