#include <memory>
#include "Menu/MainMenu.h"
#include "Game.h"
#include "System/EventSystem/Timer.h"
#include "System/Time.h"
#include "System/GameManager.h"

int main(int argc, char* argv[])
{
    using namespace bestia;

    auto& gameManager = system::GameManager::getInstance();

    //EGameState gameState = EGameState::InMenu;

    sf::Clock frameClock;
    auto t = bestia::time::restart();
    event::timer::Timer::getTimer10ms().start();

    /*std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<Game> game;*/

    while (gui::Window::isOpen())
    {
        bestia::time::restart();
        event::system::handleEvents();

        gui::Window::clear(sf::Color(40, 150, 210, 255));

        gameManager.update();

        /*switch (gameState)
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
        }*/

        gui::Window::display();
    }

    return 0;
}