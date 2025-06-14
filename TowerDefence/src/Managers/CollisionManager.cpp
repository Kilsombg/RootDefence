#include "../../include/ManagersHeaders/CollisionManager.h"

std::shared_ptr<CollisionManager> CollisionManager::s_pInstance = nullptr;

std::shared_ptr<CollisionManager> CollisionManager::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<CollisionManager>(new CollisionManager);
		return s_pInstance;
	}
	return s_pInstance;
}

void CollisionManager::clean()
{
	s_pInstance = nullptr;
}

void CollisionManager::setTowersObjects(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towersObjects)
{
	m_towersObjects = towersObjects;
}

bool CollisionManager::collideTowerPlacement(SDLGameObject* gameObject, std::shared_ptr<Level> pLevel)
{
	// get game objects sides
	int rightGameObject, bottomGameObject;
	rightGameObject = gameObject->getPosition().getX() + gameObject->getWidth();
	bottomGameObject = gameObject->getPosition().getY() + gameObject->getHeight();

	return checkCollisionWithPathArea(gameObject, pLevel->getPathArea()) || collideWithTowers(gameObject) || 
		(rightGameObject > pLevel->getWidth()) || (bottomGameObject > pLevel->getHeight());
}

bool CollisionManager::checkCollisionWithPathArea(SDLGameObject* gameObject, std::vector<SDL_Rect>& pathArea)
{
	// check collision with each pathArea
	for (std::vector<SDL_Rect>::size_type i = 0; i < pathArea.size(); i++)
	{
		if (checkCollisionWithRectangleArea(gameObject, pathArea[i]))
		{
			return true;
		}
	}
	return false;
}

CollisionManager::CollisionManager()
{
}

bool CollisionManager::collideWithTowers(SDLGameObject* gameObject)
{
	// check collision with each tower on screen
	for (std::vector<std::shared_ptr<Tower>>::size_type i = 0; i < m_towersObjects->size(); i++)
	{
		if (checkCollision(gameObject, (*m_towersObjects)[i].get()))
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkCollision(SDLGameObject* gameObject1, SDLGameObject* gameObject2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = gameObject1->getPosition().getX();
	rightA = gameObject1->getPosition().getX() + gameObject1->getWidth();
	topA = gameObject1->getPosition().getY();
	bottomA = gameObject1->getPosition().getY() + gameObject1->getHeight();

	//Calculate the sides of rect B
	leftB = gameObject2->getPosition().getX();
	rightB = gameObject2->getPosition().getX() + gameObject2->getWidth();
	topB = gameObject2->getPosition().getY();
	bottomB = gameObject2->getPosition().getY() + gameObject2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}


bool CollisionManager::checkCollisionWithRectangleArea(SDLGameObject* gameObject1, SDL_Rect& rectArea)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = gameObject1->getPosition().getX();
	rightA = gameObject1->getPosition().getX() + gameObject1->getWidth();
	topA = gameObject1->getPosition().getY();
	bottomA = gameObject1->getPosition().getY() + gameObject1->getHeight();

	//Calculate the sides of rect B
	leftB = rectArea.x;
	rightB = rectArea.x + rectArea.w;
	topB = rectArea.y;
	bottomB = rectArea.y + rectArea.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;;
}