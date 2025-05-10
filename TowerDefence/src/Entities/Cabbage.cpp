#include "../../include/EntitiesHeaders/Cabbage.h"

Cabbage::Cabbage() : Enemy()
{
}

void Cabbage::draw()
{
	Enemy::draw();
}

void Cabbage::update()
{
	Enemy::update();
}

void Cabbage::clean()
{
	Enemy::clean();
}

void Cabbage::load(const std::shared_ptr<LoaderParams> pParams)
{
	Enemy::load(pParams);
}

std::unique_ptr<GameObject> CabbageCreator::create() const
{
	return std::make_unique<Cabbage>();
}
