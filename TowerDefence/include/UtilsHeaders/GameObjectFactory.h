#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include "BaseCreator.h"

#include "../EntitiesHeaders/GameObject.h"

#include<map>
#include<memory>
#include<iostream>

class GameObjectFactory
{
public:
	bool registerType(std::string typeID, std::shared_ptr<BaseCreator> pCreator);
	std::unique_ptr<GameObject> create(std::string typeID);

	static std::shared_ptr<GameObjectFactory> Instance();

private:
	GameObjectFactory();
	static std::shared_ptr<GameObjectFactory> s_pInstance;

	std::map<std::string, std::shared_ptr<BaseCreator>> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif // !__GameObjectFactory__
