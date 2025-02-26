#ifndef __InputHandler__
#define __InputHandler__

#include "SDL.h"
#include "Vector2D.h"

#include<vector>
#include<unordered_map>
#include<memory>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance();
	void update();
	void clean();
	void reset();

	bool getMouseButtonState(int buttonNumber);
	std::shared_ptr<Vector2D> getMousePosition();
	
	bool isKeyDown(SDL_Scancode key);
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
