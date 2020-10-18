#include "Button.h"
#include <algorithm>
#include "Utils/CommonFcn.h"

namespace bestia {
namespace gui {

	Button::Button()
	{
		setFillColor(m_defaultColor);

		EventCallSFML<sf::Event::MouseEntered>::eventHandler = [this](const sf::Event&) {
			setActive(true);
			setFillColor(m_mouseOverColor);
		};

		EventCallSFML<sf::Event::MouseLeft>::eventHandler = [this](const sf::Event&) {
			setActive(false);
			setFillColor(m_defaultColor);
		};

		using namespace std::placeholders;
		event::system::connect<sf::Event::MouseMoved>(std::bind(&Button::onMouseEnteredEvent, this, _1), this);
		event::system::connect<sf::Event::MouseMoved>(std::bind(&Button::onMouseLeftEvent, this, _1), this);
		event::system::connect<sf::Event::MouseButtonPressed>(std::bind(&Button::onMouseButtonPressedEvent, this, _1), this);
	}

	Button::Button(const Button&) : Button()
	{
	}

	Button::~Button()
	{
		event::system::disconnect<sf::Event::MouseMoved>(this);
		event::system::disconnect<sf::Event::MouseButtonPressed>(this);
	}

	Button& Button::operator= (const Button& button)
	{
		if (this != &button)
		{
			using namespace std::placeholders;
			event::system::connect<sf::Event::MouseMoved>(std::bind(&Button::onMouseEnteredEvent, this, _1), this);
			event::system::connect<sf::Event::MouseMoved>(std::bind(&Button::onMouseLeftEvent, this, _1), this);
			event::system::connect<sf::Event::MouseButtonPressed>(std::bind(&Button::onMouseButtonPressedEvent, this, _1), this);
		}

		return *this;
	}

	void Button::setString(const sf::String& string)
	{
		m_string.setString(string);
		setAligment(m_stringAlign);
	}

	void Button::setFont(const sf::Font& font)
	{
		m_string.setFont(font);
		setAligment(m_stringAlign);
	}

	void Button::setCharacterSize(uint size)
	{
		m_string.setCharacterSize(size);
		setAligment(m_stringAlign);
	}

	void Button::setStringColor(const sf::Color& color)
	{
		m_string.setFillColor(color);
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		m_buttonShape.setSize(size);
		setAligment(m_stringAlign);
	}

	void Button::setFillColor(const sf::Color& color)
	{
		m_buttonShape.setFillColor(color);
	}

	void Button::setDefaultColor(const sf::Color& color)
	{
		m_defaultColor = color;
		setFillColor(m_defaultColor);
	}

	void Button::setMouseOverColor(const sf::Color& color)
	{
		m_mouseOverColor = color;
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		m_buttonShape.setPosition(position);
		setAligment(m_stringAlign);
	}

	void Button::setAligment(const alignment_t& align)
	{
		constexpr alignment_t pureVertical = EStringAlignment::Bottom | EStringAlignment::Top;
		constexpr alignment_t pureHorizontal = EStringAlignment::Left | EStringAlignment::Right;
		setVerticalAlignment(align &~ pureHorizontal);
		setHorizontalAlignment(align &~ pureVertical);
	}

	void Button::setActive(const bool isActive)
	{
		m_isActive = isActive;
	}

	const sf::String& Button::getString() const
	{
		return m_string.getString();
	}

	const sf::Vector2f& Button::getSize() const
	{
		return m_buttonShape.getSize();
	}

	const sf::Vector2f& Button::getPosition() const
	{
		return m_buttonShape.getPosition();
	}

	const sf::Color& Button::getFillColor() const
	{
		return m_buttonShape.getFillColor();
	}

	bool Button::isMouseOver(const sf::RenderWindow& window) const
	{
		auto mousePixelPos = sf::Mouse::getPosition(window);
		auto mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

		return m_buttonShape.getGlobalBounds().contains(mouseCoordPos.x, mouseCoordPos.y);
	}

