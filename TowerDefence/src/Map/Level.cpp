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
	// render each layer
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
	// update layers
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

int Level::getTileSize()
{
	return m_tileSize;
}

int Level::getWidth()
{
	return m_width;
}

int Level::getHeight()
{
	return m_height;
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

std::vector<SDL_Rect>& Level::getPathArea()
{
	return m_pathAreas;
}
