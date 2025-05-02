#include "../../include/EntitiesHeaders/Projectile.h"

Projectile::Projectile() : SDLGameObject(), m_damage(0), m_speed(0), m_hitEnemy(false)
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

void Projectile::setDamage(float damage)
{
	m_damage = damage;
}

float Projectile::getDamage()
{
	return m_damage;
}

void Projectile::setSpeed(float speed)
{
	m_speed = speed;
}

void Projectile::setTargetEnemy(std::weak_ptr<Enemy> targetEnemy)
{
	m_targetEnemy = targetEnemy;
}

std::weak_ptr<Enemy> Projectile::getTargetEnemy()
{
	return m_targetEnemy;
}

bool Projectile::hitEnemy()
{
	return m_hitEnemy;
}

void Projectile::move()
{
	if (m_targetEnemy.use_count())
	{
		std::shared_ptr<Enemy> targetEnemy = m_targetEnemy.lock();
		m_targetCenterX = targetEnemy->getPosition().getX() + targetEnemy->getWidth() / 2;
		m_targetCenterY = targetEnemy->getPosition().getY() + targetEnemy->getHeight() / 2;
	}
	
	Vector2D targetPoint = Vector2D(m_targetCenterX, m_targetCenterY);

	m_velocity = targetPoint - m_position;

	if (m_velocity.length() < m_speed)
	{
		m_hitEnemy = true;
		return;
	}

	m_velocity.normalize();
	m_velocity *= m_speed;
}


std::unique_ptr<GameObject> ProjectileCreator::createGameObject() const
{
	return std::make_unique<Projectile>();
}