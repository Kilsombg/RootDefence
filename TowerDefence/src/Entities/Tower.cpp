#include "../../include/EntitiesHeaders/Tower.h"

#include "../../include/Game.h"

#include "../../include/Constants/LoaderParamsConsts.h"
#include "../../include/Constants/GameObjectConsts.h"
#include "../../include/Constants/SettingsConsts.h"
#include "../../include/Constants/ColorsConsts.h"

#include "../../include/DataHeaders/GameSessionData.h"

#include "../../include/EventHandlersHeaders/ClickToPlaceTowerHandler.h"

#include "../../include/ManagersHeaders/PurchaseManager.h"

#include "../../include/UtilsHeaders/Vector2D.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/ProjectileManager.h"
#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/InputHandler.h"


#include<iostream>
#include<functional>

#pragma region TowerUpgradeData functionality

void to_json(json& j, const TowerUpgradeData& data)
{
	j = json{
		{LoaderParamsConsts::statName, data.statName},
		{LoaderParamsConsts::values, data.values},
		{LoaderParamsConsts::costs, data.costs},
		{LoaderParamsConsts::maxLevel, data.maxLevel},
		{LoaderParamsConsts::nextLevel, data.nextLevel}
	};
}

void from_json(const json& j, TowerUpgradeData& data)
{
	// statName
	if (j.contains(LoaderParamsConsts::statName)) {
		j.at(LoaderParamsConsts::statName).get_to(data.statName);
	}

	// values
	if (j.contains(LoaderParamsConsts::values)) {
		j.at(LoaderParamsConsts::values).get_to(data.values);
	}

	// costs
	if (j.contains(LoaderParamsConsts::costs)) {
		j.at(LoaderParamsConsts::costs).get_to(data.costs);
	}

	// maxLevel
	if (j.contains(LoaderParamsConsts::maxLevel))
	{
		j.at(LoaderParamsConsts::maxLevel).get_to(data.maxLevel);
	}

	// nextLevel
	if (j.contains(LoaderParamsConsts::nextLevel))
	{
		j.at(LoaderParamsConsts::nextLevel).get_to(data.nextLevel);
	}
}

void to_json(json& j, const ArrayOf2TowerUpgradesData& arrayOf2TowerUpgradesData)
{
	j = json::array();
	for (const auto& towerUpgrade : arrayOf2TowerUpgradesData) {
		j.push_back(towerUpgrade);
	}
}

void from_json(const json& j, ArrayOf2TowerUpgradesData& arrayOf2TowerUpgradesData)
{
	if (!j.is_array() || j.size() != 2) {
		if (!j.is_array())
		{
			int a = 3;
		}
		if (j.size() != 2)
		{
			int b = 3;
		}
		throw std::runtime_error("Expected array of exactly 2 TowerUpgradeData items");
	}

	for (size_t i = 0; i < 2; ++i) {
		arrayOf2TowerUpgradesData[i] = j.at(i).get<TowerUpgradeData>();
	}
}

void to_json(json& j, const std::map<std::string, std::shared_ptr<ArrayOf2TowerUpgradesData>>& dataMap)
{
	for (const auto& it : dataMap) {
		if (it.second) {
			j[it.first] = *(it.second);
		}
	}
}

void from_json(const json& j, std::map<std::string, std::shared_ptr<ArrayOf2TowerUpgradesData>>& dataMap)
{
	dataMap.clear();
	for (auto it = j.begin(); it != j.end(); ++it) {
		if (it.value().is_null()) {
			dataMap[it.key()] = nullptr;
		}
		else {
			auto arrayOf2TowerUpgradesData = std::make_shared<ArrayOf2TowerUpgradesData>();
			from_json(it.value(), *arrayOf2TowerUpgradesData);
			dataMap[it.key()] = arrayOf2TowerUpgradesData;
		}
	}
}

#pragma endregion


#pragma region Tower functionality

Tower::Tower() : SDLGameObject(), m_projectileID(""), m_attackSpeed(0), m_damage(0), m_radius(0), m_attackTimer(0)
{
	m_spentResources.value = 0;
}

Tower::Tower(const Tower& tower) : SDLGameObject(tower)
{
	m_name = tower.m_name;
	m_projectileID = tower.m_projectileID;
	m_damage = tower.m_damage;
	m_radius = tower.m_radius;
	m_baseCost.type = tower.m_baseCost.type;
	m_baseCost.value = tower.m_baseCost.value;
	m_color = tower.m_color;
	setAttackSpeed(tower.m_attackSpeed);

	m_spentResources = tower.m_spentResources;
}

