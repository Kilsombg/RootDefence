#include "../../include/MapHeaders/LevelParser.h"
#include "../../include/MapHeaders/TileSet.h"
#include "../../include/MapHeaders/TileLayer.h"
#include "../../include/MapHeaders/ObjectLayer.h"
#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/base64.h"

#include "../../include/Game.h"

#include<SDL.h>
#include<zlib.h>
#include<iostream>
#include <sstream>

std::shared_ptr<Level> LevelParser::parseLevel(const char* levelFile)
{
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);


	m_pLevel = std::shared_ptr<Level>(new Level);
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);
	m_pLevel->m_width = m_width * m_tileSize;
	m_pLevel->m_height = m_height * m_tileSize;

	m_pLevel->m_tileSize = m_tileSize;

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e);
		}
	}

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e);
		}
	}

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			if (e->Attribute("name") == std::string("EntitiesPaths"))
			{
				parsePathsLayer(e);
			}
			else if (e->Attribute("name") == std::string("ObjectLayer"))
			{
				parseObjectLayer(e);
			}
		}
	}

	return m_pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot)
{
	Tileset tileset;
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");

	for (TiXmlElement* e = pTilesetRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			parseTileSetProperties(e, tileset.firstGridID);
		}
		else if (e->Value() == std::string("image"))
		{
			std::string sourcePath = std::string("src/assets/Map/") + e->Attribute("source");
			std::cout << "Tile source path:" << sourcePath << "\n";
			TheTextureManager::Instance()->load(sourcePath, pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

			e->Attribute("width", &tileset.width);
			e->Attribute("height", &tileset.height);
		}
	}
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	m_pLevel->getTilesets()->push_back(tileset);
}

void LevelParser::parseTileSetProperties(TiXmlElement* pPropertiesRoot, int firstGridID)
{
	for (TiXmlElement* property = pPropertiesRoot->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
	{
		if (std::string(property->Attribute("name")).find("TileID") != std::string::npos)
		{
			parseTileIDs(property->Attribute("name"), property->Attribute("value"), firstGridID);
		}
	}
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement)
{
	std::shared_ptr<TileLayer> pTileLayer = std::make_shared<TileLayer>(m_width, m_height ,m_tileSize, *m_pLevel->getTilesets());

	std::vector<std::vector<int>> data;
	std::string decodedIDs;
	TiXmlElement* pDataNode = nullptr;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// uncompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	setMapTileTypes(data);
	pTileLayer->setTileIDs(data);

	m_pLevel->getLayers()->push_back(pTileLayer);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement)
{
	// create an object layer
	std::shared_ptr<ObjectLayer> pObjectLayer = std::make_shared<ObjectLayer>();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			double x, y;

			std::shared_ptr<GameObject> pGameObject = std::move(TheGameObjectFactory::Instance()->create(e->Attribute("type")));
			std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();

			e->Attribute("x", &x);
			e->Attribute("y", &y);

			pParams->setAttribute<float>("x", static_cast<float>(x));
			pParams->setAttribute<float>("y", static_cast<float>(y));

			// get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							std::string name = property->Attribute("name");
							const char* value = property->Attribute("value");

							if (name.empty() || value == nullptr) {
								continue;
							}

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
					}
				}
			}
			pGameObject->load(pParams);
			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	m_pLevel->getLayers()->push_back(pObjectLayer);
}

void LevelParser::setMapTileTypes(std::vector<std::vector<int>> data)
{
	if (data.empty())
	{
		return;
	}

	if (data[0].empty())
	{
		return;
	}

	std::vector<std::vector<TileType>>* pTileTypeMap = &(m_pLevel->getTileTypeMap());

	std::vector<TileType> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		pTileTypeMap->push_back(layerRow);
	}

	for (std::vector<std::vector<int>>::size_type i = 0; i < data.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j < data[i].size(); j++)
		{
			for (auto& it : m_pLevel->getTileTypeIDs())
			{
				const std::string& tileType = it.first;
				const std::set<int>& tileIDs = it.second;
				if (tileIDs.find(data[i][j]) != tileIDs.end())
				{
					(*pTileTypeMap)[i][j] = getTileTypeByString(tileType);
				}
			}
		}
	}
}

void LevelParser::parseTileIDs(std::string tileTypeName, std::string strTileIDs, int firstGridID)
{
	std::stringstream ss(strTileIDs);
	std::string strTileID;

	while (std::getline(ss, strTileID, ',')) {
		m_pLevel->getTileTypeIDs()[tileTypeName].insert(std::stoi(strTileID) + firstGridID);
	}
}

void LevelParser::parsePathsLayer(TiXmlElement* pPathElement)
{
	for (TiXmlElement* e = pPathElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// parse enemy's path points to follow
		if (e->Attribute("name") == std::string("enemyPath"))
		{
			parseEnemyPath(e);
		}
		else if (e->Attribute("name") == std::string("enemyPathArea"))
		{
			// parse path area
			parseEnemyPathArea(e);
		}
		
	}
}

void LevelParser::parseEnemyPath(TiXmlElement* pPathElement)
{
	double x, y;
	std::string points;

	pPathElement->Attribute("x", &x);
	pPathElement->Attribute("y", &y);

	for (TiXmlElement* polyline = pPathElement->FirstChildElement(); polyline != NULL; polyline = polyline->NextSiblingElement())
	{
		if (polyline->Value() == std::string("polyline"))
		{
			points = polyline->Attribute("points");
		}
	}

	m_pLevel->getEnemyPath() = std::move(parsePolylinePoints(points, static_cast<float>(x), static_cast<float>(y)));
}

void LevelParser::parseEnemyPathArea(TiXmlElement* pPathElement)
{
	SDL_Rect rect;

	pPathElement->Attribute("x", &rect.x);
	pPathElement->Attribute("y", &rect.y);
	pPathElement->Attribute("width", &rect.w);
	pPathElement->Attribute("height", &rect.h);

	m_pLevel->m_pathAreas.push_back(rect);
}

std::vector<std::shared_ptr<Vector2D>> LevelParser::parsePolylinePoints(std::string & strPoints, float objectX, float objectY)
{
	std::vector<std::shared_ptr<Vector2D>> points = std::vector<std::shared_ptr<Vector2D>>();
	std::stringstream ss(strPoints);
	std::string pair;

	while (std::getline(ss, pair, ' ')) {
		std::stringstream pairStream(pair);
		std::string strX, strY;

		if (std::getline(pairStream, strX, ',') && std::getline(pairStream, strY, ',')) {
			float pointX = objectX + std::stof(strX);
			float pointY = objectY + std::stof(strY);
			std::shared_ptr<Vector2D> point = std::make_shared<Vector2D>(pointX, pointY);
			points.push_back(point);
		}
	}
	
	return points;
}