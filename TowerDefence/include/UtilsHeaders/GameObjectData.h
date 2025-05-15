#ifndef __GameObjectData__
#define __GameObjectData__

#include "NLJsonParser.h"

#include<map>
#include<string>
#include<memory>

/**
* Data object taken from JSON file. Data is parsed into map of T values.

Use parseGameOjbectsData() to parse the data, then use getData() to gather the data.
*/
template<typename T>
struct GameObjectData
{
public:
	/**
	* Get data for a gameObject.
	* 
	* @param gameObjectType is a string value for the specific gameObject to gather.
	*/
	std::shared_ptr<T> getData(std::string gameOjbectType);
	/**
	* Get all data from the map.
	* 
	* @return a map of objects' data.
	*/
	std::map<std::string, std::shared_ptr<T>> getObjectsData();
	/**
	* Parse map from JSON file.
	* 
	* @param filePath is path to the JSON data
	* @param objectKey is the object's key inside JSON file
	*/
	void parseGameOjbectsData(const char* filePath, std::string objectKey);

private:
	// map to store the object's data
	std::map<std::string, std::shared_ptr<T>> m_gameObjectsData;
};


template<typename T>
inline std::shared_ptr<T> GameObjectData<T>::getData(std::string gameOjbectType)
{
	//std::map<std::string, std::shared_ptr<T>>::iterator it = m_gameObjectsData.find(gameOjbectType);
	auto it = m_gameObjectsData.find(gameOjbectType);

	if (it == m_gameObjectsData.end())
	{
		std::cout << "could not find type: " << gameOjbectType << "\n";
		return NULL;
	}
	return it->second;
}

template<typename T>
inline std::map<std::string, std::shared_ptr<T>> GameObjectData<T>::getObjectsData()
{
	return m_gameObjectsData;
}

template<typename T>
inline void GameObjectData<T>::parseGameOjbectsData(const char* filePath, std::string objectKey)
{
	NLJasonParser<std::map<std::string, std::shared_ptr<T>>>::parseFromFile(filePath, m_gameObjectsData, objectKey);
}

#endif // !__GameObjectData__

