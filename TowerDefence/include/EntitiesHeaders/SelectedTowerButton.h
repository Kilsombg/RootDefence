#ifndef __SelectedTowerButon__
#define __SelectedTowerButon__

#include "Button.h"
#include "Tower.h"

#include<memory>

class SelectedTowerButton : public Button
{
public:
	SelectedTowerButton();

	virtual void load(const std::shared_ptr<LoaderParams> pParams);

	void setSelectedTower(std::shared_ptr<Tower> selectedTower);
	
protected:
	std::shared_ptr<Tower> m_selectedTower;
};

#endif // !__SelectedTowerButon__
