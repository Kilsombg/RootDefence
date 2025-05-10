#ifndef __PanelFactory__
#define __PanelFactory__

#include "BaseFactory.h"

#include "../UIHeaders/CommonHeaders/Panel.h"
#include "../UIHeaders/CommonHeaders/PanelCreator.h"

#include<memory>

class PanelFactory : public BaseFactory<Panel, PanelCreator>
{
public:
	static std::shared_ptr< PanelFactory> Instance();

private:
	PanelFactory();
	static std::shared_ptr< PanelFactory> s_pInstance;
};

typedef PanelFactory ThePanelFactory;

#endif // !__PanelFactory__
