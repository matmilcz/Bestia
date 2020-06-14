#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "ExtendedSFML/RoundedRectangleShape.h"
#include "Window.h"
#include "EventSystem/EventDispatcher.h"
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

	class Button : public sf::Drawable, public event::EventCaller
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

		void setOnMousePressedEvent(const std::function<void()>& onMousePressedEvent);
		void setOnMouseEnterEvent(const std::function<void()>& onMouseEnterEvent);
		void setOnMouseExitEvent(const std::function<void()>& onMouseExitEvent);
		void setOnMouseOverEvent(const std::function<void()>& onMouseOverEvent);

		virtual void onMousePressedEvent(const sf::Event& event);
		virtual void onMouseEnterEvent(const sf::Event& event);
		virtual void onMouseExitEvent(const sf::Event& event);

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

		std::function<void()> m_onMousePressedEvent;
		std::function<void()> m_onMouseEnterEvent = [this]() {
			setFillColor(sf::Color::Blue);
		};
		std::function<void()> m_onMouseExitEvent = [this]() {
			setFillColor(sf::Color::White);
		};
		std::function<void()> m_onMouseOverEvent;

		void setVerticalAlignment(const EVerticalAlignment& vAlign);
		void setHorizontalAlignment(const EHorizontalAlignment& hAlign);
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}