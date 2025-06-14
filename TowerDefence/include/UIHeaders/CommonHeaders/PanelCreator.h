#ifndef __PanelCreator__
#define __PanelCreator__

#include "Panel.h"

#include "../../UtilsHeaders/Creator.h"

/**
* Base Creator class for panels.
*/
class PanelCreator : public Creator<Panel>
{
public:
	virtual ~PanelCreator() {}
};

#endif // !__PanelCreator__
