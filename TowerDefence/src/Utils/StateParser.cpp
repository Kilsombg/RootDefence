#include "../../include/UtilsHeaders/StateParser.h"
#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/PanelFactory.h"

#include "../../include/Constants/LoaderParamsConsts.h"

#include "../../include/Game.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<std::string>* pTextureIDs, std::vector<std::unique_ptr<Panel>>* pPanels)
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


	TiXmlElement* pPanelRoot = 0;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("PANELS"))
		{
			pPanelRoot = e;
		}
	}
	parsePanels(pPanelRoot, pPanels);
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

void StateParser::parsePanels(TiXmlElement* pPanelsRoot, std::vector<std::unique_ptr<Panel>>* pPanels)
{
	for (TiXmlElement* panelElement = pPanelsRoot->FirstChildElement(); panelElement != NULL; panelElement = panelElement->NextSiblingElement())
	{
		// get panel's objects root
		TiXmlElement* pObjectRoot = 0;
		for (TiXmlElement* e = panelElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("OBJECTS"))
			{
				pObjectRoot = e;
			}
		}

		// parse panel's objects		
		std::vector<std::unique_ptr<GameObject>> objects;
		parseObjects(pObjectRoot, &objects);

		// create and load panel
		std::unique_ptr<Panel> panel = ThePanelFactory::Instance()->create(panelElement->Attribute("type"));
		parsePanelBackground(panelElement, panel);
		panel->load(std::move(objects));
		pPanels->push_back(std::move(panel));
	}
}

void StateParser::parsePanelBackground(TiXmlElement* panelElement, std::unique_ptr<Panel>& panel)
{
	// create texture
	std::unique_ptr<Texture> backgroundTexture = std::make_unique<Texture>();
	std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

	// load params from xml
	double x, y;
	int width, height;
	std::string textureID;
	panelElement->Attribute(LoaderParamsConsts::x, &x);
	panelElement->Attribute(LoaderParamsConsts::y, &y);
	panelElement->Attribute(LoaderParamsConsts::width, &width);
	panelElement->Attribute(LoaderParamsConsts::height, &height);
	textureID = panelElement->Attribute(LoaderParamsConsts::textureID);

	// set attributes
	pParams->setAttribute(LoaderParamsConsts::x, static_cast<float>(x));
	pParams->setAttribute(LoaderParamsConsts::y, static_cast<float>(y));
	pParams->setAttribute(LoaderParamsConsts::width, width);
	pParams->setAttribute(LoaderParamsConsts::height, height);
	pParams->setAttribute(LoaderParamsConsts::textureID, textureID);

	backgroundTexture->load(pParams);
	panel->setBackgroundTexture(std::move(backgroundTexture));
}


void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<GameObject>>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

		for (TiXmlAttribute* attribute = e->FirstAttribute(); attribute != NULL; attribute = attribute->Next())
		{
			std::string name = attribute->Name();
			std::string value = attribute->Value();

			if (std::isdigit(value[0]) || (value[0] == '-' && std::isdigit(value[1]))) {
				if (value.find('.') != std::string::npos) {
					pParams->setAttribute(name, std::stof(value));
				}
				else {
					pParams->setAttribute(name, std::stoi(value));
				}
			}
			else if (value == "true" || value == "false")
			{
				bool boolValue = value == "true";
				pParams->setAttribute(name, boolValue);
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