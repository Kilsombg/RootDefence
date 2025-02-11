#ifndef __Level__
#define __Level__

#include "Tileset.h"
#include "Layer.h"


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

private:
	Level();

	std::vector<Tileset> m_tilesets;
	std::vector<std::shared_ptr<Layer>> m_layers;

	friend class LevelParser;
};

#endif // !__Level__

