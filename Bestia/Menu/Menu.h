#pragma once

#include <vector>
#include <initializer_list>
#include <SFML/Graphics/Drawable.hpp>
#include "MenuOption.h"
#include "../EGameState.h"

extern EGameState gameState; // TODO: try to avoid global variables

namespace Bestia {

	class Menu : public sf::Drawable
	{
	public:
		Menu(std::initializer_list <MenuOption> menu) : m_menu(menu)
		{
			sf::Vector2f pos{ 0, 0 };
			const auto posStep = m_menu[0].getCharacterSize() + 20;

			for (auto& menu_it : m_menu)
			{
				menu_it.setPosition(pos);
				pos.y += posStep;
			}
		}

		~Menu()
		{
		}

		void handleMouseEvents(const sf::Event& event, const sf::RenderWindow& window)
		{
			for (auto& menu_it : m_menu)
			{
				if (menu_it.isMouseOver(window))
				{
					menu_it.setStyle(sf::Text::Bold);
					if (sf::Event::MouseButtonPressed == event.type && menu_it.getString() == "NEW GAME") // TODO: add menuClicked fcn
					{
						gameState = EGameState::InGame;
					}
					else if (sf::Event::MouseButtonPressed == event.type && menu_it.getString() == "CREDITS")
					{
#ifdef _DEBUG
						std::cout << "Credits: Mlody i Zosia\n";
#endif // _DEBUG

					}
				}
				else
				{
					menu_it.setStyle(sf::Text::Regular);
				}
			}
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (const auto& menu_it : m_menu)
			{
				target.draw(menu_it, states);
			}
		}

	private:
		std::vector <MenuOption> m_menu;
	};

}