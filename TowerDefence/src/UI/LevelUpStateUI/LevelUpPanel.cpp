#include "../../../include/UIHeaders/LevelUpUIHeaders/LevelUpPanel.h"

#include "../../../include/Game.h"

#include "../../../include/Constants/LoaderParamsConsts.h"
#include "../../../include/Constants/UIConsts.h"

#include "../../../include/EntitiesHeaders/MenuButton.h"

#include "../../../include/UtilsHeaders/LoaderParams.h"
#include "../../../include/UtilsHeaders/InputHandler.h"
#include "../../../include/UtilsHeaders/TextFormatter.h"
#include "../../../include/UtilsHeaders/TowerFactory.h"

LevelUpPanel::moveState LevelUpPanel::s_moveState = DOWN;

LevelUpPanel::LevelUpPanel() : MenuInteractivePanel(), m_clickedInside(false)
{
}

void LevelUpPanel::draw()
{
	m_backgroundTexture->draw();

	// draw textures
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

	// draw buttons
	MenuInteractivePanel::draw();

	// draw labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->draw();
	}

	// draw tower unlocked
	if (m_towerUnlockedTexture) m_towerUnlockedTexture->draw();
}

void LevelUpPanel::update()
{
	// move panel
	updateMoveState();

	// update buttons
	MenuInteractivePanel::update();
}

void LevelUpPanel::clean()
{
	// set static fields to default
	s_moveState = DOWN;

	// clean panel
	MenuInteractivePanel::clean();

	// clean tower unlocked texture
	if (m_towerUnlockedTexture) m_towerUnlockedTexture->clean();
}

void LevelUpPanel::handleEvents()
{
	// handle input
	if (s_moveState == IDLE) handleClickOutside();

	// handle buttons
	MenuInteractivePanel::handleEvents();
}

void LevelUpPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		// load buttons
		if (std::unique_ptr<MenuButton> pButton = std::unique_ptr<MenuButton>(dynamic_cast<MenuButton*>(gameObjects[i].get())))
		{
			m_buttonObjects.push_back(std::make_shared<MenuButton>(std::move(pButton.get())));
			gameObjects[i].release();
		}
		// load labels
		else if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_labelsMap[pText->getLabelID()] = std::move(pText);
			gameObjects[i].release();
		}
		else
		{
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load static labels
	loadStaticLabels();

	// load callbacks
	loadCallbacks();
}

void LevelUpPanel::loadCallbacks()
{
	m_callbacks[LoaderParamsConsts::returnToPlayCallbackID] = s_returnToPlay;

	setCallbacks();
}

void LevelUpPanel::setTowerUnlockID(std::string name)
{
	if (name == std::string()) return;

	//seperate texture id to get tower's name
	std::vector<std::string> words = TextFormatter::splitCamelCase(name);
	if (words.size() < 3) return;

	std::string towerID;
	if (TowerFactory::Instance()->canTowerBeColored(words[0]))
	{
		// colored towers
		towerID = words[1];
		towerID[0] = std::tolower(towerID[0]);
	}
	else // special towers
	{
		towerID = words[0] + words[1];
	}
	auto pParams = TowerFactory::Instance()->getTowerData(towerID);

	// set up tower texture
	createTowerUnlockedTexture(name, pParams->getAttribute<int>(LoaderParamsConsts::width), pParams->getAttribute<int>(LoaderParamsConsts::height));

	// set up tower unlocked label
	createTowerUnklockLabel(words[0] + " " + words[1]);
}

void LevelUpPanel::s_returnToPlay()
{
	s_moveState = UP;
}

void LevelUpPanel::handleClickOutside()
{
	if (InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		if (!InputHandler::Instance()->isMouseOnObject(m_backgroundTexture->getPosition(), m_backgroundTexture->getWidth(), m_backgroundTexture->getHeight())
			&& !m_clickedInside)
		{
			s_returnToPlay();
		}
		else // clicked inside panel
		{
			m_clickedInside = true;
		}
	}
	else { m_clickedInside = false; }
}

