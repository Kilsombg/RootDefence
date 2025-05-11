#ifndef __SellTowerHandler__
#define __SellTowerHandler__

#include "../EntitiesHeaders/Tower.h"

#include "../MapHeaders/Level.h"

#include<memory>
#include<vector>

/**
* Event handler for selling selected tower.
*/
class SellTowerHandler
{
public:
	/**
	* Handle selling tower.
	* 
	* @param selectedTower - tower to be sold
	*/
	void handleSellTowerEvent(std::shared_ptr<Tower> selectedTower);
	/**
	* Set pointer to PlayState's towers.
	*/
	void setPlayStateTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> playStateTowers);
	/**
	* Set pointer to Map's level.
	*/
	void setLevel(std::shared_ptr<Level> level);

private:
	
	// pointer to PlayState towers.
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_playStateTowers;
	// pointer to level
	std::shared_ptr<Level> pLevel;
};

#endif // !__SellTowerHandler__