float Tower::getRadius() const
{
	return m_radius;
}

void Tower::setRadius(float radius)
{
	m_radius = radius;
}

Resource Tower::getBaseCost() const
{
	return m_baseCost;
}

std::string Tower::getName()
{
	return m_name;
}

std::string Tower::getTexureID()
{
	return m_textureID;
}

float Tower::getAttackSpeed() const
{
	return m_attackSpeed;
}

void Tower::setAttackSpeed(float attackSpeed)
{
	m_attackSpeed = attackSpeed;
	float attackInterval = 1 / m_attackSpeed;
	m_attackTimer = Timer(attackInterval, attackInterval);
}

float Tower::getDamage() const
{
	return m_damage;
}

void Tower::setDamage(float damage)
{
	m_damage = damage;
}

std::string Tower::getProjectileID()
{
	return m_projectileID;
}

std::string Tower::getColor()
{
	return m_color;
}

void Tower::setColor(std::string color)
{
	m_color = color;
}

Resource Tower::getSpentResources() const
{
	return m_spentResources;
}

void Tower::setSpentResources(Resource spentResource)
{
	m_spentResources = spentResource;
}

std::weak_ptr<Enemy> Tower::getTargetEnemy() const
{
	return m_targetEnemy;
}

ArrayOf2TowerUpgradesData& Tower::getTowerUpgradesData()
{
	return m_towerUpgradesData;
}

void Tower::setTowerUpgradesData(ArrayOf2TowerUpgradesData data)
{
	m_towerUpgradesData = data;
}

void Tower::setClickToPlaceTowersHandlerState(ClickToPlaceTowerStates state)
{
	clickToPlaceTowersHandlerState = state;
}

void Tower::update()
{
	SDLGameObject::update();

	// check for mouseOver
	m_selectOnClickEventHandler.update();

	aimEnemy();
}

void Tower::draw()
{
	// draw range area when selected
	if (m_selectOnClickEventHandler.isSelected())
	{
		TheTextureManager::Instance()->drawFilledCircle(
			m_position.getX() + m_width / 2, m_position.getY() + m_height / 2, static_cast<int>(m_radius),
			{ ColorsConsts::gray.r, ColorsConsts::gray.g, ColorsConsts::gray.b, ColorsConsts::gray.a },
			TheGame::Instance()->getRenderer());
	}

	/*TheTextureManager::Instance()->drawProgressBar(m_position.getX(), m_position.getY(), m_width, m_height,
		{ 255,0,0,125 }, {}, 0,
		TheGame::Instance()->getRenderer());*/

	SDLGameObject::draw();
}

void Tower::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	// load color specific parameters
	bool canBeColored = pParams->getAttribute<bool>(LoaderParamsConsts::canBeColored);
	std::string namePrefix = "";
	if (canBeColored)
	{
		m_textureID[0] = std::toupper(m_textureID[0]);
		m_textureID = getTowerType(pParams->getAttribute<std::string>(LoaderParamsConsts::color)) + m_textureID;

		namePrefix = getTowerType(pParams->getAttribute<std::string>(LoaderParamsConsts::color));
		namePrefix[0] = std::toupper(namePrefix[0]);
		namePrefix.append(" ");

		m_projectileID = pParams->getAttribute<std::string>(LoaderParamsConsts::projectileID);
		m_projectileID[0] = std::toupper(m_projectileID[0]);
		m_projectileID = std::string(getTowerType(pParams->getAttribute<std::string>(LoaderParamsConsts::color)) + m_projectileID);
	}
	m_name = std::string(namePrefix + pParams->getAttribute<std::string>(LoaderParamsConsts::name));
	m_color = pParams->getAttribute<std::string>(LoaderParamsConsts::color);

	// load other paramters
	m_damage = pParams->getAttribute<float>(LoaderParamsConsts::damage) ? pParams->getAttribute<float>(LoaderParamsConsts::damage) : 0;
	m_radius = pParams->getAttribute<float>(LoaderParamsConsts::radius);
	m_baseCost.type = getResourceTypeByString(pParams->getAttribute<std::string>(LoaderParamsConsts::costType));
	m_baseCost.value = pParams->getAttribute<int>(LoaderParamsConsts::costValue);

	// load attack speed
	float attackSpeed = pParams->getAttribute<float>(LoaderParamsConsts::attackSpeed);
	if (attackSpeed) setAttackSpeed(attackSpeed);

	m_spentResources.type = m_baseCost.type;
}

