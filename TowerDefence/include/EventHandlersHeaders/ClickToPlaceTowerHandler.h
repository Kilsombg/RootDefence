#ifndef __ClickToPlaceListener__
#define __ClickToPlaceListener__

#include "BaseButtonHandler.h".h"

#include "../EntitiesHeaders/SDLGameObject.h"
#include "../EntitiesHeaders/TowerButton.h"

#include<vector>
#include<memory>

class ClickToPlaceTowerHandler : public BaseButtonHandler
{
public:
	ClickToPlaceTowerHandler();

	void handleEvent(Button* sourceButton);
	void update(std::vector<std::unique_ptr<GameObject>>& gameObjects);
	void clear();

	std::unique_ptr<SDLGameObject>& getShadowObject();

private:
	void handleIdleState(Button* sourceButton);
	void handleMovingState(Button* sourceButton);
	void createShadowObject();
	void setShadowObjectPosition();
	void interrupt();
	bool addObject(std::vector<std::unique_ptr<GameObject>>& gameObjects);

	enum clickToPlaceTowerStates
	{
		IDLE = 0,
		MOVING = 1,
		PLACING = 2,
		INTERRUPTED = 3
	};

	clickToPlaceTowerStates m_state;
	TowerButton* m_activeButton;
	std::unique_ptr<SDLGameObject> m_shadowObject;
};

#endif // !__ClickToPlaceListener__
