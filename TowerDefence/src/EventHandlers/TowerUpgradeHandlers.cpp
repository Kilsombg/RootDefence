#include "../../include/EventHandlersHeaders/TowerUpgradeHandlers.h"

#pragma region handlers for tower

void TowerUpgradeHandlers::handleUpgradeOneEvent(std::shared_ptr<Tower> activeTower)
{
}

void TowerUpgradeHandlers::handleUpgradeTwoEvent(std::shared_ptr<Tower> activeTower)
{
	if (activeTower.use_count() == 0) return;
}

void TowerUpgradeHandlers::handleUpgradeThreeEvent(std::shared_ptr<Tower> activeTower)
{
}

#pragma endregion

