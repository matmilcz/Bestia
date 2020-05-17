#include "DrawableList.h"

namespace bestia {

	DrawableList::DrawableList(std::initializer_list<Text> list) : m_list(list)
	{
		setInterline(m_interline);
	}

	Text& DrawableList::operator[] (const int idx)
	{
		return m_list[idx];
	}

	void DrawableList::add(const Text& text)
	{
		if (m_list.empty())
		{
			m_list.push_back(text);
		}
		else
		{
			m_list.push_back(text);
			
			setPosition(m_list.front().getPosition()); // TODO: no need to update whole list
		}
	}

	void DrawableList::add(const sf::String& string)
	{
		add({ string, m_font, m_size });
		m_list.back().setColor(m_color);
	}

	void DrawableList::setColor(const sf::Color& color)
	{
		m_color = color;

		for (auto& it_list : m_list)
		{
			it_list.setColor(m_color);
		}
	}

	void DrawableList::setFont(const sf::Font& font)
	{
		m_font = font;

		for (auto& it_list : m_list)
		{
			it_list.setFont(m_font);
		}
	}

	void DrawableList::setSize(const uint& size)
	{
		m_size = size;

		for (auto& it_list : m_list)
		{
			it_list.setCharacterSize(m_size);
		}
	}

	void DrawableList::setInterline(const uint& interline)
	{
		m_interline = interline;

		if (!m_list.empty())
		{
			setPosition(m_list[0].getPosition());
		}
	}

	void DrawableList::setPosition(const sf::Vector2f& desiredPos)
	{
		sf::Vector2f pos = desiredPos;

		for (auto& it_list : m_list)
		{
			it_list.setPosition(pos);
			pos.y += it_list.getCharacterSize() + m_interline;
		}
	}

	std::vector<Text>::iterator DrawableList::begin()
	{
		return m_list.begin();
	}

	std::vector<Text>::iterator DrawableList::end()
	{
		return m_list.end();
	}

	void DrawableList::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& it_list : m_list)
		{
			target.draw(it_list, states);
		}
	}

}