#pragma once

#include <SFML/Graphics/View.hpp>
#include "Gui/DrawableList.h"
#include "Gui/Button.h"
#include "Utils/CommonFcn.h"
#include "Utils/Log.h"
#include "EventSystem/EventDispatcher.h"

namespace bestia {

	class MainMenu
	{
	public:
		MainMenu(sf::RenderWindow& window, EGameState& gameState);
		MainMenu(const MainMenu&) = delete;
		~MainMenu() = default;
		MainMenu& operator= (const MainMenu&) = delete;

		void loop();
		void setEventDispatcher();

	private:
		gui::DrawableList<gui::Button> m_mainList;

		sf::RenderWindow& m_window;
		EGameState& m_gameState;
		sf::View m_view = sf::View{ sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_window.getSize()) };

		sf::Font m_font;

		void handleMouseButtonPressedEvent();
		void handleMouseMovedEvent();
	};

}
