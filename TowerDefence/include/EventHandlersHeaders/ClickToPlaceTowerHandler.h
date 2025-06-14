#ifndef __ClickToPlaceListener__
#define __ClickToPlaceListener__

#include "BaseButtonHandler.h"

#include "../../include/Constants/ColorsConsts.h"

#include "../EntitiesHeaders/Tower.h"
#include "../EntitiesHeaders/TowerButton.h"

#include "../MapHeaders/Level.h"

#include<vector>
#include<memory>

/**
* Button states.
*/
enum ClickToPlaceTowerStates
{
	IDLE = 0, // not interracted
	MOVING = 1, // when clicked and dummyTower on screen
	PLACING = 2, // second clicked handled
	INTERRUPTED = 3 // interruption event occured
};

/**
* Click to place handler for tower placement.
* 
* When clicked on TowerButton, handleEvent() is called for handling the state of the event.
* 
* states of handler:
* - IDLE : do nothing, waits for click on towerButton to switch state to MOVING and creates shadowObject.
* - MOVING: render shadowObject on screen untill clicked on free tower space or outside map, then switch to PLACING.
* - PLACING: calls addObject() to add tower object to the game.
* - INTERRUPTED: return handler to default values and switch to IDLE.
* 
* * Warning: level, that is played on, needs to be set to work.
*/
class ClickToPlaceTowerHandler : public BaseButtonHandler
{
public:
	ClickToPlaceTowerHandler();

	/**
	* Handle click event send from TowerButton.
	* 
	* If sourceButton is nullptr then interrupt handler.
	* Handle corresponding state otherwise.
	*/
	void handleEvent(Button* sourceButton) override;
	/**
	* Update event.
	*/
	void update(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> gameObjects);
	/**
	* Renders tower shadow object on screen.
	*/
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
	* Update based on the handler's state.
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
