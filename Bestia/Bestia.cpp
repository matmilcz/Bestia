#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

    sf::RenderWindow window(sf::VideoMode(Bestia::WINDOW_WIDTH, Bestia::WINDOW_HEIGHT), "Bestia");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(Bestia::VIEW_WIDTH, Bestia::VIEW_HEIGHT));

    // TODO: would it be better if AnimatedSprite object was made only after entered InGame state?
    sf::Texture beastTexture;
    beastTexture.loadFromFile("../../../../Bestia/resources/spritesheets/white_monster.png"); // TODO: do sth with it

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    sf::Font font;
    font.loadFromFile("../../../../Bestia/resources/fonts/calibri.ttf"); // TODO: do sth with it

    Bestia::EGameState gameState = Bestia::EGameState::InMenu;

    sf::Clock frameClock;

    while (window.isOpen())
    {
        switch (gameState)
        {
        case Bestia::EGameState::InMenu:
            {
                std::unique_ptr <Bestia::MainMenu> mainMenu{ new Bestia::MainMenu(window, gameState, font) };
                mainMenu->loop();
            }
            break;
        case Bestia::EGameState::InGame: // TODO: make a class to handle this state
            sf::Event event;

            while (window.pollEvent(event))
            {
                Bestia::handleCommonEvent(event, window, view);
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