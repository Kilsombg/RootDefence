#ifndef __FreezeTower__
#define __FreezeTower__

#include "Tower.h"

#include "../UtilsHeaders/BaseCreator.h"

/**
* Tower that freezes enemies in radius.
*/
class FreezeTower : public Tower
{
public:
	FreezeTower();

	void load(const std::shared_ptr<LoaderParams> pParams) override;

	/**
	* Each enemy in radius is effected.
	*/
	virtual void targetEnemy(std::shared_ptr<std::vector<std::shared_ptr<Enemy>>> enemies) override;
	virtual void aimEnemy() override {};

	// getter and setter
	float getFreezePercentage();
	void setFreezePercentage(float freezePercentage);

private:
	float m_freezePercentage;
};


class FreezeTowerCreator : public BaseCreator
{
	virtual std::unique_ptr<GameObject> create() const;
};

#endif // !__FreezeTower__
