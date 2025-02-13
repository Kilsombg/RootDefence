#include "../../include/MapHeaders/LevelParser.h"
#include "../../include/MapHeaders/TileSet.h"
#include "../../include/MapHeaders/TileLayer.h"
#include "../../include/MapHeaders/ObjectLayer.h"

#include "../../include/UtilsHeaders/TextureManager.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/base64.h"

#include "../../include/Game.h"

#include<zlib.h>
#include<iostream>
#include <sstream>

std::shared_ptr<Level> LevelParser::parseLevel(const char* levelFile)
{
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);


	std::shared_ptr<Level> pLevel = std::shared_ptr<Level>(new Level);
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}

	/*
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			parseTextures(e);
		}
	}*/


	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			if (e->Attribute("name") == std::string("EntitiesPaths"))
			{
				parsePathsLayer(e, pLevel->getEnemyPath());
			}
			else if (e->Attribute("name") == std::string("ObjectLayer"))
			{
				parseObjectLayer(e, pLevel->getLayers());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	std::string sourcePath = std::string("src/assets/Map/") + pTilesetRoot->FirstChildElement()->Attribute("source");
	std::cout << "Tile source path:" << sourcePath << "\n";
	TheTextureManager::Instance()->load(sourcePath, pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<std::shared_ptr<Layer>>* pLayers, const std::vector<Tileset>* pTilesets)
{
	std::shared_ptr<TileLayer> pTileLayer = std::make_shared<TileLayer>(m_tileSize, *pTilesets);

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
	pTileLayer->setTileIDs(data);


	pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	for (TiXmlElement* e = pTextureRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == static_cast<std::string>("property"))
		{
			std::string filePath = static_cast<std::string>("./src/assets/") + e->Attribute("value");
			if (!TheTextureManager::Instance()->load(filePath, e->Attribute("name"), TheGame::Instance()->getRenderer()))
			{
				std::cout << "failed to load textures";
			}
		}
	}
}


void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<std::shared_ptr<Layer>>* pLayers)
{
	// create an object layer
	std::shared_ptr<ObjectLayer> pObjectLayer = std::make_shared<ObjectLayer>();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames, callbackID, animSpeed;
			std::string textureID;

			// get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			std::shared_ptr<GameObject> pGameObject = std::move(TheGameObjectFactory::Instance()->create(e->Attribute("type")));

			// get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (e->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}
			pGameObject->load(std::make_shared<LoaderParams>(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	pLayers->push_back(pObjectLayer);
}

void LevelParser::parsePathsLayer(TiXmlElement* pPathElement, std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>>& pEnemyPath)
{
	double x, y;
	std::string points;

	for (TiXmlElement* e = pPathElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			e->Attribute("x", &x);
			e->Attribute("y", &y);

			for (TiXmlElement* polyline = e->FirstChildElement(); polyline != NULL; polyline = polyline->NextSiblingElement())
			{
				if (polyline->Value() == std::string("polyline"))
				{
					points = polyline->Attribute("points");
				}
			}
		}
	}

	pEnemyPath = std::move(parsePolylinePoints(points, static_cast<float>(x), static_cast<float>(y)));
}

std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> LevelParser::parsePolylinePoints(std::string & strPoints, float objectX, float objectY)
{
	std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> points = std::make_shared<std::vector<std::shared_ptr<Vector2D>>>();
	std::stringstream ss(strPoints);
	std::string pair;

	while (std::getline(ss, pair, ' ')) {
		std::stringstream pairStream(pair);
		std::string strX, strY;

		if (std::getline(pairStream, strX, ',') && std::getline(pairStream, strY, ',')) {
			std::shared_ptr<Vector2D> point = std::make_shared<Vector2D>(std::stof(strX), std::stof(strY));
			points->push_back(point);
		}
	}
	
	return points;
}