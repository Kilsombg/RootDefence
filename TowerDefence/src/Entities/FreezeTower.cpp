#include "../../include/EntitiesHeaders/FreezeTower.h"

#include "../../include/Constants/LoaderParamsConsts.h"

FreezeTower::FreezeTower() : Tower(), m_freezePercentage(0)
{
}

void FreezeTower::load(const std::shared_ptr<LoaderParams> pParams)
{
	Tower::load(pParams);
	m_freezePercentage = pParams->getAttribute<float>(LoaderParamsConsts::freezePercentage);
}

void FreezeTower::targetEnemy(std::vector<std::shared_ptr<Enemy>> enemies)
{
	if (enemies.empty()) return;

	// slow each enemy in radius
	for (std::vector<std::shared_ptr<Enemy>>::size_type i = 0; i < enemies.size(); i++)
	{
		if (inRadius(enemies[i]))
		{
			enemies[i]->slow(m_freezePercentage);
		}
	}
}

std::unique_ptr<GameObject> FreezeTowerCreator::create() const
{
	return std::make_unique<FreezeTower>();
}
