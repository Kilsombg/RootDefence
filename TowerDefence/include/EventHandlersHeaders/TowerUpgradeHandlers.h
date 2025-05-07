#ifndef __TowerUpgradeHandlers__
#define __TowerUpgradeHandlers__

#include "../EntitiesHeaders/Tower.h"

#include<memory>

/**
* Base class for tower upgrades buttons handlers
* 
* each tower will have two upgrade types.
*/
class BaseTowerUpgradeHandlers
{
public:
	// handle upgrade
	virtual void handleUpgradeEvent(std::shared_ptr<Tower> activeTower, int upgradeID) = 0;
};




/**
* Handler class for tower upgrades
*/
class TowerUpgradeHandlers : public BaseTowerUpgradeHandlers
{
public:
	/** handle upgrade
	* 
	* @param activeTower - tower to be upgraded
	* @param upgradeID - id of the choosed upgrade
	*/
	void handleUpgradeEvent(std::shared_ptr<Tower> activeTower, int upgradeID) override;

private:
	/**
	* Look for attribute and upgrade it.
	* 
	* @param activeTower - tower to be upgraded
	* @param upgradeID - id of the choosed upgrade
	* 
	* @return true on success, otherwise false
	*/
	bool upgradeTowerAttribute(std::shared_ptr<Tower> activeTower, int upgradeID);
};

#endif // !__TowerUpgradeHandlers__
