#pragma once

#include <SFML/Graphics/View.hpp>
#include "DrawableList.h"
#include "../Utils/CommonFcn.h"

namespace Bestia {

	class MainMenu
	{
	public:
		MainMenu(sf::RenderWindow& window, EGameState& gameState, const sf::Font& font)
			: m_window(window), m_gameState(gameState)
		{
			m_mainList.add({ "NEW GAME", font, 30 });
			m_mainList.add({ "CREDITS", font, 30 });
			m_mainList.add({ "EXIT", font, 30 });
		}

		~MainMenu() {}

		void loop()
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

				m_window.draw(m_mainList);

				m_window.display();
			}
		}

	private:
		DrawableList m_mainList;

		sf::RenderWindow& m_window;
		EGameState& m_gameState;
		sf::View m_view{ sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT) };

		void handleEvent(const sf::Event& event)
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

		void handleMouseButtonPressedEvent()
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
						std::cout << "Credits: Mlody i Zosia" << '\n';
#endif // _DEBUG
					}
					else if ("EXIT" == it_list.getString())
					{
						m_window.close(); // TODO: in future probably would need some cleanup
					}
				}
				
			}
		}

		void handleMouseMovedEvent()
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
	};

}
