#include "../../include/UtilsHeaders/GameObjectData.h"

#include<iostream>

std::shared_ptr<LoaderParams> GameObjectData::getData(std::string gameOjbectType)
{
	std::map<std::string, std::shared_ptr<LoaderParams>>::iterator it  = m_gameObjectsData.find(gameOjbectType);
	
	if (it == m_gameObjectsData.end())
	{
		std::cout << "could not find type: " << gameOjbectType << "\n";
		return NULL;
	}
	return it->second;
}

void GameObjectData::parseGameOjbectsData(const char* filePath)
{
	NLJasonParser<std::map<std::string, std::shared_ptr<LoaderParams>>>::parseFromFile(filePath, m_gameObjectsData, GameObjectConsts::gameObjectData);
}
