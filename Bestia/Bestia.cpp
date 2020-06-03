#include <memory>
#include "Utils/Log.h"
#include "AnimatedSprite.h"
#include "Menu/MainMenu.h"
#include "Utils/CommonFcn.h"
#include "EventSystem/EventHandler.h"

int main(int argc, char* argv[])
{
    using namespace bestia;

    LOG("Here you can log things that will not appear in release mode:" << '\n');

    sf::View view(sf::Vector2f{0.0f, 0.0f}, sf::Vector2f{ gui::Window::getSize() });
    gui::Window::setView(view);

    // TODO: would it be better if AnimatedSprite object was made only after entered InGame state?
    sf::Texture beastTexture;
    beastTexture.loadFromFile("Resources/spritesheets/white_monster.png");

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    EGameState gameState = EGameState::InMenu;

    sf::Clock frameClock;

    std::unique_ptr <MainMenu> mainMenu;

    sf::Event event;
    event::EventDispatcher<sf::Event::Closed>::setDispatcher([](const sf::Event& event) {
        gui::Window::close();
        });

    while (gui::Window::isOpen())
    {
        while (gui::Window::pollEvent(event))
        {
            event::handleEvent(event);
        }

        gui::Window::clear();

        switch (gameState)
        {
        case EGameState::InMenu:
            if (mainMenu == nullptr)
            {
                mainMenu = std::make_unique <MainMenu> (gameState);
            }
            mainMenu->prepareFrame();
            break;
        case EGameState::InGame: // TODO: make a class to handle this state
            mainMenu.reset();

            event::EventDispatcher<sf::Event::MouseButtonPressed>::setDispatcher([](const sf::Event& event) { LOG("Pressed\n"); });
            event::EventDispatcher<sf::Event::MouseMoved>::setDispatcher([](const sf::Event& event) { LOG("Moved\n"); });
            event::EventDispatcher<sf::Event::KeyPressed>::setDispatcher([&](const sf::Event& event) {
                if (sf::Keyboard::Escape == event.key.code)
                {
                    gameState = EGameState::InMenu;
                }
                });

            beast.update(frameClock.restart());
            gui::Window::setView(view);
            gui::Window::draw(beast);
            break;
        }

        gui::Window::display();
    }

    return 0;
}