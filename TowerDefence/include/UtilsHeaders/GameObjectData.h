#ifndef __GameObjectData__
#define __GameObjectData__

#include "LoaderParams.h"
#include "NLJsonParser.h"

#include "../Constants/GameObjectConsts.h"

#include<map>
#include<string>
#include<memory>

struct GameObjectData
{
public:
	std::shared_ptr<LoaderParams> getData(std::string gameOjbectType);
	void parseGameOjbectsData(const char* filePath);

private:
	std::map<std::string, std::shared_ptr<LoaderParams>> m_gameObjectsData;
};

#endif // !__GameObjectData__
