#include "../../../include/UIHeaders/PlayStateUIHeaders/TipsPanel.h"

#include "../../../include/Constants/UIConsts.h"
#include "../../../include/Constants/SettingsConsts.h"

TipsPanel::TipsPanel() : m_currentTipID(0)
{
}

void TipsPanel::draw()
{
	//  draw background
	m_backgroundTexture->draw();

	// draw labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->draw();
	}
}

void TipsPanel::update()
{
	updateTipOnScreen();
}

void TipsPanel::clean()
{
	// clean background texture
	m_backgroundTexture->clean();

	// clean objects texture
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	// clean labels
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->clean();
	}
}

void TipsPanel::load(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	// load relevant objects
	for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
	{
		if (std::unique_ptr<Text> pText = std::unique_ptr<Text>(dynamic_cast<Text*>(gameObjects[i].get())))
		{
			m_labelsMap[pText->getLabelID()] = std::move(pText);
			gameObjects[i].release();
		}
		else
		{
			m_gameObjects.push_back(std::move(gameObjects[i]));
		}
	}

	// load tips
	loadTips();

	// ser current tip to show
	m_currentTipID = rand() % m_tips.size();

	// load tips timer
	m_tipsTimer = Timer(20, 0);
}

void TipsPanel::updateTipOnScreen()
{
	// update timer
	m_tipsTimer.countDown(DELAY_TIME / 1000.);

	// timer expired
	if (m_tipsTimer.timeSIsZero())
	{
		m_currentTipID = (++m_currentTipID) % m_tips.size();

		// update dynamic labels
		updateDynamicLabel();

		// reset timer
		m_tipsTimer.resetToMax();
	}
}

void TipsPanel::updateDynamicLabel()
{
	m_labelsMap[UIConsts::tipMessageLabel]->setMessage(m_tips[m_currentTipID]);

	// update text on screen
	for (std::map<std::string, std::unique_ptr<Text>>::iterator it = m_labelsMap.begin(); it != m_labelsMap.end(); it++)
	{
		it->second->update();
	}
}

void TipsPanel::loadTips()
{
	m_tips = {
		std::string("Press Start button or click SPACE to begin a wave."),
		std::string("There are three types of enemies - green, yellow and red. Each enemy type drops unique resources."),
		std::string("Blue Bean has damage resistance against every tower type."),
		std::string("Agate, amber and ruby towers deal different damage multiplayer against each enemy type."),
		std::string("Go to settings to see a table of damage against enemies."),
		std::string("Stump has standard stats. Pine has high att.speed, but lower damage. Oak is vice versa."),
		std::string("Frozen bush doesn't do damage, but slows enemies."),
		std::string("Blue bean drops sapphires, which are used to buy frozen bush"),
		std::string("If you placed a tower on unwanted place you can sell it."),
		std::string("Each tower type uses its own resource - easy to gather resources for towers."),
		std::string("Some towers have large placement area, so plan ahead your placements."),
		std::string("A wise man once said - upgraded tower is always better than not upgraded."),
		std::string("Hover tower's upgrade button to preview stat changes.")
	};
}

std::unique_ptr<Panel> TipsPanelCreator::create() const
{
	return std::make_unique<TipsPanel>();
}
