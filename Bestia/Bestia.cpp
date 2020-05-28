#include <SFML/Graphics.hpp>
#include <memory>
#include "Utils/Log.h"
#include "AnimatedSprite.h"
#include "Menu/MainMenu.h"
#include "Utils/CommonFcn.h"
#include "EventSystem/EventHandler.h"

int main(int argc, char* argv[])
{
    LOG("Here you can log things that will not appear in release mode:" << '\n');

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

#ifdef _DEBUG
    sf::RenderWindow window(desktopMode, "Bestia"); // TODO: change hardcoded view size
#else
    sf::RenderWindow window(desktopMode, "Bestia", sf::Style::Fullscreen);
#endif // _DEBUG

    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(bestia::VIEW_WIDTH, bestia::VIEW_HEIGHT));

    // TODO: would it be better if AnimatedSprite object was made only after entered InGame state?
    sf::Texture beastTexture;
    beastTexture.loadFromFile("Resources/spritesheets/white_monster.png");

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    bestia::EGameState gameState = bestia::EGameState::InMenu;

    sf::Clock frameClock;

    std::unique_ptr <bestia::MainMenu> mainMenu;

    sf::Event event;
    bestia::event::EventDispatcher<sf::Event::Closed>::setDispatcher([&window]() {
        window.close(); 
        });
    bestia::event::EventDispatcher<sf::Event::Resized>::setDispatcher([&window, &view]() {
        bestia::resizeView(window, view);
        view.setCenter(0.0f, 0.0f);
        });

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            bestia::event::handleEvent(event);
        }

        window.clear();

        switch (gameState)
        {
        case bestia::EGameState::InMenu:
            if (mainMenu == nullptr)
            {
                mainMenu = std::make_unique <bestia::MainMenu> (window, gameState);
            }
            mainMenu->loop();
            break;
        case bestia::EGameState::InGame: // TODO: make a class to handle this state
            mainMenu.reset();

            bestia::event::EventDispatcher<sf::Event::MouseButtonPressed>::setDispatcher([]() { LOG("Pressed\n"); });
            bestia::event::EventDispatcher<sf::Event::MouseMoved>::setDispatcher([]() { LOG("Moved\n"); });
            bestia::event::EventDispatcher<sf::Event::KeyPressed>::setDispatcher([&]() { 
                if (sf::Keyboard::Escape == event.key.code)
                {
                    gameState = bestia::EGameState::InMenu;
                }
                });

            beast.update(frameClock.restart());
            window.setView(view);
            window.draw(beast);
            break;
        }

        window.display();
    }

    return 0;
}