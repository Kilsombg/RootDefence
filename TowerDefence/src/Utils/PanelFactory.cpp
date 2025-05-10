#include "../../include/UtilsHeaders/PanelFactory.h"

std::shared_ptr<PanelFactory> PanelFactory::s_pInstance = nullptr;

std::shared_ptr<PanelFactory> PanelFactory::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = std::shared_ptr<PanelFactory>(new PanelFactory());
		return s_pInstance;
	}
	return s_pInstance;
}

PanelFactory::PanelFactory()
{
}
