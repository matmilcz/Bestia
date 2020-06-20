#pragma once

#include <SFML/Graphics.hpp>
#include "ExtendedSFML/RoundedRectangleShape.h"
#include "Window.h"
#include "EventSystem/EventDispatcher.h"

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

	class Button : 
		public sf::Drawable, 
		public event::MouseButtonPressedEvent,
		public event::MouseEnteredEvent,
		public event::MouseLeftEvent
	{
	public:
		Button();
		Button(const Button&);
		~Button();
		Button& operator= (const Button& button);

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
		void setActive(const bool isActive);

		virtual void onMouseButtonPressedEvent(const sf::Event& event) override;
		virtual void onMouseEnteredEvent(const sf::Event& event) override;
		virtual void onMouseLeftEvent(const sf::Event& event) override;

		const sf::String& getString() const;
		const sf::Vector2f& getSize() const;
		const sf::Vector2f& getPosition() const;

		inline bool isActive() const
		{
			return m_isActive;
		}
		bool isMouseOver(const sf::RenderWindow& window = Window::getRenderWindow()) const;

	private:
		sf::Text m_string;
		sf::extended::RoundedRectangleShape m_roundedRectangle{ sf::Vector2f{50, 30}, 5, 5 };
		EVerticalAlignment m_vAlign = EVerticalAlignment::Center;	// TODO: keep alignment in one variable
		EHorizontalAlignment m_hAlign = EHorizontalAlignment::Center;
		bool m_isActive = false;

		void setVerticalAlignment(const EVerticalAlignment& vAlign);
		void setHorizontalAlignment(const EHorizontalAlignment& hAlign);
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}