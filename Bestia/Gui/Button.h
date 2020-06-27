#pragma once

#include <SFML/Graphics.hpp>
#include "ExtendedSFML/RoundedRectangleShape.h"
#include "Window.h"
#include "EventSystem/EventDispatcher.h"

namespace bestia {
namespace gui {

	using uint = unsigned int;
	using alignment_t = uint;

	enum EStringAlignment : alignment_t
	{
#define BIT(bit) (1 << (bit))
		Top = BIT(1),
		Bottom = BIT(2),
		Center = BIT(3),
		Left = BIT(4),
		Right = BIT(5)
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
		void setAligment(const alignment_t& alignment);
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
		alignment_t m_stringAlign = EStringAlignment::Center;
		bool m_isActive = false;

		void setVerticalAlignment(const alignment_t& vAlign);
		void setHorizontalAlignment(const alignment_t& hAlign);
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}