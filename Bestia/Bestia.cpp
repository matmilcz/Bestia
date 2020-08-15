#include <memory>
#include "Menu/MainMenu.h"
#include "Game.h"
#include "EventSystem/System.h"

int main(int argc, char* argv[])
{
    using namespace bestia;

    EGameState gameState = EGameState::InMenu;

    sf::Clock frameClock;

    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<Game> game;

    sf::Event event;
    while (gui::Window::isOpen())
    {
        while (gui::Window::pollEvent(event))
        {
            event::system::handleEvent(event);
        }

        gui::Window::clear();

        switch (gameState)
        {
        case EGameState::InMenu:
            if (game != nullptr)
            {
                game.reset();
            }

            if (mainMenu == nullptr)
            {
                mainMenu = std::make_unique<MainMenu>(gameState);
            }
            mainMenu->prepareFrame();
            break;
        case EGameState::InGame:
            if (mainMenu != nullptr)
            {
                mainMenu.reset();
            }

            if (game == nullptr)
            {
                game = std::make_unique<Game>(gameState, frameClock);
            }
            game->prepareFrame();
            break;
        }

        gui::Window::display();
    }

    return 0;
}