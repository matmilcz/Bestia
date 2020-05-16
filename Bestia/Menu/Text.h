#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Bestia {

	using uint = unsigned int;

	class Text : public sf::Text
	{
	public:
		Text(const sf::String& string, const sf::Font& font, const uint& characterSize);
		Text(const Text&) = default;
		~Text() = default;
		Text& operator= (const Text&) = default;

		bool isMouseOver(const sf::RenderWindow& window) const;

	private:

	};

}

