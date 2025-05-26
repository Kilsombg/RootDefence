#ifndef __VictoryState__
#define __VictoryState__

#include "MenuState.h"

#include "../EntitiesHeaders/GameObject.h"

#include "../UIHeaders/VictoryStateUIHeaders/VictoryStateUI.h"

#include<memory>

class VictoryState : public MenuState
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

	virtual std::string getStateID() const override;

	void setCurrentWaveID(int currentWaveID);

private:
	std::unique_ptr<VictoryStateUI> m_victoryStateUI;

	int m_currentWaveID;
};


#endif // !__VictoryState__
