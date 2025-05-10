#ifndef __PanelCreator__
#define __PanelCreator__

#include "Panel.h"

#include "../../UtilsHeaders/Creator.h"

#include<memory>

class PanelCreator : public Creator<Panel>
{
public:
	virtual ~PanelCreator() {}
};

#endif // !__PanelCreator__
