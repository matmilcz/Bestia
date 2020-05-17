#include "MainMenu.h"

namespace bestia {

	MainMenu::MainMenu(sf::RenderWindow& window, EGameState& gameState)
		: m_window(window), m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		m_mainList.setFont(m_font);
		m_mainList.setColor(sf::Color::Black);
		m_mainList.add("NEW GAME");
		m_mainList.add("CREDITS");
		m_mainList.add("EXIT");

		m_backgroundTexture.loadFromFile("Resources/textures/back_900x600.jpg");
		m_backgroundSprite.setTexture(m_backgroundTexture);
		m_backgroundSprite.setPosition(-500.f, -300.f);
	}

	void MainMenu::loop()
	{
		sf::Event event;

		while (EGameState::InMenu == m_gameState && m_window.isOpen())
		{
			while (m_window.pollEvent(event))
			{
				handleEvent(event);
			}

			m_window.clear();
			m_window.setView(m_view);

			m_window.draw(m_backgroundSprite);
			m_window.draw(m_mainList);

			m_window.display();
		}
	}

	void MainMenu::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			handleMouseButtonPressedEvent();
			break;
		case sf::Event::MouseMoved:
			handleMouseMovedEvent();
			break;
		default:
			handleCommonEvent(event, m_window, m_view);
			break;
		}
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
#ifdef _DEBUG
					std::cout << "Credits: Mlody i Zosia\n"
							  << "Attrribution: \n"
							  << "Background photo created by freepik - www.freepik.com\n";
#endif // _DEBUG
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