void LevelUpPanel::loadStaticLabels()
{
	m_labelsMap[UIConsts::levelLUPLabel]->setMessage(std::to_string(TheGame::Instance()->getProgressManager()->getGameProgress()->level));
	m_labelsMap[UIConsts::levelLUPLabel]->centerText();

	// update labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->update();
	}
}

void LevelUpPanel::updateMoveState()
{
	switch (s_moveState)
	{
	case IDLE:
		break;
	case DOWN:
		movePanel(Vector2D(380, 100), 25);
		break;
	case UP:
		movePanel(Vector2D(380, -400), 25);
		break;
	case EXIT:
		updateExitMoveState();
	default:
		break;
	}
}

void LevelUpPanel::updateExitMoveState()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void LevelUpPanel::movePanel(Vector2D targetPoint, int speed)
{
	Vector2D velocity = calculateVelocity(targetPoint, speed);
	if (velocity.length() == 0) return;

	// move objects
	m_backgroundTexture->setPosition(m_backgroundTexture->getPosition() + velocity);

	// move buttons
	for (std::vector<std::shared_ptr<Button>>::size_type i = 0; i < m_buttonObjects.size(); i++)
	{
		m_buttonObjects[i]->setPosition(m_buttonObjects[i]->getPosition() + velocity);
	}

	// move textures
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		SDLGameObject* pObject = dynamic_cast<SDLGameObject*>(m_gameObjects[i].get());
		pObject->setPosition(pObject->getPosition() + velocity);
		pObject = nullptr;
	}

	// move tower unlocked
	if (m_towerUnlockedTexture) m_towerUnlockedTexture->setPosition(m_towerUnlockedTexture->getPosition() + velocity);

	// move labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->setPosition(it->second->getPosition() + velocity);
	}
}

Vector2D LevelUpPanel::calculateVelocity(Vector2D targetPoint, int speed)
{
	// point Panel to target
	Vector2D velocity = targetPoint - m_backgroundTexture->getPosition();

	// if Panel went to target point, then stop moving
	if (velocity.length() < speed)
	{
		// At first Panel is moving down so when getting to target point it sets to IDLE.
		// if Panel is not moving down that means that it is set to close - UP state.
		s_moveState = s_moveState == DOWN ? IDLE : EXIT;

		return Vector2D(0, 0);
	}

	// if target is far away get the direction to target and change the magnitude to projectile speed
	velocity.normalize();
	return velocity * speed;
}

void LevelUpPanel::createTowerUnlockedTexture(std::string textureID, int width, int heigh)
{
	m_towerUnlockedTexture = std::make_unique<Texture>();
	std::shared_ptr<LoaderParams> pParams = std::make_shared<LoaderParams>();


	pParams->setAttribute(LoaderParamsConsts::x, 420.f);
	pParams->setAttribute(LoaderParamsConsts::y, -265.f);
	pParams->setAttribute(LoaderParamsConsts::width, width);
	pParams->setAttribute(LoaderParamsConsts::height, heigh);
	pParams->setAttribute(LoaderParamsConsts::textureID, textureID + UIConsts::levelUpPanelSuffix);

	m_towerUnlockedTexture->load(pParams);
	m_towerUnlockedTexture->centerTexture();
}

void LevelUpPanel::createTowerUnklockLabel(std::string message)
{
	m_labelsMap[UIConsts::unlockedLabel]->setHidden(false);

	m_labelsMap[UIConsts::towerUnlockedLabel]->setHidden(false);
	m_labelsMap[UIConsts::towerUnlockedLabel]->setMessage(message);
	m_labelsMap[UIConsts::towerUnlockedLabel]->centerText();
	m_labelsMap[UIConsts::towerUnlockedLabel]->update();
}

std::unique_ptr<Panel> LevelUpPanelCreator::create() const
{
	return std::make_unique<LevelUpPanel>();
}
