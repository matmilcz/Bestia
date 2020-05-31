#pragma once

#include <vector>
#include <utility>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace bestia {
namespace gui {

	using uint = unsigned int;

	template <typename TDrawableItem>
	class DrawableList : public sf::Drawable
	{
	public:
		DrawableList() = default;
		DrawableList(const DrawableList<TDrawableItem>&) = default;
		~DrawableList() = default;
		DrawableList<TDrawableItem>& operator= (const DrawableList<TDrawableItem>&) = default;

		TDrawableItem& operator[] (uint idx);

		void setPosition(const sf::Vector2f& position);
		void setSpacing(const sf::Vector2f& spacing);

		void resetSpacing();
		void add(const TDrawableItem& drawableItem);
		void add(TDrawableItem&& drawableItem);

	private:
		std::vector <TDrawableItem> m_list;
		sf::Vector2f m_spacing = { 0, 0 };

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	template<typename TDrawableItem>
	TDrawableItem& DrawableList<TDrawableItem>::operator[] (uint idx)
	{
		return m_list[idx];
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::setPosition(const sf::Vector2f& position)
	{
		m_list[0].setPosition(position);
		resetSpacing();
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::setSpacing(const sf::Vector2f& spacing)
	{
		m_spacing = spacing;
		resetSpacing();
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::resetSpacing()
	{
		for (auto it_list = m_list.begin() + 1; it_list != m_list.end(); ++it_list)
		{
			it_list->setPosition((it_list - 1)->getPosition() + m_spacing);
		}
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::add(const TDrawableItem& drawableItem)
	{
		m_list.emplace_back(drawableItem);
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::add(TDrawableItem&& drawableItem)
	{
		m_list.emplace_back(std::move(drawableItem));
	}

	template<typename TDrawableItem>
	void DrawableList<TDrawableItem>::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& it_list : m_list)
		{
			target.draw(it_list, states);
		}
	}

}}
