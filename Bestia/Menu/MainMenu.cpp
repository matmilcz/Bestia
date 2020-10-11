#include "MainMenu.h"
#include <utility>

extern bestia::event::timer::Timer g_timer60tpc;

namespace bestia {

	MainMenu::MainMenu(EGameState& gameState) : m_gameState(gameState)
	{
		auto background = prepareBackgroundLayer();
		auto gui = prepareGuiLayer();

		m_scene.background = background;
		m_scene.gui = gui;
	}

	void MainMenu::prepareFrame()
	{
		gui::Window::setView(m_view);
		gui::Window::draw(m_scene);
	}

	std::shared_ptr<scene::BackgroundLayer> MainMenu::prepareBackgroundLayer()
	{
		m_cloudTexture.loadFromFile("Resources/spritesheets/clouds.png");

		std::shared_ptr<sf::Sprite> cloudSprites[3] =
		{
			std::make_shared<sf::Sprite>(m_cloudTexture, sf::IntRect{ 0, 0, 580, 280 }),
			std::make_shared<sf::Sprite>(m_cloudTexture, sf::IntRect{ 0, 300, 800, 330 }),
			std::make_shared<sf::Sprite>(m_cloudTexture, sf::IntRect{ 0, 630, 590, 325 })
		};

		cloudSprites[0]->move(sf::Vector2f{ 100.f, 150.f });
		cloudSprites[1]->move(sf::Vector2f{ -800.f, -480.f });
		cloudSprites[2]->move(sf::Vector2f{ -600.f, -50.f });

		auto background = std::make_shared<scene::BackgroundLayer>();
		background->objects.push_back(cloudSprites[2]);
		background->objects.push_back(cloudSprites[1]);
		background->objects.push_back(cloudSprites[0]);

		event::system::connect<event::TimerTimeoutEvent>([this, cloudSprites](const event::TimerTimeoutEvent& e) {
			if (e.sender == &g_timer60tpc)
			{
				static int dir[3] = { -1, -1, 1 };
				sf::Vector2f bounds[3] = { {200.f, -400.f}, {0.f, -900.f}, {0.f, -700.f} }; // this implementation force A > B for { A, B }

				for (unsigned i = 0; i < 3; ++i)
				{
					if (cloudSprites[i]->getPosition().x > bounds[i].x || cloudSprites[i]->getPosition().x < bounds[i].y)
					{
						dir[i] *= -1;
					}

					cloudSprites[i]->move(sf::Vector2f{ dir[i] * 0.5f, 0 });
				}
			}
			}, this);

		return background;
	}

	std::shared_ptr<scene::GuiLayer> MainMenu::prepareGuiLayer()
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");
		prepareMainSelectionList();

		auto gui = std::make_shared<scene::GuiLayer>();
		gui->objects.push_back(m_mainSelectionList);

		return gui;
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
			it_list.setDefaultColor(sf::Color{ 10, 20, 180, 180 });
			it_list.setMouseOverColor(sf::Color{ 10, 20, 70, 180 });
			it_list.setStringColor(sf::Color{ 190, 190, 190, 240 });
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

