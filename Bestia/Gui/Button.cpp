#include "Button.h"

namespace bestia {
namespace gui {

	void Button::setString(const sf::String& string)
	{
		m_string.setString(string);
		setAligment(m_vAlign, m_hAlign);
	}

	void Button::setFont(const sf::Font& font)
	{
		m_string.setFont(font);
		setAligment(m_vAlign, m_hAlign);
	}

	void Button::setCharacterSize(uint size)
	{
		m_string.setCharacterSize(size);
		setAligment(m_vAlign, m_hAlign);
	}

	void Button::setStringColor(const sf::Color& color)
	{
		m_string.setFillColor(color);
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		m_roundedRectangle.setSize(size);
		setAligment(m_vAlign, m_hAlign);
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
		setAligment(m_vAlign, m_hAlign);
	}

	void Button::setAligment(const EVerticalAlignment& vAlign, const EHorizontalAlignment& hAlign)
	{
		setVerticalAlignment(vAlign);
		setHorizontalAlignment(hAlign);
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

	void Button::setVerticalAlignment(const EVerticalAlignment& vAlign)
	{
		// TODO: sometimes there correction needed for Y axis... fix rounded rectangle
		const auto& rectanglePosY = m_roundedRectangle.getPosition().y;
		const auto rectangleHeight = m_roundedRectangle.getLocalBounds().height - m_roundedRectangle.getCornersRadius();

		const auto& stringPosX = m_string.getPosition().x;

		switch (vAlign)
		{
		case EVerticalAlignment::Top:
			m_string.setPosition(sf::Vector2f{ stringPosX, rectanglePosY });
			break;
		case EVerticalAlignment::Center:
		{
			const auto moveY = (rectangleHeight - m_string.getCharacterSize()) / 2;
			const auto stringPosY = rectanglePosY + moveY;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		case EVerticalAlignment::Bottom:
		{
			const auto moveY = rectangleHeight - m_string.getCharacterSize();
			const auto stringPosY = rectanglePosY + moveY;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		}
	}

	void Button::setHorizontalAlignment(const EHorizontalAlignment& hAlign)
	{
		constexpr float correctionX = 1; // TODO: there is 1px off to the right... fix rounded rectangle
		const auto& rectanglePosX = m_roundedRectangle.getPosition().x - correctionX;
		const auto rectangleWidth = m_roundedRectangle.getLocalBounds().width;

		const auto& stringPosY = m_string.getPosition().y;

		switch (hAlign)
		{
		case EHorizontalAlignment::Left:
			m_string.setPosition(sf::Vector2f{ rectanglePosX, stringPosY });
			break;
		case EHorizontalAlignment::Center:
		{
			const auto moveX = (rectangleWidth - m_string.getLocalBounds().width) / 2;
			const auto stringPosX = rectanglePosX + moveX;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		case EHorizontalAlignment::Right:
		{
			const auto moveX = rectangleWidth - m_string.getLocalBounds().width;
			const auto stringPosX = rectanglePosX + moveX;
			m_string.setPosition(sf::Vector2f{ stringPosX, stringPosY });
			break;
		}
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_roundedRectangle);
		target.draw(m_string);
	}

}}