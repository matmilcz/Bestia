#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bestia");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    sf::Texture beastTexture;
    beastTexture.loadFromFile("../../../../Bestia/resources/spritesheets/white_monster.png"); // TODO: do sth with it

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f));

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                view.setCenter(0.0f, 0.0f);
                break;
            }
        }

        beast.update(frameClock.restart());

        window.clear();
        window.setView(view);
        window.draw(beast);
        window.display();
    }

    return 0;
}