#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bestia");
    window.setVerticalSyncEnabled(true);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    // TODO: would it be better if AnimatedSprite object was made only after entered inGame state?
    sf::Texture beastTexture;
    beastTexture.loadFromFile("../../../../Bestia/resources/spritesheets/white_monster.png"); // TODO: do sth with it

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    // TODO: make nice looking menu
    sf::Font font;
    font.loadFromFile("../../../../Bestia/resources/fonts/calibri.ttf"); // TODO: do sth with it
    
    sf::Text menuMainText;
    menuMainText.setString("MENU - click left mouse button see the beast");
    menuMainText.setFont(font);
    menuMainText.setFillColor(sf::Color::White);
    menuMainText.setCharacterSize(18);

    gameState = EGameState::inMenu;

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (gameState)
            {
            case EGameState::inMenu:
                handleInMenuEvents(event);
                break;
            case EGameState::inGame:
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
        case EGameState::inMenu:
            window.draw(menuMainText);
            break;
        case EGameState::inGame:
            window.draw(beast);
            break;
        }
        
        window.display();
    }

    return 0;
}