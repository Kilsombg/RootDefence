#ifndef __FreezeTower__
#define __FreezeTower__

#include "Tower.h"

#include "../UtilsHeaders/BaseCreator.h"

/**
* Tower that slows enemies in radius.
*/
class FreezeTower : public Tower
{
public:
	FreezeTower();

	void load(const std::shared_ptr<LoaderParams> pParams) override;

	/**
	* Each enemy in radius is effected.
	*/
	virtual void targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies);
	virtual void aimEnemy() {};

	// getter and setter
	float getFreezePercentage();

private:
	float m_freezePercentage;
};


class FreezeTowerCreator : public BaseCreator
{
	virtual std::unique_ptr<GameObject> create() const;
};

#endif // !__FreezeTower__
