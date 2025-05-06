#ifndef __TowerUpgradeHandlers__
#define __TowerUpgradeHandlers__

#include "../EntitiesHeaders/Tower.h"

#include<memory>

/**
* Base class for tower upgrades buttons handlers
* 
* each tower will have three upgrade types.
*/
class BaseTowerUpgradeHandlers
{
public:
	virtual void handleUpgradeOneEvent(std::shared_ptr<Tower> activeTower) = 0;
	virtual void handleUpgradeTwoEvent(std::shared_ptr<Tower> activeTower) = 0;
	virtual void handleUpgradeThreeEvent(std::shared_ptr<Tower> activeTower) = 0;
};




/**
* Handler class for tower upgrades
*/
class TowerUpgradeHandlers : public BaseTowerUpgradeHandlers
{
public:
	void handleUpgradeOneEvent(std::shared_ptr<Tower> activeTower) override;
	void handleUpgradeTwoEvent(std::shared_ptr<Tower> activeTower) override;
	void handleUpgradeThreeEvent(std::shared_ptr<Tower> activeTower) override;
};

#endif // !__TowerUpgradeHandlers__
