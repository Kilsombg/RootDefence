#ifndef __InputHandler__
#define __InputHandler__

#include "SDL.h"
#include "Vector2D.h"

#include<vector>
#include<unordered_map>
#include<memory>

/**
* Mouse buttons.
*/
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

/**
* Manages mouse and keyboard input in the program.
* 
* Save input state for the frame with update().
* 
* Calls getMouseButtonState() to get mouse state.
* Calls isKeyDown() or isKeyPressed() for keyboard input.
*/
class InputHandler
{
public:
	static InputHandler* Instance();
	/**
	* Update input state.
	*/
	void update();
	/**
	* Cleans InputHandler.
	* 
	* Calls this on exit.
	*/
	void clean();
	/**
	* Reset mouse buttons' states.
	*/
	void reset();
	/**
	* Get mouse button state.
	* 
	* @param buttonNumber - id of mouse button. (mouse_button enum)
	*/
	bool getMouseButtonState(int buttonNumber);
	/**
	* Get mouse possition.
	*/
	std::shared_ptr<Vector2D> getMousePosition();
	/**
	* @param pos - position of object.
	* @param width, height of the object.
	* @return if mouse position is inside object.
	*/
	bool isMouseOnObject(Vector2D pos, int width, int height);
	/**
	* Check if key is down.
	*/
	bool isKeyDown(SDL_Scancode key);
	/**
	* Check if key is pressed and set to false afterwards.
	*/
	bool isKeyPressed(SDL_Scancode key);

private:
	InputHandler();
	~InputHandler();

	static InputHandler* s_pInstance;
	
	// handle keyboard events

	void onKeyDown(SDL_Event& event);
	void onKeyUp(SDL_Event& event);

	// handle mouse events

	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	std::vector<bool> m_mouseButtonStates;
	std::shared_ptr<Vector2D> m_mousePosition;
	const Uint8* m_keystates;
	std::unordered_map<SDL_Scancode, bool> m_keyPressed;
};
typedef InputHandler TheInputHandler;

#endif // !__InputHandler__
