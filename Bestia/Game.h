#pragma once

#include "Utils/Log.h"
#include "Animation/Animation.h"
#include "Animation/AnimatedSprite.h"
#include "System/EventSystem/System.h"
#include "Scene/Scene.h"

namespace bestia {

	// TODO: it's just temporary implementation to keep Bestia.cpp cleaner
	class Game : public event::EventCaller
	{
	public:
		Game(EGameState& gameState, sf::Clock& frameClock)
			: m_gameState(gameState), m_beastTimer(500)
		{
			gui::Window::setView(m_view);

			sf::Texture beastTexture;
			beastTexture.loadFromFile("Resources/spritesheets/white_monster.png");
			std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

			m_beastAnimation = std::make_shared<animation::Animation>(std::move(beastTexture), std::move(frameRect));
			m_beastSprite = std::make_shared<animation::AnimatedSprite>(m_beastAnimation, m_beastTimer);

			m_beastSprite->setScale(sf::Vector2f(5.0f, 5.0f));

			event::system::connect<sf::Event::KeyPressed>([&](const sf::Event& event) {
				if (sf::Keyboard::Escape == event.key.code)
				{
					gameState = EGameState::InMenu;
				}
				}, this);

			m_beastSprite->start();
			m_beastTimer.start();

			auto background = std::make_shared<scene::BackgroundLayer>();
			background->objects.push_back(std::make_shared<sf::CircleShape>(100.f, 20));

			auto front = std::make_shared<scene::FrontLayer>();
			front->objects.push_back(m_beastSprite);

			m_scene.background = background;
			m_scene.front = front;
		}

		~Game()
		{
			event::system::disconnect<sf::Event::KeyPressed>(this);
			m_beastTimer.stop();
		}

		void prepareFrame()
		{
			gui::Window::setView(m_view);
			gui::Window::draw(m_scene);
		}

	private:
		sf::View m_view{ sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ gui::Window::getSize() } };

		event::timer::Timer m_beastTimer;
		std::shared_ptr<animation::Animation> m_beastAnimation;
		std::shared_ptr<animation::AnimatedSprite> m_beastSprite;

		scene::Scene m_scene;

		EGameState& m_gameState;
	};

}