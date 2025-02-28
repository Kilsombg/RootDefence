#include "../../include/UtilsHeaders/TowerFactory.h"
#include "../../include/UtilsHeaders/GameObjectData.h"
#include "../../include/UtilsHeaders/GameObjectFactory.h"
#include "../../include/UtilsHeaders/LoaderParams.h"
#include "../../include/UtilsHeaders/InputHandler.h"


#include "../../include/Constants/LoaderParamsConsts.h"

#include<memory>


std::shared_ptr<TowerFactory> TowerFactory::s_pInstance = nullptr;

TowerFactory::TowerFactory() {}


std::shared_ptr<TowerFactory> TowerFactory::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<TowerFactory>(new TowerFactory);
		return s_pInstance;
	}
	return s_pInstance;
}

std::unique_ptr<GameObject> TowerFactory::createTower(std::string towerTypeID)
{
	return std::unique_ptr<GameObject>();
}

std::unique_ptr<Tower> TowerFactory::createShadowTower(std::string towerTypeID)
{
	if (std::unique_ptr<GameObject>	towerObject = TheGameObjectFactory::Instance()->create(towerTypeID))
	{
		if (std::unique_ptr<Tower> shadowObject = std::unique_ptr<Tower>(dynamic_cast<Tower*>(towerObject.release())))
		{
			std::shared_ptr<LoaderParams> params = m_towerObjectData->getData(towerTypeID);
			std::shared_ptr<Vector2D> mousePos = InputHandler::Instance()->getMousePosition();
			params->setAttribute(LoaderParamsConsts::x, mousePos->getX());
			params->setAttribute(LoaderParamsConsts::y, mousePos->getY());

			shadowObject->load(params);

			return std::move(shadowObject);
		}
		else {
			towerObject.reset();  // remove object to prevent memory leak
		}
	}
	return NULL;
}

void TowerFactory::setGameObjectData(GameObjectData* gameObjectdata)
{
	m_towerObjectData = std::make_unique<GameObjectData>(*gameObjectdata);
}