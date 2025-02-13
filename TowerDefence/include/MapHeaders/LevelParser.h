#ifndef __LevelParser__
#define __LevelParser__

#include "Level.h"

#include "../UtilsHeaders/tinyxml.h"
#include "../UtilsHeaders/Vector2D.h"

#include<vector>
#include<memory>

class LevelParser
{
public:
	std::shared_ptr<Level> parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<std::shared_ptr<Layer>>* pLayers, const std::vector<Tileset>* pTilesets);
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<std::shared_ptr<Layer>>* pLayers);
	void parsePathsLayer(TiXmlElement* pPathElement, std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>>& pEnemyPath);
	
	std::shared_ptr<std::vector<std::shared_ptr<Vector2D>>> parsePolylinePoints(std::string& strPoints, float objectX, float objectY);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif // !__LevelParser__
