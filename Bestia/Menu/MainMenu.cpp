#include "MainMenu.h"

namespace bestia {

	MainMenu::MainMenu(EGameState& gameState)
		: m_gameState(gameState)
	{
		m_font.loadFromFile("Resources/fonts/calibri.ttf");

		gui::Button tempButton;
		constexpr uint length = 5;
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
			it_list.setOnMouseOverEvent([&it_list]() {
				it_list.setFillColor(sf::Color::Blue);
				it_list.setStringColor(sf::Color::White);
				});
		}

		m_mainList[0].setString("NEW GAME");
		m_mainList[0].setOnClickEvent([this]() { m_gameState = EGameState::InGame; });

		m_mainList[1].setString("OPTIONS");

		m_mainList[2].setString("HOW TO PLAY");

		m_mainList[3].setString("CREDITS");
		m_mainList[3].setOnClickEvent([]() {
			LOG("Credits: Mlody i Zosia\n" <<
				"Attrribution: \n" <<
				"Background photo created by freepik - www.freepik.com\n"); });

		m_mainList[4].setString("EXIT");
		m_mainList[4].setOnClickEvent([]() { gui::Window::close(); });
		
		m_mainList.setPosition(sf::Vector2f{ -125.f, -200.f });
		m_mainList.setSpacing(sf::Vector2f{ 0.f, 80.f });

		setEventDispatcher();
	}

	void MainMenu::prepareFrame()
	{
		gui::Window::setView(m_view);
		gui::Window::draw(m_mainList);
	}

	void MainMenu::setEventDispatcher()
	{
		using namespace std::placeholders;
		event::EventDispatcher<sf::Event::MouseButtonPressed>::setDispatcher(std::bind(&MainMenu::handleMouseButtonPressedEvent, this, _1));
		event::EventDispatcher<sf::Event::MouseMoved>::setDispatcher(std::bind(&MainMenu::handleMouseMovedEvent, this, _1));
		event::EventDispatcher<sf::Event::KeyPressed>::setDispatcher(std::bind(&MainMenu::handleKeyPressedEvent, this, _1));
	}

	void MainMenu::handleMouseButtonPressedEvent(const sf::Event& event)
	{
		for (auto& it_list : m_mainList)
		{
			if (it_list.isMouseOver(gui::Window::getRenderWindow()))
			{
				it_list.onClickEvent();
			}
		}
	}

	void MainMenu::handleMouseMovedEvent(const sf::Event& event)
	{
		for (auto& it_list : m_mainList)
		{
			if (it_list.isMouseOver(gui::Window::getRenderWindow()))
			{
				it_list.onMouseOverEvent();
			}
			else
			{
				it_list.setFillColor(sf::Color::White);
				it_list.setStringColor(sf::Color::Black);
			}
		}
	}

	void MainMenu::handleKeyPressedEvent(const sf::Event& event)
	{
		if (sf::Keyboard::Escape == event.key.code)
		{
			gui::Window::close();
		}
	}

}

