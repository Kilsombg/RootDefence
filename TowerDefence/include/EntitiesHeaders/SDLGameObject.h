#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"

#include "../UtilsHeaders/Vector2D.h"

#include<memory>

class SDLGameObject : public GameObject
{
public:
	virtual void draw();
	virtual void update();
	virtual void clean();

	 virtual void load(const std::shared_ptr<LoaderParams> pParams);

	Vector2D& getPosition();
	int getWidth();
	int getHeight();

protected:
	SDLGameObject();

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	
	std::string m_textureID;
};

#endif // !__SDLGameObject__
