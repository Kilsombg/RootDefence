#ifndef __Panel__
#define __Panel__

#include "../../EntitiesHeaders/GameObject.h"
#include "../../EntitiesHeaders/Texture.h"
#include "../../EntitiesHeaders/Text.h"

#include<vector>
#include<string>
#include<memory>

/**
* base class for panels
*/
class Panel
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load(std::vector<std::unique_ptr<GameObject>> gameObjects) = 0;

	void setBackgroundTexture(std::unique_ptr<Texture> backgroundTexture) { m_backgroundTexture = std::move(backgroundTexture); }

protected:
	std::vector<std::string> m_textureIDList; // all texture the panel has
	std::vector<std::unique_ptr<GameObject>> m_gameObjects; // left game objects in panel
	std::unique_ptr<Texture> m_backgroundTexture; // background texture
	std::map<std::string, std::unique_ptr<Text>> m_labelsMap; // map of labels for each panel
};

#endif // !__Panel__
