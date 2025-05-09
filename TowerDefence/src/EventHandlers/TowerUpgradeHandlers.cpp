#include "../../include/EventHandlersHeaders/TowerUpgradeHandlers.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/ManagersHeaders/PurchaseManager.h"

#include<string>

void TowerUpgradeHandlers::handleUpgradeEvent(std::shared_ptr<Tower> activeTower, int upgradeID)
{
	// if tower not passed, then return
	if (activeTower.use_count() == 0) return;

	// get upgrade data
	auto& data = activeTower->getTowerUpgradesData()[upgradeID];

	// if we maxed this upgrade, then return
	if (data.nextLevel >= data.maxLevel) return;

	// set new value to the attribute
	if (upgradeTowerAttribute(activeTower, upgradeID))
	{
		// purchase upgrade
		int cost = activeTower->getTowerUpgradesData()[upgradeID].costs[data.nextLevel];
		PurchaseManager::Instance()->purchaseUpgrade(cost, activeTower->getColor());

		// set next level on success
		data.nextLevel++;
	};
}

bool TowerUpgradeHandlers::upgradeTowerAttribute(std::shared_ptr<Tower> activeTower, int upgradeID)
{
	// get upgrade data
	auto data = activeTower->getTowerUpgradesData()[upgradeID];

	// set new value to the attribute
	if (data.statName == LoaderParamsConsts::damage) { activeTower->setDamage(data.values[data.nextLevel]); return true; }
	if (data.statName == LoaderParamsConsts::radius) { activeTower->setRadius(data.values[data.nextLevel]); return true; }
	if (data.statName == LoaderParamsConsts::attackSpeed) { activeTower->setAttackSpeed(data.values[data.nextLevel]); return true; }

	return false;
}
