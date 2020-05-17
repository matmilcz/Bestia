#pragma once

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

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
		void setColor(const sf::Color& color);
		void setInterline(const uint& interline);
		void setPosition(const sf::Vector2f&);

		std::vector <Text>::iterator begin();
		std::vector <Text>::iterator end();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector <Text> m_list;
		uint m_interline = 20;
	};

}