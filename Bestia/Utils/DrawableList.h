#pragma once

#include <vector>
#include <initializer_list>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include "Utils/Text.h"

namespace bestia {

	using uint = unsigned int;

	class DrawableList : public sf::Drawable
	{
	public:
		DrawableList() = default;
		DrawableList(std::initializer_list <Text> list);
		DrawableList(const DrawableList&) = default;
		~DrawableList() = default;
		DrawableList& operator= (const DrawableList&) = default;

		Text& operator[] (const int idx);

		void add(const Text& text);
		void add(const sf::String& string);
		void setColor(const sf::Color& color);
		void setFont(const sf::Font& font);
		void setSize(const uint& size);
		void setInterline(const uint& interline);
		void setPosition(const sf::Vector2f& desiredPos); // TODO: currently needs to be called after list initialization

		std::vector <Text>::iterator begin();
		std::vector <Text>::iterator end();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector <Text> m_list;
		sf::Color m_color = sf::Color::White;
		sf::Font m_font;
		uint m_interline = 20;
		uint m_size = 30;
	};

}