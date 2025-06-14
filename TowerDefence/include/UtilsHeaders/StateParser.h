#ifndef __StateParser__
#define __StateParser__

#include "tinyxml.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/CommonHeaders/Panel.h"

#include <vector>
#include<memory>

/**
* Parse a state from XML file.
* 
* calls parseState() with stateID to be parsed.
*/
class StateParser
{
public:
	/**
	* Parse a state from XML file.
	* 
	* @param stateFile - file path to state XML file
	* @param stateID - id of state to be extracted
	* @param pTextureIDs - pointer to textureIDs of the state
	* @param pPanels - pointer to panels vector of state
	* 
	* @return true if all succeeded.
	*/
	bool parseState(const char* stateFile, std::string stateID, std::vector<std::string>* pTextureIDs, std::vector<std::unique_ptr<Panel>>* pPanels);

private:
	/**
	* Parse textures for the state.
	*/
	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
	/**
	* Parse state's panels.
	*/
	void parsePanels(TiXmlElement* pPanelsRoot, std::vector<std::unique_ptr<Panel>>* pPanels);
	/**
	* Parse panel's backgroudn.
	*/
	void parsePanelBackground(TiXmlElement* panelElement, std::unique_ptr<Panel>& panel);
	/**
	* Parse panel's objects.
	*/
	void parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>* pObjects);
};

#endif // !__StateParser__
