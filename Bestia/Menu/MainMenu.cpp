#include "MainMenu.h"
#include <utility>

namespace bestia {

	MainMenu::MainMenu(EGameState& gameState)
		: m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		gui::Button tempButton;
		constexpr uint length = 5;
		m_mainList.reserve(length);
		for (auto i = 0; i < length; ++i)
		{
			m_mainList.add(tempButton);
		}

		constexpr uint fontSize = 30;
		for (auto& it_list : m_mainList)
		{
			it_list.setFont(m_font);
			it_list.setStringColor(sf::Color::Black);
			it_list.setCharacterSize(fontSize);
			it_list.setSize(sf::Vector2f{ 250.f, 70.f });
		}

		m_mainList[0].setString("NEW GAME");
		m_mainList[0].setOnMouseButtonPressedEvent([this](const sf::Event& event) { m_gameState = EGameState::InGame; });

		m_mainList[1].setString("OPTIONS");

		m_mainList[2].setString("HOW TO PLAY");

		m_mainList[3].setString("CREDITS");
		m_mainList[3].setOnMouseButtonPressedEvent([](const sf::Event& event) {
			LOG("Credits: Mlody i Zosia\n" <<
				"Attrribution: \n" <<
				"Background photo created by freepik - www.freepik.com\n"); });

		m_mainList[4].setString("EXIT");
		m_mainList[4].setOnMouseButtonPressedEvent([](const sf::Event& event) { gui::Window::close(); });
		
		m_mainList.setPosition(sf::Vector2f{ -125.f, -200.f });
		m_mainList.setSpacing(sf::Vector2f{ 0.f, 80.f });
	}

	void MainMenu::prepareFrame()
	{
		gui::Window::setView(m_view);
		gui::Window::draw(m_mainList);
	}

}

