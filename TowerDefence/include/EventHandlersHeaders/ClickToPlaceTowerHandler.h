#ifndef __ClickToPlaceListener__
#define __ClickToPlaceListener__

#include "BaseButtonHandler.h".h"

#include "../../include/Constants/ColorsConsts.h"

#include "../EntitiesHeaders/Tower.h"
#include "../EntitiesHeaders/TowerButton.h"

#include "../MapHeaders/Level.h"

#include "../UtilsHeaders/Vector2D.h"

#include<vector>
#include<memory>


enum ClickToPlaceTowerStates
{
	IDLE = 0,
	MOVING = 1,
	PLACING = 2,
	INTERRUPTED = 3
};

class ClickToPlaceTowerHandler : public BaseButtonHandler
{
public:
	ClickToPlaceTowerHandler();

	/**
	* handle click event send from TowerButton
	*/
	void handleEvent(Button* sourceButton) override;
	void update(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> gameObjects);
	void render();
	void clean();


	// getters and setters

	std::shared_ptr<Tower>& getShadowObject();
	
	void setLevel(std::shared_ptr<Level> level);

	ClickToPlaceTowerStates getState();

private:
	/**
	* set active tower when clicked in IDLE state
	*/
	void handleIdleState(Button* sourceButton);
	/**
	* set state to PLACING when clicked in MOVING state
	*/
	void handleMovingState(Button* sourceButton);
	/**
	* create shadow object coressponding to active button's towerName
	*/
	void createShadowObject();
	/**
	* update state
	*/
	void updateState(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> gameObjects);
	void updateShadowObject();
	/**
	* set shadow object position and check whether mouse is over free tower tile
	*/
	void updateMovingState();
	/**
	* set position of shadow object by tile
	*/
	void setShadowObjectPosition();
	/**
	* interrupt the event
	*/
	void interrupt();
	/**
	* add object into playState towers
	*/
	bool addObject(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> gameTowers);

	ClickToPlaceTowerStates m_state;
	TowerButton* m_activeButton;
	std::shared_ptr<Tower> m_shadowObject;
	ColorsConsts::Color m_shadowObjectRadiusColor;
	bool m_canPlace;
	bool m_isMouseOnFreeTowerTile;
	std::shared_ptr<Level> pLevel;
};

#endif // !__ClickToPlaceListener__
