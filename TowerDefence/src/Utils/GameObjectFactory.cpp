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