#include "../../include/UtilsHeaders/InputHandler.h"

#include "../../include/Game.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler() : m_mousePosition(new Vector2D(0, 0))
{
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}

	m_keystates = SDL_GetKeyboardState(0);
}

InputHandler* InputHandler::Instance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new InputHandler();
	}
	return s_pInstance;
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::clean()
{
	delete s_pInstance;
	s_pInstance = nullptr;

	m_keystates = nullptr;
}

void InputHandler::reset()
{
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates[i] = false;
	}
}

InputHandler::~InputHandler()
{
}


bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}

std::shared_ptr<Vector2D> InputHandler::getMousePosition()
{
	return m_mousePosition;
}

bool InputHandler::isMouseOnObject(Vector2D pos, int width, int height)
{
	return m_mousePosition->getX() < (pos.getX() + width)
		&& m_mousePosition->getX() > pos.getX()
		&& m_mousePosition->getY() < (pos.getY() + height)
		&& m_mousePosition->getY() > pos.getY();
}


bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}



void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		m_mouseButtonStates[LEFT] = false;
		break;

	case SDL_BUTTON_MIDDLE:
		m_mouseButtonStates[MIDDLE] = false;
		break;

	case SDL_BUTTON_RIGHT:
		m_mouseButtonStates[RIGHT] = false;
		break;

	default:
		break;
	}
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

bool InputHandler::isKeyPressed(SDL_Scancode key)
{
	bool pressed = m_keyPressed[key];
	m_keyPressed[key] = false;
	return pressed;
}

void InputHandler::onKeyDown(SDL_Event& event)
{
	m_keystates = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		m_keyPressed[event.key.keysym.scancode] = true;
	}
}

void InputHandler::onKeyUp(SDL_Event& event)
{
	m_keystates = SDL_GetKeyboardState(NULL);

	m_keyPressed[event.key.keysym.scancode] = false;
}