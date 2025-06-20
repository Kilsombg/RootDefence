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

// forward declaration
enum ClickToPlaceTowerStates;

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

// methods for nlohmann/json parsing.

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
	Tower();
	Tower(const Tower& tower);

	// getter and setters

	std::string getName();

	std::string getTexureID();

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

	double getDamageDealt();

	std::weak_ptr<Enemy> getTargetEnemy() const;

	ArrayOf2TowerUpgradesData& getTowerUpgradesData();
	void setTowerUpgradesData(ArrayOf2TowerUpgradesData data);

	void setClickToPlaceTowersHandlerState(ClickToPlaceTowerStates state);

	void setMouseOverRadius(bool mouseOverRadiusUpgrade);
	bool getMouseOverRadius();

	void setNextRadiusUpgradeValue(int nextRadiusUpgradeValue);

	// override methods
	virtual void update() override;
	virtual void draw() override;
	void load(const std::shared_ptr<LoaderParams> pParams) override;



	void handleEvent();

	/**
	* Get tower type by tower color from xml towerButtons.
	* 
	* @return string value with tower type.
	*/
	std::string getTowerType(std::string towerColor);
	/**
	* look for enemy in radius to target
	* @param enemies is a vector of objects in current state
	*/
	virtual void targetEnemy(std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> enemies);
	/**
	* check whether the enemy is in tower radius
	*/
	bool inRadius(std::shared_ptr<Enemy> enemy);
	/**
	* execute attack interval
	*/
	virtual void aimEnemy();
	/**
	* when enemy got hit by tower's projectile, increase damage dealt.
	*/
	void incrementDealtDamage(float damage);
	/**
	* @return true if selected, otherwise false
	*/
	bool isSelected();

	/**
	* set up tower after placed
	*/
	void placed();


private:
	std::string m_name;
	std::string m_projectileID;
	float m_damage;
	float m_radius; // range
	Resource m_baseCost;
	float m_attackSpeed;
	Timer m_attackTimer;
	std::string m_color;
	double m_damageDealt; //damage is counted only if its projectile hit the target enemy.
	Resource m_spentResources; /// spent resources on tower.

	std::weak_ptr<Enemy> m_targetEnemy;

	SelectOnClickEventHandler m_selectOnClickEventHandler;

	// state of clickToPlaceTowersHandler to detect when towerButton is selected, so it stop from selecting the tower.
	ClickToPlaceTowerStates clickToPlaceTowersHandlerState;

	ArrayOf2TowerUpgradesData m_towerUpgradesData;

	bool m_mouseOverRadiusUpgrade; // flag for drawing upgrade radius on screen
	int m_nextRadiusUpgradeValue; // needed radius for drawing on screen
};

class TowerCreator : public BaseCreator
{
	std::unique_ptr<GameObject> create() const override;
};

#endif // !__Tower__