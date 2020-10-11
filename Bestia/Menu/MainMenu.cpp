#include "MainMenu.h"
#include <utility>

namespace bestia {

	MainMenu::MainMenu(EGameState& gameState)
		: m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		prepareMainSelectionList();

		auto gui = std::make_shared<scene::GuiLayer>();
		gui->objects.push_back(m_mainSelectionList);

		m_scene.gui = gui;
	}

	void MainMenu::prepareFrame()
	{
		gui::Window::setView(m_view);
		gui::Window::draw(m_scene);
	}

	void MainMenu::prepareMainSelectionList()
	{
		gui::Button tempButton;
		constexpr uint length = 5;
		m_mainSelectionList->reserve(length);
		for (auto i = 0; i < length; ++i)
		{
			m_mainSelectionList->add(tempButton);
		}

		constexpr uint fontSize = 30;
		for (auto& it_list : *m_mainSelectionList)
		{
			it_list.setFont(m_font);
			it_list.setStringColor(sf::Color::Black);
			it_list.setCharacterSize(fontSize);
			it_list.setSize(sf::Vector2f{ 250.f, 70.f });
		}

		(*m_mainSelectionList)[0].setString("NEW GAME");
		(*m_mainSelectionList)[0].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[this](const sf::Event& event) { m_gameState = EGameState::InGame; };

		(*m_mainSelectionList)[1].setString("OPTIONS");

		(*m_mainSelectionList)[2].setString("HOW TO PLAY");

		(*m_mainSelectionList)[3].setString("CREDITS");
		(*m_mainSelectionList)[3].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[this](const sf::Event& event) {
			event::system::EventQueue<event::ViewMoveEvent>::push({});
			LOG("Credits: Mlody i Zosia\n" <<
				"Attrribution: \n" <<
				"Background photo created by freepik - www.freepik.com\n"); };

		(*m_mainSelectionList)[4].setString("EXIT");
		(*m_mainSelectionList)[4].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[](const sf::Event& event) { gui::Window::close(); };

		m_mainSelectionList->setPosition(sf::Vector2f{ -125.f, -200.f });
		m_mainSelectionList->setSpacing(sf::Vector2f{ 0.f, 80.f });
	}

}

