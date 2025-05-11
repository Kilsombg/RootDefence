#ifndef __Tower__
#define __Tower__

#include "SDLGameObject.h"
#include "Enemy.h"

#include "../DataHeaders/GameSessionData.h"

#include "../EventHandlersHeaders/SelectOnClickEventHandler.h"

#include "../UtilsHeaders/BaseCreator.h"
#include "../UtilsHeaders/Timer.h"

#include<string>
#include<array>
#include<memory>

#include<nlohmann\json.hpp>
using json = nlohmann::json;

/**
* Tower upgrades data
*
* contains information about the upgrades for a tower.
*/
struct TowerUpgradeData
{
	// stat to be changed
	std::string statName;
	// vector with each level's values
	std::vector<float> values;
	// vector with each level's costs
	std::vector<int> costs;
	// max level upgrade can get
	int maxLevel;
	// next upgrade level
	int nextLevel;
};

typedef std::array<TowerUpgradeData, 2> ArrayOf2TowerUpgradesData;

void to_json(json& j, const TowerUpgradeData& data);
void from_json(const json& j, TowerUpgradeData& data);

void to_json(json& j, const ArrayOf2TowerUpgradesData& arrayOf3TowerUpgradesData);
void from_json(const json& j, ArrayOf2TowerUpgradesData& arrayOf3TowerUpgradesData);

void to_json(json& j, const std::map<std::string, std::shared_ptr<ArrayOf2TowerUpgradesData>>& dataMap);
void from_json(const json& j, std::map<std::string, std::shared_ptr<ArrayOf2TowerUpgradesData>>& dataMap);

/**
* Base class for towers
*/
class Tower : public SDLGameObject
{
public:
	enum TowerType
	{
		BASIC = 0, ///< balanced tower
		FAST = 1, ///< fast attack speed, low damage tower
		SLOW = 2 ///< slow attack speed, high damage tower
	};

	Tower();
	Tower(const Tower& tower);

	// getter and setters
	TowerType getTowerType();

	float getAttackSpeed() const;
	void setAttackSpeed(float attackSpeed);

	float getDamage() const;
	void setDamage(float damage);

	float getRadius() const;
	void setRadius(float radius);

	Resource getBaseCost() const;

	std::string getProjectileID();

	std::string getColor();
	void setColor(std::string color);

	Resource getSpentResources() const;
	void setSpentResources(Resource spentResource);

	std::weak_ptr<Enemy> getTargetEnemy() const;

	ArrayOf2TowerUpgradesData& getTowerUpgradesData();
	void setTowerUpgradesData(ArrayOf2TowerUpgradesData data);

	// override methods
	virtual void update() override;
	virtual void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams);



	void handleEvent();

	/**
	* look for enemy in radius to target
	* @param enemies is a vector of objects in current state
	*/
	void targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies);
	/**
	* check wheather the enemy is in tower radius
	*/
	bool inRadius(std::shared_ptr<Enemy> enemy);
	/**
	* execute attack interval
	*/
	void aimEnemy();

	bool isSelected();

	/**
	* set up tower after placed
	*/
	void placed();


private:
	std::string m_projectileID;
	float m_damage;
	float m_radius; // range
	Resource m_baseCost;
	float m_attackSpeed;
	Timer m_attackTimer;
	TowerType m_towerType;
	std::string m_color;

	Resource m_spentResources; /// spent resources on tower.

	std::weak_ptr<Enemy> m_targetEnemy;

	SelectOnClickEventHandler m_selectOnClickEventHandler;

	ArrayOf2TowerUpgradesData m_towerUpgradesData;
};

class TowerCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Tower__