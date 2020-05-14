#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bestia");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    // TODO: would it be better if AnimatedSprite object was made only after entered InGame state?
    sf::Texture beastTexture;
    beastTexture.loadFromFile("../../../../Bestia/resources/spritesheets/white_monster.png"); // TODO: do sth with it

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    // TODO: make nice looking menu
    sf::Font font;
    font.loadFromFile("../../../../Bestia/resources/fonts/calibri.ttf"); // TODO: do sth with it
    
    Bestia::Menu mainMenu{ {"NEW GAME", font, 30},
                           {"CREDITS", font, 30},
                           {"EXIT", font, 30} };

    gameState = EGameState::InMenu;

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (gameState)
            {
            case EGameState::InMenu:
                handleInMenuEvents(mainMenu, event, window);
                break;
            case EGameState::InGame:
                handleInGameEvents(event);
                break;
            }

            handleCommonEvents(event, window, view);
        }

        beast.update(frameClock.restart());

        window.clear();
        window.setView(view);

        switch (gameState)
        {
        case EGameState::InMenu:
            window.draw(mainMenu);
            break;
        case EGameState::InGame:
            window.draw(beast);
            break;
        }
        
        window.display();
    }

    return 0;
}