#ifndef __SellManager__
#define __SellManager__

#include "../DataHeaders/GameSessionData.h"

#include "../EntitiesHeaders/Tower.h"

#include<memory>

/**
* Manages selling and spent resources on towers in PlayState.
* 
* Use updateSpentResources() on each tower purchase.
* 
* Used for selling:
* - towers
* 
* SellManager is created on PlayState enter.
*/
class SellManager
{
public:
	static std::shared_ptr< SellManager> Instance();

	void clean();

	/**
	* Set a pointer to active tower from TowerUpgradePanel.
	*/
	void setSelectedTower(std::shared_ptr<Tower> selectedTower);

	/**
	* Set a pointer to game session data.
	*/
	void setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData);

	/**
	* Update spent on active tower.
	* 
	* Increases active tower's spent resources. Execute this on each tower specified purchase.
	* 
	* @param resource spent from a tower purchase.
	*/
	void updateSpentResources(Resource resource);

	/**
	* Get back m_baseSellPercentage of tower's spent resources.
	* 
	* Execute this before deleting selected tower.
	*/
	void sellSelectedTower();

private:
	SellManager();
	static std::shared_ptr< SellManager> s_pInstance;

	// base sell percentage from spent resources.
	float m_baseSellPercentage;

	// selected tower in PlayState.
	std::shared_ptr<Tower> m_selectedTower;

	// pointer to the gameSession data.
	std::shared_ptr<GameSessionData> m_gameSessionData;
};

typedef SellManager TheSellManager;

#endif // !__SellManager__
