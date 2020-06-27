#include "Button.h"

namespace bestia {
namespace gui {

	Button::Button()
	{
		setOnMouseEnteredEvent([this](const sf::Event& event) {
			setFillColor(sf::Color::Blue);
			});

		setOnMouseLeftEvent([this](const sf::Event& event) {
			setFillColor(sf::Color::White);
			});

		using namespace std::placeholders;
		event::EventDispatcher<sf::Event::MouseMoved>::add(std::bind(&Button::onMouseEnteredEvent, this, _1), this);
		event::EventDispatcher<sf::Event::MouseMoved>::add(std::bind(&Button::onMouseLeftEvent, this, _1), this);
		event::EventDispatcher<sf::Event::MouseButtonPressed>::add(std::bind(&Button::onMouseButtonPressedEvent, this, _1), this);
	}

	Button::Button(const Button&) : Button()
	{
	}

	Button::~Button()
	{
		event::EventDispatcher<sf::Event::MouseMoved>::remove(this);
		event::EventDispatcher<sf::Event::MouseButtonPressed>::remove(this);
	}

	Button& Button::operator= (const Button& button)
	{
		if (this != &button)
		{
			using namespace std::placeholders;
			event::EventDispatcher<sf::Event::MouseMoved>::add(std::bind(&Button::onMouseEnteredEvent, this, _1), this);
			event::EventDispatcher<sf::Event::MouseMoved>::add(std::bind(&Button::onMouseLeftEvent, this, _1), this);
			event::EventDispatcher<sf::Event::MouseButtonPressed>::add(std::bind(&Button::onMouseButtonPressedEvent, this, _1), this);
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
		m_roundedRectangle.setSize(size);
		setAligment(m_stringAlign);
	}

	void Button::setCornersRadius(float radius)
	{
		m_roundedRectangle.setCornersRadius(radius);
	}

	void Button::setCornerPointCount(uint count)
	{
		m_roundedRectangle.setCornerPointCount(count);
	}

	void Button::setFillColor(const sf::Color& color)
	{
		m_roundedRectangle.setFillColor(color);
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		m_roundedRectangle.setPosition(position);
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
		return m_roundedRectangle.getSize();
	}

	const sf::Vector2f& Button::getPosition() const
	{
		return m_roundedRectangle.getPosition();
	}

	bool Button::isMouseOver(const sf::RenderWindow& window) const
	{
		auto mousePixelPos = sf::Mouse::getPosition(window);
		auto mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

		return m_roundedRectangle.getGlobalBounds().contains(mouseCoordPos.x, mouseCoordPos.y);
	}

	void Button::setVerticalAlignment(const alignment_t& vAlign)
	{
		// TODO: sometimes there correction needed for Y axis... fix rounded rectangle
		const auto& rectanglePosY = m_roundedRectangle.getPosition().y;
		const auto rectangleHeight = m_roundedRectangle.getLocalBounds().height - m_roundedRectangle.getCornersRadius();

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
		constexpr float correctionX = 1; // TODO: there is 1px off to the right... fix rounded rectangle
		const auto& rectanglePosX = m_roundedRectangle.getPosition().x - correctionX;
		const auto rectangleWidth = m_roundedRectangle.getLocalBounds().width;

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
			event::MouseButtonPressedEvent::onMouseButtonPressedEvent(event);
		}
	}

	void Button::onMouseEnteredEvent(const sf::Event& event)
	{
		if (isMouseOver() && !isActive())
		{
			setActive(true);
			event::MouseEnteredEvent::onMouseEnteredEvent(event);
		}
	}

	void Button::onMouseLeftEvent(const sf::Event& event)
	{
		if (!isMouseOver() && isActive())
		{
			setActive(false);
			event::MouseLeftEvent::onMouseLeftEvent(event);
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_roundedRectangle);
		target.draw(m_string);
	}

}}