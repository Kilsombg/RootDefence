#ifndef __Text__
#define __Text__

#include "GameObject.h"

#include "../UtilsHeaders/BaseCreator.h"

#include<string>

/**
* Object to display text on screen.
*
* Call load() or parameterized constructor to create the object.
* If you need to update the text, use setMessage() and update() on each frame.
* Call clean() to clean the texture.
*/
class Text : public GameObject
{
public:
	Text();
	/**
	* Object to display text on screen.
	*
	* @param x,y - position of text
	* @param width, height of the text
	* @param id - textureId
	* @param message to be displayed
	*/
	Text(float x, float y, int characterWidth, int width, int height, std::string textureID, std::string labelID, std::string message, bool dynamic = false);
	/**
	* Draw text on sccreen.
	*/
	void draw() override;
	/**
	* Update text's message if needed.
	*/
	void update() override;
	/**
	* Clean text's texture in TrueTypeManager.
	*/
	void clean() override;
	/**
	* Load text's params.
	*
	* @param pParams - parameters in key-value way.
	*/
	void load(const std::shared_ptr<LoaderParams> pParams) override;

	// setters and getters

	/**
	* Change text's message.
	*/
	void setMessage(std::string message);
	/**
	* Get label identifier for dynamics text, which updates on each frame.
	*/
	std::string getLabelID();
	/**
	* Return true if the text is dynamic - its message is changing each frame.
	*/
	bool getDynamic();

private:
	/**
	* Load text texture into TrueTypeManager.
	*/
	void loadTexture();

	std::string m_message; // message to be displayed
	std::string m_prevMessage; // for checking a change
	std::string m_labelID; // identifies the label
	int m_characterWidth; // width for one character, dynamicaly changes with message's length
	bool m_dynamic; // true if message is changing, otherwise false. When true - update() is called each frame.
};


class TextCreator : public BaseCreator
{
	virtual std::unique_ptr<GameObject> create() const;
};

#endif // !__Text__
