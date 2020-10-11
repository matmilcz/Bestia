#pragma once

#include <SFML/Graphics/View.hpp>
#include "Gui/DrawableList.h"
#include "Gui/Button.h"
#include "Utils/CommonFcn.h"
#include "Utils/Log.h"
#include "EventSystem/System.h"
#include "Scene/Scene.h"

namespace bestia {

	class MainMenu : public event::EventCaller
	{
	public:
		MainMenu(EGameState& gameState);
		MainMenu(const MainMenu&) = delete;
		~MainMenu() = default;
		MainMenu& operator= (const MainMenu&) = delete;

		void prepareFrame();

	private:
		std::shared_ptr<gui::DrawableList<gui::Button>> m_mainSelectionList = std::make_shared<gui::DrawableList<gui::Button>>();
		sf::Font m_font;
		sf::View m_view = sf::View{ sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ gui::Window::getSize() } };
		scene::Scene m_scene;

		sf::Texture m_cloudTexture;

		EGameState& m_gameState;

		std::shared_ptr<scene::BackgroundLayer> prepareBackgroundLayer();
		std::shared_ptr<scene::GuiLayer> prepareGuiLayer();
		void prepareMainSelectionList();
	};

}
