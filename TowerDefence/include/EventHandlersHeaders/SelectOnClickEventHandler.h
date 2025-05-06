#ifndef __SelectOnClickEventHandler__
#define __SelectOnClickEventHandler__

#include "../UtilsHeaders/Vector2D.h"

// area for second click to deselect
struct CloseArea
{
	float m_areaX;
	float m_areaY;
	int m_areaWidth;
	int m_areaHeight;
};

/**
* Event handler for objects that can be selected. Call update() and handleEvent() on each frame and get whether the object is selected with isSelected().
*/
class SelectOnClickEventHandler
{
public:
	/**
	* Event handler for objects that can be selected. Call update() and handleEvent() on each frame and get whether the object is selected with isSelected().
	* Set keyInteruptible to false to exclude interruption with key.
	*
	* @param pos, width and height are object's attributes
	* @param closeArea is area for second click to deselect
	* @param keyInteruptible is flag to be interruptible selection with key or not
	*/
	SelectOnClickEventHandler(Vector2D pos, int width, int height, CloseArea closeArea = {-1, -1, 0, 0}, bool keyInterruptible = true);
	/**
	* Event handler for objects that can be selected. Call update() and handleEvent() on each frame and get whether the object is selected with isSelected().
	*/
	SelectOnClickEventHandler();

	// update on each frame
	void update();
	// handle on each frame
	void handleEvent();
	// get selection state of the object
	bool isSelected();

private:
	void resetParams();
	void handleInterruptEvent();
	void handleOutsideCLick();
	void handleClickOnButton();

	/**
	* when given area restriction, check whether mouse position is in that area for the second click
	*/
	bool isMouseInsideArea();

	Vector2D m_objPos;
	int m_objWidth;
	int m_objHeight;
	// area for the second click
	CloseArea m_closeArea;
	// to be interruptible selection with key or not
	bool m_keyInterruptible;

	bool m_selected;
	bool m_pressed;
	bool m_isMouseOnObject;
	bool m_pressedOutside;
};

#endif // !__SelectOnClickEventHandler__
