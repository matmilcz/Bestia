#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

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

    while (window.isOpen())
    {
        switch (gameState)
        {
        case bestia::EGameState::InMenu:
            {
                std::unique_ptr <bestia::MainMenu> mainMenu{ new bestia::MainMenu(window, gameState) };
                mainMenu->loop();
            }
            break;
        case bestia::EGameState::InGame: // TODO: make a class to handle this state
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (sf::Event::KeyPressed == event.type && sf::Keyboard::Escape == event.key.code)
                {
                    gameState = bestia::EGameState::InMenu;
                }
                bestia::handleCommonEvent(event, window, view);
            }
            beast.update(frameClock.restart());

            window.clear();
            window.setView(view);
            window.draw(beast);
            window.display();
            break;
        }
    }

    return 0;
}