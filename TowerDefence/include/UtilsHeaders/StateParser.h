#ifndef __StateParser__
#define __StateParser__

#include "../EntitiesHeaders/GameObject.h"

#include "tinyxml.h"

#include <iostream>
#include <vector>
#include<memory>

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<std::unique_ptr<GameObject>>* pObjects, std::vector<std::string>* pTextureIDs);

private:
	void parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>* pObjects);

	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};

#endif // !__StateParser__
