#pragma once

#include <SFML/Graphics/View.hpp>
#include "Gui/DrawableList.h"
#include "Gui/Button.h"
#include "Gui/Window.h"
#include "Utils/CommonFcn.h"
#include "Utils/Log.h"
#include "EventSystem/EventDispatcher.h"

namespace bestia {

	class MainMenu
	{
	public:
		MainMenu(EGameState& gameState);
		MainMenu(const MainMenu&) = delete;
		~MainMenu() = default;
		MainMenu& operator= (const MainMenu&) = delete;

		void prepareFrame();

	private:
		gui::DrawableList<gui::Button> m_mainList;

		EGameState& m_gameState;
		sf::View m_view = sf::View{ sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ gui::Window::getSize() } };

		sf::Font m_font;
	};

}
