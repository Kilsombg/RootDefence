#ifndef __TileType__
#define __TileType__

enum TileType
{
	NONE = 0,
	OCCUPIED = 1,    // tile with tower object
	TOWER = 2,	// tile that can be placed tower
	PATH = 3	// enemy path
};

#endif // !__TileType__
