#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Bestia {

	using uint = unsigned int;

	class MenuOption : public sf::Text
	{
	public:
		MenuOption(const sf::String& string, const sf::Font& font, uint characterSize = 30)
			: sf::Text{ string, font, characterSize }
		{
		}

		~MenuOption()
		{
		}

		bool isMouseOver(const sf::RenderWindow& window) const;

	private:

	};

}

