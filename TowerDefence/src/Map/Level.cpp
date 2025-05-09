#include "../../include/MapHeaders/Level.h"

#include "../../include/UtilsHeaders/TextureManager.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::clean()
{
	// clean textures
	for (std::vector<Tileset>::size_type i = 0; i < m_tilesets.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_tilesets[i].name);
	}

	// clean layers
	m_layers.clear();

	// clean path;
	m_enemyPath.clear();
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}

std::vector<Tileset>* Level::getTilesets()
{
	return &m_tilesets;
}

std::vector<std::shared_ptr<Layer>>* Level::getLayers()
{
	return &m_layers;
}

std::unordered_map<std::string, std::set<int>>& Level::getTileTypeIDs()
{
	return m_tileTypeIDs;
}

TileType Level::getTileTypeByPosition(float x, float y) const
{
	int r, c;
	r = y / m_tileSize;
	c = x / m_tileSize;

	if (r >= m_tileTypeMap.size() || c >= m_tileTypeMap[0].size())
	{
		return TileType::NOT_TILE_TYPE;
	}

	return m_tileTypeMap[r][c];
}

std::vector<std::vector<TileType>>& Level::getTileTypeMap()
{
	return m_tileTypeMap;
}

int Level::getTileSize()
{
	return m_tileSize;
}

Vector2D& Level::getSpawnPoint()
{
	return m_spawnPoint;
}

std::vector<std::shared_ptr<Vector2D>>& Level::getEnemyPath()
{
	return m_enemyPath;
}

void Level::setSpawnPoint(const Vector2D spawnPoint)
{
	m_spawnPoint = spawnPoint;
}
