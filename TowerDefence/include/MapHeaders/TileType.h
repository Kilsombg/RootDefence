#ifndef __TileType__
#define __TileType__

#include<string>

namespace TileTypeConsts
{
	constexpr char pathTileID[] = "pathTileID";
	constexpr char towerTileID[] = "towerTileID";
}

enum TileType
{
	NONE = 0,
	OCCUPIED = 1,    // tile with tower object
	TOWER = 2,	// tile that can be placed tower
	PATH = 3	// enemy path
};

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
		return NONE;
	}
}

#endif // !__TileType__
