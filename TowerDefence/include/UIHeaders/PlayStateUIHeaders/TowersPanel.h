#ifndef __TowersPanel__
#define __TowersPanel__

#include "../CommonHeaders/InteractivePanel.h"

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

#endif // !__TowersPanel__
