#ifndef __StateParser__
#define __StateParser__

#include "tinyxml.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/CommonHeaders/Panel.h"

#include <iostream>
#include <vector>
#include<memory>

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<std::string>* pTextureIDs, std::vector<std::unique_ptr<Panel>>* pPanels);

private:
	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
	void parsePanels(TiXmlElement* pPanelsRoot, std::vector<std::unique_ptr<Panel>>* pPanels);
	void parsePanelBackground(TiXmlElement* panelElement, std::unique_ptr<Panel>& panel);
	void parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>* pObjects);
};

#endif // !__StateParser__
