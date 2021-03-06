#include "Text.h"

namespace bestia {

	Text::Text(const sf::String& string, const sf::Font& font, const uint& characterSize = 30)
		: sf::Text{ string, font, characterSize }
	{
	}

	bool Text::isMouseOver(const sf::RenderWindow& window) const
	{
		auto mousePixelPos = sf::Mouse::getPosition(window);
		auto mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

		return getGlobalBounds().contains(mouseCoordPos.x, mouseCoordPos.y);
	}

}
