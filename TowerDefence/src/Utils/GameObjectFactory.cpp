#include "../../include/UtilsHeaders/GameObjectFactory.h"

std::shared_ptr<GameObjectFactory> GameObjectFactory::s_pInstance = nullptr;

GameObjectFactory::GameObjectFactory()
{
}

std::shared_ptr<GameObjectFactory> GameObjectFactory::Instance()
{
	if (s_pInstance == nullptr) 
	{
		s_pInstance = std::shared_ptr<GameObjectFactory>(new GameObjectFactory);
		return s_pInstance;
	}

	return s_pInstance;
}

bool GameObjectFactory::registerType(std::string typeID, std::shared_ptr<BaseCreator> pCreator)
{
	std::map<std::string, std::shared_ptr<BaseCreator>>::iterator it = m_creators.find(typeID);
	
	// if the type is already registered, do nothing
	if (it != m_creators.end())
	{
		return false;
	}
	
	m_creators[typeID] = pCreator;
	return true;
}

std::unique_ptr<GameObject> GameObjectFactory::create(std::string typeID)
{
	std::map<std::string, std::shared_ptr<BaseCreator>>::iterator it = m_creators.find(typeID);
	
	//If the type is not already registered
	if (it == m_creators.end())
	{
		std::cout << "could not find type: " << typeID << "\n";
		return NULL;
	}

	std::shared_ptr<BaseCreator> pCreator = it->second;
	return pCreator->createGameObject();
}


