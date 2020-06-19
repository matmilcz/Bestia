#pragma once

#include "Utils/Log.h"
#include "AnimatedSprite.h"
#include "EventSystem/EventHandler.h"

namespace bestia {

	// TODO: it's just temporary implementation to keep Bestia.cpp cleaner
	class Game :
		public event::EventCaller
	{
	public:
		Game(EGameState& gameState, sf::Clock& frameClock)
			: m_gameState(gameState), m_frameClock(frameClock)
		{
			gui::Window::setView(view);

			beastTexture.loadFromFile("Resources/spritesheets/white_monster.png");

			beast.setScale(sf::Vector2f(5.0f, 5.0f));

			event::EventDispatcher<sf::Event::KeyPressed>::add([&](const sf::Event& event) {
				if (sf::Keyboard::Escape == event.key.code)
				{
					gameState = EGameState::InMenu;
				}
				}, this);
		}

		~Game()
		{
			event::EventDispatcher<sf::Event::KeyPressed>::remove(this);
		}

		void prepareFrame()
		{
			beast.update(m_frameClock.restart());
			gui::Window::setView(view);
			gui::Window::draw(beast);
		}

	private:
		sf::View view{ sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ gui::Window::getSize() } };
		sf::Texture beastTexture;
		const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };
		AnimatedSprite beast{ beastTexture, frameRect };

		EGameState& m_gameState;
		sf::Clock& m_frameClock;
	};

}