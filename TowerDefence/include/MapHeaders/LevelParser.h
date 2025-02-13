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

	/**
	* Parse object layer that cointains polylines intented for objects' paths.
	*/
	void parsePathsLayer(TiXmlElement* pPathElement, std::vector<std::shared_ptr<Vector2D>>& pEnemyPath);
	
	/**	
	*  Parse a string of points values into vector of points.
	* 
	* @param strPoints contains a string of points values, seperated by space delimiter. Point values x and y are
	* separated by ',' delimiter.
	* @param objectX, objectY are coordinates of the polyline object in the tilemap.
	* @return vector of Vector2D points containing the values
	*/
	std::vector<std::shared_ptr<Vector2D>> parsePolylinePoints(std::string& strPoints, float objectX, float objectY);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif // !__LevelParser__
