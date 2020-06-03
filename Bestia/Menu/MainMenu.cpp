#include "MainMenu.h"

namespace bestia {

	MainMenu::MainMenu(sf::RenderWindow& window, EGameState& gameState)
		: m_window(window), m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		gui::Button tempButton;
		constexpr uint length = 5;
		constexpr uint fontSize = 30;
		for (auto i = 0; i < length; ++i)
		{
			m_mainList.add(tempButton);
			m_mainList[i].setFont(m_font);
			m_mainList[i].setStringColor(sf::Color::Black);
			m_mainList[i].setCharacterSize(fontSize);
			m_mainList[i].setSize(sf::Vector2f{ 250.f, 70.f });
		}

		m_mainList[0].setString("NEW GAME");
		m_mainList[1].setString("OPTIONS");
		m_mainList[2].setString("HOW TO PLAY");
		m_mainList[3].setString("CREDITS");
		m_mainList[4].setString("EXIT");
		
		m_mainList.setPosition(sf::Vector2f{ -125.f, -200.f });
		m_mainList.setSpacing(sf::Vector2f{ 0.f, 80.f });

		setEventDispatcher();
	}

	void MainMenu::prepareFrame()
	{
		m_window.setView(m_view);
		m_window.draw(m_mainList);
	}

	void MainMenu::setEventDispatcher()
	{
		using namespace event;
		EventDispatcher<sf::Event::MouseButtonPressed>::setDispatcher(std::bind(&MainMenu::handleMouseButtonPressedEvent, this));
		EventDispatcher<sf::Event::MouseMoved>::setDispatcher(std::bind(&MainMenu::handleMouseMovedEvent, this));
	}

	void MainMenu::handleMouseButtonPressedEvent()
	{
		for (auto& it_list : m_mainList)
		{
			if (it_list.isMouseOver(m_window))
			{
				if ("NEW GAME" == it_list.getString())
				{
					m_gameState = EGameState::InGame;
				}
				else if ("CREDITS" == it_list.getString())
				{
					LOG("Credits: Mlody i Zosia\n" <<
						"Attrribution: \n" <<
						"Background photo created by freepik - www.freepik.com\n");
				}
				else if ("EXIT" == it_list.getString())
				{
					m_window.close(); // TODO: in future probably would need some cleanup
				}
			}
		}
	}

	void MainMenu::handleMouseMovedEvent()
	{
		for (auto& it_list : m_mainList)
		{
			if (it_list.isMouseOver(m_window))
			{
				it_list.setFillColor(sf::Color::Blue);
				it_list.setStringColor(sf::Color::White);
			}
			else
			{
				it_list.setFillColor(sf::Color::White);
				it_list.setStringColor(sf::Color::Black);
			}
		}
	}

}