	bool Button::fadeOut(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue)
	{
		sf::Color buttonColor = m_buttonShape.getFillColor();
		sf::Color stringColor = m_string.getFillColor();
		sf::Uint8 biggerAlpha = std::max(buttonColor.a, stringColor.a);

		if (biggerAlpha > targetValue)
		{
			if (biggerAlpha - targetValue > effectSpeed)
			{
				buttonColor.a = subSafely(buttonColor.a, effectSpeed);
				stringColor.a = subSafely(stringColor.a, effectSpeed);
			}
			else
			{
				buttonColor.a = subSafely<sf::Uint8>(buttonColor.a, biggerAlpha - targetValue);
				stringColor.a = subSafely<sf::Uint8>(stringColor.a, biggerAlpha - targetValue);
			}

			m_buttonShape.setFillColor(buttonColor);
			m_string.setFillColor(stringColor);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Button::fadeIn(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue)
	{
		sf::Color buttonColor = m_buttonShape.getFillColor();
		sf::Color stringColor = m_string.getFillColor();
		sf::Uint8 smallerAlpha = std::min(buttonColor.a, stringColor.a);

		if (smallerAlpha < targetValue)
		{
			if (targetValue - smallerAlpha > effectSpeed)
			{
				buttonColor.a = addSafely(buttonColor.a, effectSpeed);
				stringColor.a = addSafely(stringColor.a, effectSpeed);
			}
			else
			{
				buttonColor.a = addSafely<sf::Uint8>(buttonColor.a, targetValue - smallerAlpha);
				stringColor.a = addSafely<sf::Uint8>(stringColor.a, targetValue - smallerAlpha);
			}

			m_buttonShape.setFillColor(buttonColor);
			m_string.setFillColor(stringColor);
			return true;
		}
		else
		{
			return false;
		}
	}

	void Button::setVerticalAlignment(const alignment_t& vAlign)
	{
		constexpr float correctionY = 10; // TODO: why?
		const auto& rectanglePosY = m_buttonShape.getPosition().y - correctionY;
		const auto rectangleHeight = m_buttonShape.getLocalBounds().height + correctionY;

		const auto& stringPosX = m_string.getPosition().x;

		switch (vAlign)
		{
		case EStringAlignment::Top:
			m_string.setPosition(sf::Vector2f{ stringPosX, rectanglePosY });
			break;
		case EStringAlignment::Center:
		{
			const auto moveY = (rectangleHeight - m_string.getCharacterSize()) / 2;
			const auto stringPosY = rectanglePosY + moveY;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		case EStringAlignment::Bottom:
		{
			const auto moveY = rectangleHeight - m_string.getCharacterSize();
			const auto stringPosY = rectanglePosY + moveY;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		default:
			LOG("Wrong vertical alignment for button. Given alignment bitmask: " << vAlign << '\n');
			break;
		}
	}

	void Button::setHorizontalAlignment(const alignment_t& hAlign)
	{
		constexpr float correctionX = 2; // TODO: why?
		const auto& rectanglePosX = m_buttonShape.getPosition().x - correctionX;
		const auto rectangleWidth = m_buttonShape.getLocalBounds().width;

		const auto& stringPosY = m_string.getPosition().y;

		switch (hAlign)
		{
		case EStringAlignment::Left:
			m_string.setPosition(sf::Vector2f{ rectanglePosX, stringPosY });
			break;
		case EStringAlignment::Center:
		{
			const auto moveX = (rectangleWidth - m_string.getLocalBounds().width) / 2;
			const auto stringPosX = rectanglePosX + moveX;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		case EStringAlignment::Right:
		{
			const auto moveX = rectangleWidth - m_string.getLocalBounds().width;
			const auto stringPosX = rectanglePosX + moveX;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		default:
			LOG("Wrong horizontal alignment for button. Given alignment bitmask: " << hAlign << '\n');
			break;
		}
	}

	void Button::onMouseButtonPressedEvent(const sf::Event& event)
	{
		if (isMouseOver() && isActive())
		{
			EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler(event);
		}
	}

	void Button::onMouseEnteredEvent(const sf::Event& event)
	{
		if (isMouseOver() && !isActive())
		{
			EventCallSFML<sf::Event::MouseEntered>::eventHandler(event);
		}
	}

	void Button::onMouseLeftEvent(const sf::Event& event)
	{
		if (!isMouseOver() && isActive())
		{
			EventCallSFML<sf::Event::MouseLeft>::eventHandler(event);
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_buttonShape);
		target.draw(m_string);
	}

}}