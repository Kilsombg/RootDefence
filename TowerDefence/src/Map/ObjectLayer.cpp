#include "../../include/MapHeaders/ObjectLayer.h"

void ObjectLayer::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

std::vector<std::shared_ptr<GameObject>>* ObjectLayer::getGameObjects()
{
	return &m_gameObjects;
}
