#ifndef __TowerUnlockManager__
#define __TowerUnlockManager__

#include "../DataHeaders/DTOsHeaders/TowerUnlocksDTO.h"

#include<memory>
#include<vector>
#include<string>

/**
* Manaages unlocking towers.
* 
* Lives as much as LevelManager. When player level up
* calls unlockTowerByLevelUp() to check if tower needs to be unlocked.
*/
class TowerUnlockManager
{
public:
	static std::shared_ptr<TowerUnlockManager> Instance();

	std::string unlockTowerByLevelUp();
	/**
	* Return true if tower is unlocked.
	*/
	bool isUnlocked(std::string towerName);

private:
	TowerUnlockManager();
	static std::shared_ptr<TowerUnlockManager> s_pInstance;

	std::shared_ptr<std::vector<TowerUnlocksDTO>> m_towerUnlocks;
};

typedef TowerUnlockManager TheTowerUnlockManager;

#endif // !__TowerUnlockManager__
