#ifndef __Panel__
#define __Panel__

#include "../../EntitiesHeaders/GameObject.h"
#include "../../EntitiesHeaders/Texture.h"

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
	std::vector<std::string> m_textureIDList;
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	std::unique_ptr<Texture> m_backgroundTexture;
};

#endif // !__Panel__
