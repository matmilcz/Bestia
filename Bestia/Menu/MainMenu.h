#pragma once

#include <SFML/Graphics/View.hpp>
#include "DrawableList.h"
#include "../Utils/CommonFcn.h"

namespace Bestia {

	class MainMenu
	{
	public:
		MainMenu(sf::RenderWindow& window, EGameState& gameState, const sf::Font& font);
		MainMenu(const MainMenu&) = delete;
		~MainMenu() = default;
		MainMenu& operator= (const MainMenu&) = delete;

		void loop();

	private:
		DrawableList m_mainList;

		sf::RenderWindow& m_window;
		EGameState& m_gameState;
		sf::View m_view{ sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) };

		void handleEvent(const sf::Event& event);
		void handleMouseButtonPressedEvent();
		void handleMouseMovedEvent();
	};

}
