#pragma once

#include <SFML/Graphics.hpp>
#include "ExtendedSFML/RoundedRectangleShape.h"
#include "Window.h"
#include "System/EventSystem/System.h"
#include "Utils/Log.h"
#include <functional>
#include "Animation/FadeEffect.h"
#include <iostream>
#include "System/GameObject.h"
#include "Utils/CommonFcn.h"

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

	class ButtonNew : public system::GameObject
	{
	public:
		ButtonNew()
		{
			event::system::connect<sf::Event::MouseButtonPressed>([this](const sf::Event& e) { 
				const auto& drawArea = sf::Rect<float>(getPosition(), m_buttonShape.getSize());
				if (isMouseOver(drawArea))
				{
					onClick(this);
				}
				}, this);

			if (m_defaultFont.getInfo().family == "")
			{
				m_defaultFont.loadFromFile("Resources/fonts/calibri.ttf");
			}

			sf::Text text("BUTTON", m_defaultFont, 12);
			text.setFillColor(sf::Color::Black);
			text.setPosition({ 0, 0 });
			setText(text);

			const auto& drawArea = sf::Rect<float>(getPosition(), m_buttonShape.getSize());
			if (isMouseOver(drawArea))
			{
				m_isMouseOver = true;
			}
		}

		void setAlignment(const alignment_t& alignment)
		{
			m_alignment = alignment;

			const auto& oldPos = m_text.getPosition();
			const auto& buttonGlobalBounds = m_buttonShape.getGlobalBounds();
			const auto& textGlobalBounds = m_text.getGlobalBounds();

			switch (m_alignment)
			{
			case EStringAlignment::Left | EStringAlignment::Top:
				m_text.setPosition({ 0, 0 });
				break;
			case EStringAlignment::Left | EStringAlignment::Center:
				m_text.setPosition({ 0, buttonGlobalBounds.height / 2 - textGlobalBounds.top - textGlobalBounds.height / 2 });
				break;
			case EStringAlignment::Left | EStringAlignment::Bottom:
				m_text.setPosition({ 0,  buttonGlobalBounds.height - textGlobalBounds.top * 2 - textGlobalBounds.height });
				break;
			case EStringAlignment::Center | EStringAlignment::Top:
				m_text.setPosition({ buttonGlobalBounds.width / 2 - textGlobalBounds.left - textGlobalBounds.width / 2, 0 });
				break;
			case EStringAlignment::Center:
				m_text.setPosition({ buttonGlobalBounds.width / 2 - textGlobalBounds.left - textGlobalBounds.width / 2,
									 buttonGlobalBounds.height / 2 - textGlobalBounds.top - textGlobalBounds.height / 2 });
				break;
			case EStringAlignment::Center | EStringAlignment::Bottom:
				m_text.setPosition({ buttonGlobalBounds.width / 2 - textGlobalBounds.left - textGlobalBounds.width / 2,
									 buttonGlobalBounds.height - textGlobalBounds.top * 2 - textGlobalBounds.height });
				break;
			case EStringAlignment::Right | EStringAlignment::Top:
				m_text.setPosition({ buttonGlobalBounds.width - textGlobalBounds.left * 2 - textGlobalBounds.width, 0 });
				break;
			case EStringAlignment::Right | EStringAlignment::Center:
				m_text.setPosition({ buttonGlobalBounds.width - textGlobalBounds.left * 2 - textGlobalBounds.width,
									 buttonGlobalBounds.height / 2 - textGlobalBounds.top - textGlobalBounds.height / 2 });
				break;
			case EStringAlignment::Right | EStringAlignment::Bottom:
				m_text.setPosition({ buttonGlobalBounds.width - textGlobalBounds.left * 2 - textGlobalBounds.width,
									 buttonGlobalBounds.height - textGlobalBounds.top * 2 - textGlobalBounds.height });
				break;
			default:
				LOG("WRN: Incorrect text alignment\n");
				break;
			}
		}

		void setText(const sf::Text& text)
		{
			m_text = text;
			setAlignment(m_alignment);
		}

		void setShape(const sf::RectangleShape& shape)
		{
			m_buttonShape = shape;
		}

		const sf::Text& getText() const
		{
			return m_text;
		}

		const sf::RectangleShape& getShape() const
		{
			return m_buttonShape;
		}

		virtual void update() override
		{
			const auto& drawArea = sf::Rect<float>(getPosition(), m_buttonShape.getSize());
			if (isMouseOver(drawArea))
			{
				if (m_isMouseOver) // mouse over
				{
					onMouseOver(this);
				}
				else // mouse enter
				{
					m_isMouseOver = true;
					onMouseEnter(this);
				}
			}
			else if(m_isMouseOver) // mouse left
			{
				m_isMouseOver = false;
				onMouseLeft(this);
			}
		}

		std::function<void(ButtonNew*)> onClick = [this](ButtonNew*) {
			LOG("No onClick callback set for: " << this << '\n');
		};

		std::function<void(ButtonNew*)> onMouseOver = [this](ButtonNew*) {};

		std::function<void(ButtonNew*)> onMouseEnter = [this](ButtonNew*) {};

		std::function<void(ButtonNew*)> onMouseLeft = [this](ButtonNew*) {};

	private:
		static sf::Font m_defaultFont;

		sf::Text m_text;
		alignment_t m_alignment{ EStringAlignment::Center };
		sf::RectangleShape m_buttonShape{ sf::Vector2f{80, 30} };

		bool m_isMouseOver = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			states.transform *= getTransform();
			target.draw(m_buttonShape, states);
			target.draw(m_text, states);
		}
	};

	class Button : 
		public sf::Drawable, 
		public event::EventCallSFML<sf::Event::MouseButtonPressed>,
		public event::EventCallSFML<sf::Event::MouseEntered>,
		public event::EventCallSFML<sf::Event::MouseLeft>,
		public animation::effect::IFadeEffect
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
		void setFillColor(const sf::Color& color);
		void setDefaultColor(const sf::Color& color);
		void setMouseOverColor(const sf::Color& color);
		void setPosition(const sf::Vector2f& position);
		void setAligment(const alignment_t& alignment);
		void setActive(const bool isActive);

		void onMouseButtonPressedEvent(const sf::Event& event);
		void onMouseEnteredEvent(const sf::Event& event);
		void onMouseLeftEvent(const sf::Event& event);

		const sf::String& getString() const;
		const sf::Vector2f& getSize() const;
		const sf::Vector2f& getPosition() const;
		const sf::Color& getFillColor() const;

		inline bool isActive() const
		{
			return m_isActive;
		}
		bool isMouseOver(const sf::RenderWindow& window = Window::getRenderWindow()) const;

		virtual bool fadeOut(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue = animation::effect::DEFAULT_FADE_OUT_TARGET_VAL) override;
		virtual bool fadeIn(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue = animation::effect::DEFAULT_FADE_IN_TARGET_VAL) override;

	private:
		sf::Text m_string;
		sf::RectangleShape m_buttonShape{ sf::Vector2f{50, 30} };
		alignment_t m_stringAlign = EStringAlignment::Center;
		sf::Color m_defaultColor = sf::Color::White;
		sf::Color m_mouseOverColor = sf::Color::Blue;
		bool m_isActive = false;

		void setVerticalAlignment(const alignment_t& vAlign);
		void setHorizontalAlignment(const alignment_t& hAlign);
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}}