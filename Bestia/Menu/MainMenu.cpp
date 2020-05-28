#include "MainMenu.h"

namespace bestia {

	MainMenu::MainMenu(sf::RenderWindow& window, EGameState& gameState)
		: m_window(window), m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		constexpr uint fontSize = 40;
		m_mainList.setFont(m_font);
		m_mainList.setColor(sf::Color::Black);
		m_mainList.setSize(fontSize);
		m_mainList.add("NEW GAME");
		m_mainList.add("OPTIONS");
		m_mainList.add("HOW TO PLAY");
		m_mainList.add("CREDITS");
		m_mainList.add("EXIT");
		m_mainList.setPosition(sf::Vector2f{ 0.f, -100.f });

		m_backgroundTexture.loadFromFile("Resources/textures/back_900x600.jpg");
		m_backgroundSprite.setTexture(m_backgroundTexture);
		m_backgroundSprite.setPosition(-500.f, -300.f);

		setEventDispatcher();
	}

	void MainMenu::loop()
	{
		m_window.setView(m_view);
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_mainList);
	}

	void MainMenu::setEventDispatcher()
	{
		using namespace sf;
		using namespace event;
		EventDispatcher<Event::MouseButtonPressed>::setDispatcher(std::bind(&MainMenu::handleMouseButtonPressedEvent, this));
		EventDispatcher<Event::MouseMoved>::setDispatcher(std::bind(&MainMenu::handleMouseMovedEvent, this));
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
				it_list.setStyle(sf::Text::Bold);
			}
			else
			{
				it_list.setStyle(sf::Text::Regular);
			}
		}
	}

}