void Tower::handleEvent()
{
	// select tower on click, when not dragging a tower to build
	if (clickToPlaceTowersHandlerState != ClickToPlaceTowerStates::MOVING)
	{
		m_selectOnClickEventHandler.handleEvent();
	}
	else
	{
		// if dragging tower, deselect this tower
		m_selectOnClickEventHandler.resetParams();
	}
}

std::string Tower::getTowerType(std::string towerColor)
{
	if (towerColor == ResourceTypeConst::green) return TowerTypeConsts::green;
	if (towerColor == ResourceTypeConst::yellow) return TowerTypeConsts::yellow;
	if (towerColor == ResourceTypeConst::red) return TowerTypeConsts::red;

	std::cout << "Tower color: " << towerColor << " not found.\n";

	return "";
}

void Tower::targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies)
{
	if (enemies.empty()) return;

	// if tower has target in range then skip searching a target, otherwise clear it
	if (inRadius(m_targetEnemy.lock())) { return; }
	else { m_targetEnemy.reset(); }

	std::shared_ptr<Enemy> tempEnemy;
	int index = 0;

	// get first enemy in radius if any
	while (tempEnemy.get() == nullptr && index < enemies.size())
	{
		if (inRadius(enemies[index]))
		{
			tempEnemy = enemies[index];
		}
		index++;
	}

	// get farthest enemy on the map in tower radius
	for (std::vector<std::shared_ptr<Enemy>>::size_type i = index; i < enemies.size(); i++)
	{
		if (tempEnemy->getDistance() < enemies[i]->getDistance() && inRadius(enemies[i]))
		{
			tempEnemy = enemies[i];
		}
	}

	// if there is none enemies in radius then return
	if (tempEnemy.get() == nullptr) return;

	// put target enemy to the tower
	if (m_targetEnemy.lock() != tempEnemy)
	{
		m_targetEnemy = tempEnemy;
	}
}

bool Tower::inRadius(std::shared_ptr<Enemy> enemy)
{
	if (enemy.get() == nullptr) return false;

	// get tower's center
	Vector2D centerPos = m_position;
	centerPos.setX(centerPos.getX() + m_width / 2);
	centerPos.setY(centerPos.getY() + m_height / 2);

	// enemy target box
	int hitboxPadding = 3;
	Vector2D topLeft = Vector2D(enemy->getPosition()) + hitboxPadding;
	Vector2D topRight = Vector2D(enemy->getPosition().getX() + enemy->getWidth() - hitboxPadding, enemy->getPosition().getY() + hitboxPadding);
	Vector2D bottomLeft = Vector2D(enemy->getPosition().getX() + hitboxPadding, enemy->getPosition().getY() + enemy->getHeight() - hitboxPadding);
	Vector2D bottomRight = Vector2D(enemy->getPosition().getX() + enemy->getWidth(), enemy->getPosition().getY() + enemy->getHeight()) - hitboxPadding;

	return Vector2D::distance(centerPos, topLeft) <= getRadius() ||
		Vector2D::distance(centerPos, topRight) <= getRadius() ||
		Vector2D::distance(centerPos, bottomLeft) <= getRadius() ||
		Vector2D::distance(centerPos, bottomRight) <= getRadius();
}

bool Tower::isSelected()
{
	return m_selectOnClickEventHandler.isSelected();
}

void Tower::placed()
{
	// set clickEventHandler after placing to get the position
	m_selectOnClickEventHandler = SelectOnClickEventHandler(m_position, m_width, m_height, { 0, 0, 640, 480 }, false); // area of the mapPanel

	// deduct tower's cost resources from gameSession data.
	ThePurchaseManager::Instance()->purchaseTower(m_baseCost);
}

void Tower::aimEnemy()
{
	if (!m_targetEnemy.expired())
	{
		m_attackTimer.countDown(DELAY_TIME / 1000.);

		if (m_attackTimer.timeSIsZero())
		{
			TheProjectileManager::Instance()->createProjectile(*this);
			m_attackTimer.resetToMax();
			//std::cout << "tower projectile created\n";
		}
	}
	else
	{
		m_attackTimer.resetToMax();
	}
}

std::unique_ptr<GameObject> TowerCreator::create() const
{
	return std::make_unique<Tower>();
}
#pragma endregion
