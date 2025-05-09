#ifndef __PurchaseManager__
#define __PurchaseManager__

#include "../DataHeaders/GameSessionData.h"

#include "../EntitiesHeaders/Tower.h"

#include<string>
#include<memory>
#include<map>

/**
* Manages purchases inside PlayState.
* 
* Check if enough resources with canPurchase() methods. Make sure to execute purchase() methods after making a purchase.
* 
* Used for purchasing:
* - towers
* - tower upgrades
* 
* PurchaseManager is created on PlayState enter.
*/
class PurchaseManager
{
public:
	static std::shared_ptr<PurchaseManager> Instance();

	void clean();

	/**
	* Set game session data
	*/
	void setGameSessionData(std::shared_ptr<GameSessionData> gameSessionData);

	/**
	* Check if there are enough resources to buy the tower.
	* 
	* @param towerName - get tower cost by his towerName.
	* @param towerColor - which resource color to check, tower color and upgrade color coincide
	* 
	* @return true if there are enough resources.
	*/
	bool canPurchaseTower(std::string towerName, std::string towerColor);
	/**
	* Deduct tower's cost resources from gameSession data. It is invoked after canPurchaseTower(), 
	* so it doesn't need verification of enough resources.
	* 
	* Execute this after placing tower.
	* 
	* @param towerCostResource - needed resources to purchase tower
	*/
	void purchaseTower(Resource towerCostResource);

	/**
	* Check if there are enough resources to buy the tower upgrade.
	*
	* @param towerUpgradeData - upgrade data from active tower
	* @param towerColor - which resource color to check, tower color and upgrade color coincide.
	* 
	* @return true if there are enough resources.
	*/
	bool canPurchaseUpgrade(TowerUpgradeData towerUpgradeData, std::string towerColor);
	/**
	* Deduct tower's cost resources from gameSession data. It is invoked after canPurchaseUpgrade(),
	* so it doesn't need verification of enough resources.
	*
	* Execute this after upgrading.
	*
	* @param upgradeCost - upgrade cost that will be deducted
	* @param towerColor - which resource color to check, tower color and upgrade color coincide.
	*/
	void purchaseUpgrade(int upgradeCost, std::string towerColor);

private:
	PurchaseManager();
	static std::shared_ptr<PurchaseManager> s_pInstance;

	/**
	* Gets the tower's cost from the map.
	* 
	* If not found get a tower data from TowerFactory.
	* 
	* @return tower's cost.
	*/
	int getTowerCostByName(std::string towerName);

	// pointer to the gameSession data.
	std::shared_ptr<GameSessionData> m_gameSessionData;
	// map of all the towers costs. *WARNING* not included colors *WARNING*
	std::map<std::string, int> m_towerCosts;
};

typedef PurchaseManager ThePurchaseManager;

#endif // !__PurchaseManager__
