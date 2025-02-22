#ifndef __Level__
#define __Level__

#include "Tileset.h"
#include "Layer.h"

#include "../UtilsHeaders/Vector2D.h"

#include<vector>
#include<memory>

class Level
{
public:
	~Level();
	
	void update();
	void render();

	std::vector<Tileset>* getTilesets();
	std::vector<std::shared_ptr<Layer>>* getLayers();
	Vector2D& getSpawnPoint();
	std::vector<std::shared_ptr<Vector2D>>& getEnemyPath();

	void setSpawnPoint(const Vector2D spawnPoint);

private:
	Level();

	std::vector<Tileset> m_tilesets;
	std::vector<std::shared_ptr<Layer>> m_layers;
	Vector2D m_spawnPoint;
	std::vector<std::shared_ptr<Vector2D>> m_enemyPath;

	friend class LevelParser;
};

#endif // !__Level__

