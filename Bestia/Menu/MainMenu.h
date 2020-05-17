#pragma once

#include <SFML/Graphics/View.hpp>
#include "Utils/DrawableList.h"
#include "Utils/CommonFcn.h"

namespace bestia {

	class MainMenu
	{
	public:
		MainMenu(sf::RenderWindow& window, EGameState& gameState);
		MainMenu(const MainMenu&) = delete;
		~MainMenu() = default;
		MainMenu& operator= (const MainMenu&) = delete;

		void loop();

	private:
		DrawableList m_mainList;

		sf::RenderWindow& m_window;
		EGameState& m_gameState;
		sf::View m_view{ sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) };

		sf::Font m_font;
		sf::Texture m_backgroundTexture;
		sf::Sprite m_backgroundSprite;

		void handleEvent(const sf::Event& event);
		void handleMouseButtonPressedEvent();
		void handleMouseMovedEvent();
	};

}
