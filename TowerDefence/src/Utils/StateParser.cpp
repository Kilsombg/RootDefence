#include "../../include/UtilsHeaders/StateParser.h"
#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"

#include "../../include/Game.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<std::unique_ptr<GameObject>>* pObjects, std::vector<std::string>* pTextureIDs)
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(stateFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pStateRoot = 0;

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}

	TiXmlElement* pTextureRoot = 0;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	parseTextures(pTextureRoot, pTextureIDs);

	TiXmlElement* pObjectRoot = 0;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	parseObjects(pObjectRoot, pObjects);
	return true;
}


void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");

		pTextureIDs->push_back(idAttribute);

		TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

		for (TiXmlAttribute* attribute = e->FirstAttribute(); attribute != NULL; attribute = attribute->Next())
		{
			std::string name = attribute->Name();
			const char* value = attribute->Value();

			if (std::isdigit(value[0]) || (value[0] == '-' && std::isdigit(value[1]))) {
				if (std::string(value).find('.') != std::string::npos) {
					pParams->setAttribute(name, std::stof(value));
				}
				else {
					pParams->setAttribute(name, std::stoi(value));
				}
			}
			else {
				pParams->setAttribute(name, std::string(value));
			}
		}

		std::unique_ptr<GameObject> pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(pParams);

		pObjects->push_back(std::move(pGameObject));
	}
}