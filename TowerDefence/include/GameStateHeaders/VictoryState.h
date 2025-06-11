#ifndef __VictoryState__
#define __VictoryState__

#include "GameState.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/VictoryStateUIHeaders/VictoryStateUI.h"

#include<memory>

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

	virtual std::string getStateID() const override;

	void setRewardValue(int rewardValue);

private:
	std::unique_ptr<VictoryStateUI> m_victoryStateUI;

	int m_rewardValue;
};


#endif // !__VictoryState__
