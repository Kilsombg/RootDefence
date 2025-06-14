#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"

#include "../UtilsHeaders/Vector2D.h"

#include<memory>

/**
* Base game object that has animation and movement.
*/
class SDLGameObject : public GameObject
{
public:
	SDLGameObject();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	 virtual void load(const std::shared_ptr<LoaderParams> pParams) override;

	 // setter and getters

	 void setPosition(const Vector2D newPosition);
	Vector2D& getPosition();
	int getWidth() const;
	int getHeight() const;

protected:
	SDLGameObject(const SDLGameObject& gameObject);

	Vector2D m_velocity;
	Vector2D m_acceleration;
	
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
};

#endif // !__SDLGameObject__
