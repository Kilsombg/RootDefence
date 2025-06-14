#ifndef __TileLayer__
#define __TileLayer__

#include "Layer.h"
#include "Tileset.h"

#include "../UtilsHeaders/Vector2D.h"

#include<vector>

/**
* Tile layer containing ids for tiles in the map.
*/
class TileLayer : public Layer
{
public:
	TileLayer(int numColumns, int numRows, int tileSize, const std::vector<Tileset>& tilesets);

	virtual void update();
	/**
	* Renders tileLayer on screen.
	*/
	virtual void render();

	// getters and setters 

	void setTileIDs(const std::vector<std::vector<int>>& data);

	void setTileSize(int tileSize);

	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset>& m_tilesets; // tilesets' data
	std::vector<std::vector<int>> m_tileIDs; // map of tiles' ids
};

#endif // !__TileLayer__
