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

	 void setPosition(const Vector2D newPosition);
	Vector2D& getPosition();
	int getWidth() const;
	int getHeight() const;

protected:
	SDLGameObject();
	SDLGameObject(const SDLGameObject& gameObject);

	Vector2D m_velocity;
	Vector2D m_acceleration;
	
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
};

#endif // !__SDLGameObject__
