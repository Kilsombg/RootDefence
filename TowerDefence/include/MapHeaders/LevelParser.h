#ifndef __LevelParser__
#define __LevelParser__

#include "Level.h"

#include "../UtilsHeaders/tinyxml.h"
#include "../UtilsHeaders/Vector2D.h"

#include<string>
#include<vector>
#include<memory>

class LevelParser
{
public:
	std::shared_ptr<Level> parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot);
	void parseTileSetProperties(TiXmlElement* pPropertiesRoot, int firstGridID);
	void parseTileLayer(TiXmlElement* pTileElement);
	void parseObjectLayer(TiXmlElement* pObjectElement);

	void setMapTileTypes(std::vector<std::vector<int>> data);

	/**
	*  Parse a string of tileID values into set of integers.
	* 
	* @param strTileIDs contains a string of tileID values, seperated by comma delimiter.
	* @return a set of these integers.
	*/
	void parseTileIDs(std::string tileTypeName, std::string strTileIDs, int firstGridID);

	/**
	* Parse object layer that contains polylines intented for objects' paths.
	*/
	void parsePathsLayer(TiXmlElement* pPathElement);
	/**
	* Parse enemy's path points to follow.
	*/
	void parseEnemyPath(TiXmlElement* pPathElement);
	/**
	* Parse enemy's path area, used for placing towers.
	*/
	void parseEnemyPathArea(TiXmlElement* pPathElement);
	
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
	std::shared_ptr<Level> m_pLevel;
};

#endif // !__LevelParser__
