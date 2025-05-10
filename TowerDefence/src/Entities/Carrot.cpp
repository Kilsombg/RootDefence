#include "../../include/EntitiesHeaders/Carrot.h"

Carrot::Carrot() : Enemy()
{
}

void Carrot::draw()
{
	Enemy::draw();
}

void Carrot::update()
{
	Enemy::update();
}

void Carrot::clean()
{
	Enemy::clean();
}

void Carrot::load(const std::shared_ptr<LoaderParams> pParams)
{
	Enemy::load(pParams);
}

std::unique_ptr<GameObject> CarrotCreator::create() const
{
	return std::make_unique<Carrot>();
}
