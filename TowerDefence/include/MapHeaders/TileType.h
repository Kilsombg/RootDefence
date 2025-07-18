#ifndef __TileType__
#define __TileType__

#include<string>

namespace TileTypeConsts
{
	constexpr char pathTileID[] = "pathTileID";
	constexpr char towerTileID[] = "towerTileID";
}

/**
* Type for tiles.
*/
enum TileType
{
	NOT_TILE_TYPE = 0,
	OCCUPIED = 1,    // tile with tower object
	TOWER = 2,	// tile that can be placed tower
	PATH = 3	// enemy path
};


/**
* Helper function for getting tileType by string.
* 
* @param strTileType - TileTypeConsts value, otherwise returns NOT_TILE_TYPE.
*/
inline TileType getTileTypeByString(std::string strTileType)
{
	if (strTileType == TileTypeConsts::pathTileID)
	{
		return PATH;
	}
	else if (strTileType == TileTypeConsts::towerTileID)
	{
		return TOWER;
	}
	else
	{
		return NOT_TILE_TYPE;
	}
}

#endif // !__TileType__
