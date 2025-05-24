#include "../../include/EntitiesHeaders/Projectile.h"

#include "../../include/Constants/LoaderParamsConsts.h"

Projectile::Projectile() : SDLGameObject(), m_damage(0), m_speed(0), m_hitEnemy(false), m_targetCenterX(0), m_targetCenterY(0)
{
}

Projectile::Projectile(const Projectile& proj) : SDLGameObject(proj)
{
	m_damage = proj.m_damage;
	m_speed = proj.m_speed;
	m_targetEnemy = proj.m_targetEnemy;
	m_hitEnemy = proj.m_hitEnemy;
}

void Projectile::update()
{
	move();

	SDLGameObject::update();
}

void Projectile::draw()
{
	SDLGameObject::draw();
}

void Projectile::load(const std::shared_ptr<LoaderParams> pParams)
{
	SDLGameObject::load(pParams);

	m_damage = pParams->getAttribute<float>(LoaderParamsConsts::damage);
	m_speed = pParams->getAttribute<float>(LoaderParamsConsts::projectileSpeed);
	m_towerType = getResourceTypeByString(pParams->getAttribute<std::string>(LoaderParamsConsts::towerColor));
}

float Projectile::getDamage()
{
	return m_damage;
}

void Projectile::setTargetEnemy(std::weak_ptr<Enemy> targetEnemy)
{
	m_targetEnemy = targetEnemy;
}

std::weak_ptr<Enemy> Projectile::getTargetEnemy()
{
	return m_targetEnemy;
}

ResourceType Projectile::getTowersType()
{
	return m_towerType;
}

bool Projectile::hitEnemy()
{
	return m_hitEnemy;
}

void Projectile::move()
{
	// get target's position
	if (m_targetEnemy.use_count())
	{
		std::shared_ptr<Enemy> targetEnemy = m_targetEnemy.lock();
		m_targetCenterX = targetEnemy->getPosition().getX() + targetEnemy->getWidth() / 2;
		m_targetCenterY = targetEnemy->getPosition().getY() + targetEnemy->getHeight() / 2;
	}
	
	// point projectile to target
	Vector2D targetPoint = Vector2D(m_targetCenterX, m_targetCenterY);
	m_velocity = targetPoint - m_position;

	// if projectile get close to target hit enemy and return
	if (m_velocity.length() < m_speed)
	{
		m_hitEnemy = true;
		return;
	}

	// if target is far away get the direction to target and change the magnitude to projectile speed
	m_velocity.normalize();
	m_velocity *= m_speed;
}


std::unique_ptr<GameObject> ProjectileCreator::create() const
{
	return std::make_unique<Projectile>();
}