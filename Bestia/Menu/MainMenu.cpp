#include "MainMenu.h"
#include <utility>
#include <array>
#include "Animation/FadeEffect.h"
#include "Animation/MoveEffect.h"

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
		constexpr uint numOfClouds = 3;

		std::array<std::shared_ptr<sf::Sprite>, numOfClouds> cloudSprites =
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

		std::array<std::function<void(const event::MoveEffectFinishedEvent&)>, numOfClouds> cloudRoutines;

		cloudRoutines[0] = [=](const event::MoveEffectFinishedEvent& event) {
			std::cout << "cloudRoutine0 sender:" << event.sender << " sprite0: " << (sf::Transformable*)&*cloudSprites[0] << "\n";
			const auto object = event.sender;
			if (object == (sf::Transformable*)&*cloudSprites[0])
			{
				constexpr float bounds[] = { -400.f, 200.f };
				
				if (object->getPosition().x <= bounds[0])
				{
					animation::effect::move(object, sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ bounds[1], 150.f });
					std::cout << "dupa1 " << object << "\n";
				}
				else if (object->getPosition().x >= bounds[1])
				{
					animation::effect::move(object, sf::Vector2f{ -1.f, 0.f }, sf::Vector2f{ bounds[0], 150.f });
					std::cout << "dupa2 " << object << "\n";
				}
				else
				{
					std::cout << "dupa posx: " << object->getPosition().x << "\n";

				}
			}
			
		};

		cloudRoutines[1] = [=](const event::MoveEffectFinishedEvent& event) {
			std::cout << "cloudRoutine1 sender:" << event.sender << " sprite1:" << (sf::Transformable*)&*cloudSprites[1] << "\n";
			auto object = event.sender;
			if (object == (sf::Transformable*)&cloudSprites[1])
			{
				constexpr float bounds[] = { -900.f, 0.f };
				if (object->getPosition().x <= bounds[0])
					animation::effect::move(object, sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ bounds[1], -480.f });
				else if (object->getPosition().x >= bounds[1])
					animation::effect::move(object, sf::Vector2f{ -1.f, 0.f }, sf::Vector2f{ bounds[0], -480.f });
				else
					std::cout << "dupa\n";
			}
		};

		cloudRoutines[2] = [](const event::MoveEffectFinishedEvent& event) {
			constexpr float bounds[] = { -700.f, 0.f };
			auto object = event.sender;
			if (object->getPosition().x <= bounds[0])
				animation::effect::move(object, sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ bounds[1], -50.f });
			else if (object->getPosition().x >= bounds[1])
				animation::effect::move(object, sf::Vector2f{ -1.f, 0.f }, sf::Vector2f{ bounds[0], -50.f });
		};

		std::cout << "cloud0: " << (sf::Transformable*)&*cloudSprites[0] << '\n';
		std::cout << "cloud1: " << (sf::Transformable*)&*cloudSprites[1] << '\n';

		std::cout << "connecting MoveEffectFinishedEvent...\n";
		event::system::connect<event::MoveEffectFinishedEvent>(cloudRoutines[0], (sf::Transformable*) &*cloudSprites[0]);
		event::system::connect<event::MoveEffectFinishedEvent>(cloudRoutines[1], (sf::Transformable*) &*cloudSprites[1]);
		std::cout << "finished connecting\n";
		//event::system::connect<event::MoveEffectFinishedEvent>(cloudRoutines[2], &*cloudSprites[2]);
		animation::effect::move(&*cloudSprites[0], sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ 200.f, 150.f });
		animation::effect::move(&*cloudSprites[1], sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ 0.f, -480.f });
		//animation::effect::move(&*cloudSprites[2], sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ 0.f, -50.f });
		//event::system::EventQueue<event::MoveEffectFinishedEvent>::push({ &*cloudSprites[0] });

		//animation::effect::move(&*cloudSprites[0], sf::Vector2f{ 1.f, 0.f }, sf::Vector2f{ 200.f, 150.f }, []() { std::cout << "dupa\n"; });

		//event::system::connect<event::TimerTimeoutEvent>([this, cloudSprites](const event::TimerTimeoutEvent& e) {
		//	if (e.sender == &event::timer::Timer::getTimer10ms())
		//	{
		//		static int dir[3] = { -1, -1, 1 };
		//		sf::Vector2f bounds[3] = { {200.f, -400.f}, {0.f, -900.f}, {0.f, -700.f} }; // this implementation force A > B for { A, B }

		//		for (unsigned i = 0; i < 3; ++i)
		//		{
		//			if (cloudSprites[i]->getPosition().x > bounds[i].x || cloudSprites[i]->getPosition().x < bounds[i].y)
		//			{
		//				dir[i] *= -1;
		//			}

		//			cloudSprites[i]->move(sf::Vector2f{ dir[i] * 0.5f, 0 });
		//		}
		//	}
		//	}, this);

		return background;
	}

	std::shared_ptr<scene::GuiLayer> MainMenu::prepareGuiLayer()
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");
		prepareMainSelectionList();

		auto credits = std::make_shared<sf::Text>();
		credits->setFont(m_font);
		credits->setPosition({ 0.f, -1000.f });
		credits->setString(
			"Credits: \n"
			"Mlody i Zosia\n\n"
			"Attrribution: \n"
			"https://www.gamedeveloperstudio.com\n");
		credits->setCharacterSize(24);

		auto gui = std::make_shared<scene::GuiLayer>();
		gui->objects.push_back(m_mainSelectionList);
		gui->objects.push_back(credits);

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
		(*m_mainSelectionList)[1].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[this](const sf::Event& event) {
			(*m_mainSelectionList)[1].setFillColor(sf::Color{ 10, 20, 180, 0 });
			(*m_mainSelectionList)[1].setStringColor(sf::Color{ 190, 190, 190, 0 });
			animation::effect::fadeIn(&(*m_mainSelectionList)[1], 10, 180);
		};

		(*m_mainSelectionList)[2].setString("HOW TO PLAY");
		(*m_mainSelectionList)[2].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[this](const sf::Event& event) {
			animation::effect::fadeOut(&(*m_mainSelectionList)[2], 5, 100);
		};

		(*m_mainSelectionList)[3].setString("CREDITS");
		(*m_mainSelectionList)[3].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[this](const sf::Event& event) { moveView({ 0.f, -500.f }, m_view, &(*m_mainSelectionList)[3]); };

		(*m_mainSelectionList)[4].setString("EXIT");
		(*m_mainSelectionList)[4].EventCallSFML<sf::Event::MouseButtonPressed>::eventHandler =
			[](const sf::Event& event) { gui::Window::close(); };

		m_mainSelectionList->setPosition(sf::Vector2f{ -125.f, -200.f });
		m_mainSelectionList->setSpacing(sf::Vector2f{ 0.f, 80.f });
	}

}

