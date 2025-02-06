#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include "BaseCreator.h"

#include "../EntitiesHeaders/GameObject.h"

#include<map>
#include<iostream>

class GameObjectFactory
{
public:
	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);

	static GameObjectFactory* Instance();

private:
	GameObjectFactory();
	static GameObjectFactory* s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif // !__GameObjectFactory__
