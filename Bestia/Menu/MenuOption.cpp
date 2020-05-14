#include "MenuOption.h"

bool Bestia::MenuOption::isMouseOver(const sf::RenderWindow& window) const
{
	auto mousePixelPos = sf::Mouse::getPosition(window);
	auto mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

	return getGlobalBounds().contains(mouseCoordPos.x, mouseCoordPos.y);
}
