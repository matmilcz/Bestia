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
		Button() = default;
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

		const sf::String& getString() const;
		const sf::Vector2f& getSize() const;
		const sf::Vector2f& getPosition() const;

		bool isMouseOver(const sf::RenderWindow& window) const;

	private:
		sf::Text m_string;
		sf::extended::RoundedRectangleShape m_roundedRectangle{ sf::Vector2f{50, 30}, 5, 5 };
		EVerticalAlignment m_vAlign = EVerticalAlignment::Center;	// TODO: keep alignment in one variable
		EHorizontalAlignment m_hAlign = EHorizontalAlignment::Center;

		void setVerticalAlignment(const EVerticalAlignment& vAlign);
		void setHorizontalAlignment(const EHorizontalAlignment& hAlign);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}