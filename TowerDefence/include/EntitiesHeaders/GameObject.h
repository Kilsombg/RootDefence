#ifndef __GameObject__
#define __GameObject__

#include "../UtilsHeaders/LoaderParams.h"
#include "../UtilsHeaders/Vector2D.h"

#include<memory>
#include<string>

/**
* Base class for each object in RootDefence.
*/
class GameObject
{
public:
	virtual ~GameObject();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void load(const std::shared_ptr<LoaderParams> pParams) = 0;

protected:
	GameObject();
	
	int m_width;
	int m_height;
	std::string m_textureID;

	Vector2D m_position;
};

#endif // !__GameObject__

