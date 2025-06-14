#ifndef __CollisionManager__
#define __CollisionManager__

#include "../EntitiesHeaders/SDLGameObject.h"
#include "../EntitiesHeaders/Tower.h"

#include "../MapHeaders/Level.h"

#include<SDL.h>
#include<memory>
#include<vector>

/**
* Class to maange collistion between objects.
* 
* Must be set playState towers objects to use collideTowerPlacement().
* Use checkCollision() to check two objects for collision.
* 
* Call clean(), when finished with manager.
*/
class CollisionManager
{
public:
	static std::shared_ptr<CollisionManager> Instance();
	void clean();

	// setters and getters

	void setTowersObjects(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towersObjects);
		
	/**
	* Check if a tower collides with other towers or path area.
	* 
	* @param gameObject - object, that will be checked for collision.
	* @param pLevel - pointer to level.
	* 
	* @return false if tower can be placed.
	*/
	bool collideTowerPlacement(SDLGameObject* gameObject, std::shared_ptr<Level> pLevel);
	/**
	* Check if two objects collide.
	*/
	bool checkCollision(SDLGameObject* gameObject1, SDLGameObject* gameObject2);
	

private:
	CollisionManager();

	/**
	* Check if object collides with any tower on screen.
	*/
	bool collideWithTowers(SDLGameObject* gameObject);
	/**
	* Check if object collides with path area on screen.
	*/
	bool checkCollisionWithPathArea(SDLGameObject* gameObject, std::vector<SDL_Rect>& pathArea);
	/**
	* Check if an object collides with rectangle area.
	*/
	bool checkCollisionWithRectangleArea(SDLGameObject* gameObject1,  SDL_Rect& rectArea);

	static std::shared_ptr<CollisionManager> s_pInstance;
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> m_towersObjects; /// playState towers objects pointer
};

typedef CollisionManager TheCollisionManager;

#endif // !__CollisionManager__
