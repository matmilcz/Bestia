#pragma once

#include <SFML/Graphics.hpp>
#include "ExtendedSFML/RoundedRectangleShape.h"
#include "Utils/Log.h"

namespace bestia {
namespace gui {

	using uint = unsigned int;

	enum class EVerticalAlignment
	{
		Top,
		Center,
		Bottom
	};

	enum class EHorizontalAlignment
	{
		Left,
		Center,
		Right,
	};

	class Button : public sf::Drawable
	{
	public:
		Button() = default; // TODO: more c-tors
		~Button() = default;

		void setString(const sf::String& string);
		void setFont(const sf::Font& font);
		void setCharacterSize(uint size);
		void setStringColor(const sf::Color& color);

		void setSize(const sf::Vector2f& size);
		void setCornersRadius(float radius);
		void setCornerPointCount(uint count);
		void setFillColor(const sf::Color& color);

		void setPosition(const sf::Vector2f& position);
		void setAligment(const EVerticalAlignment& vAlign, const EHorizontalAlignment& hAlign);

	private:
		sf::Text m_string;
		sf::extended::RoundedRectangleShape m_roundedRectangle{ sf::Vector2f{50, 30}, 5, 5 };

		void setVerticalAlignment(const EVerticalAlignment& vAlign);
		void setHorizontalAlignment(const EHorizontalAlignment& hAlign);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}