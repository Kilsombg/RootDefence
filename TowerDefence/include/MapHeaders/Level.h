#ifndef __Level__
#define __Level__

#include "Tileset.h"
#include "Layer.h"

#include "../UtilsHeaders/Vector2D.h"


#include<SDL.h>
#include<vector>
#include<set>
#include<memory>
#include<unordered_map>

/**
* Class representing map's data.
*/
class Level
{
public:
	~Level();
	
	void update();
	void render();
	void clean();

	// getters and setters 

	std::vector<Tileset>* getTilesets();
	std::vector<std::shared_ptr<Layer>>* getLayers();
	// gets indexes for each tiletype on the tilemap
	std::unordered_map<std::string, std::set<int>>& getTileTypeIDs();
	// gets tile size of the tilemap
	int getTileSize();
	/**
	* get map's width
	*/
	int getWidth();
	/**
	* get map's height
	*/
	int getHeight();
	// gets the spawnpoint of the enemies
	Vector2D& getSpawnPoint();
	// sets the spawnpoint of the enemies
	void setSpawnPoint(const Vector2D spawnPoint);
	// gets the path that enemies follow
	std::vector<std::shared_ptr<Vector2D>>& getEnemyPath();
	/**
	* Get path area.
	*/
	std::vector<SDL_Rect>& getPathArea();

private:
	Level();

	std::vector<Tileset> m_tilesets;
	std::vector<std::shared_ptr<Layer>> m_layers;
	// contains indexes for each tiletype on the tilemap
	std::unordered_map<std::string, std::set<int>> m_tileTypeIDs;
	int m_tileSize;
	// map's width
	int m_width;
	// map's height
	int m_height;
	// spawnpoint of the enemies
	Vector2D m_spawnPoint;
	// path that enemies follow
	std::vector<std::shared_ptr<Vector2D>> m_enemyPath;
	// vector of rectangles defining enemy's path
	std::vector<SDL_Rect> m_pathAreas;

	friend class LevelParser;
};

#endif // !__Level__