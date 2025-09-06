#ifndef __VictoryState__
#define __VictoryState__

#include "GameState.h"

#include "../UIHeaders/VictoryStateUIHeaders/VictoryStateUI.h"

#include<memory>

/**
* GameState when victory occurs.
* 
* If all waves are finished and still has positive health points from PlayState, then VictoryState occurs.
*/
class VictoryState : public GameState
{
public:
	VictoryState();

	// override methods

	virtual void update() override;
	virtual void render() override;

	virtual bool onEnter() override;
	virtual bool onExit() override;

	void handleEvents() override;

	bool drawUnderneath() override;

	// getters and setters

	void setRewardValue(int rewardValue);

private:
	std::unique_ptr<VictoryStateUI> m_victoryStateUI;

	int m_rewardValue;
};


#endif // !__VictoryState__
