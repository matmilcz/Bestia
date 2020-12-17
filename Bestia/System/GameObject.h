#pragma once

#include <vector>
#include <algorithm>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Gui/Window.h"

namespace bestia {
namespace system {

	class IGameObject
	{
	public:
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void fixedUpdate() = 0;
	};

	class GameObject : 
		public IGameObject,
		public sf::Drawable,
		public sf::Transformable
	{
	public:
		GameObject();
		virtual ~GameObject();

		static const std::vector<IGameObject*>& getGameObjects();

		virtual void start() override {}
		virtual void update() override {}
		virtual void fixedUpdate() override {}

	private:
		static std::vector<IGameObject*> m_gameObjects;
		static uint32_t m_numOfGameObjects;

		void registerGameObject();
		void deregisterGameObject();
	};

	class TestGameObject : public GameObject
	{
	public:
		virtual void update() override
		{
			if (isMouseOver())
			{
				m_circle.setFillColor(sf::Color::Green);
			}
			else
			{
				m_circle.setFillColor(sf::Color::Cyan);
			}
		}

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			gui::Window::draw(m_circle);
		}

		bool isMouseOver(const sf::RenderWindow& window = gui::Window::getRenderWindow()) const
		{
			auto mousePixelPos = sf::Mouse::getPosition(window);
			auto mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

			return m_circle.getGlobalBounds().contains(mouseCoordPos.x, mouseCoordPos.y);
		}

		sf::CircleShape m_circle{ 30, 30 };
	};
}
}