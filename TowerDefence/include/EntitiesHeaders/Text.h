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
	Text(float x, float y, int width, int height, std::string id, std::string message);
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

private:
	/**
	* Load text texture into TrueTypeManager.
	*/
	void loadTexture();

	std::string m_message; // message to be displayed
	std::string m_prevMessage; // for checking a change
};


class TextCreator : public BaseCreator
{
	virtual std::unique_ptr<GameObject> create() const;
};

#endif // !__Text__
