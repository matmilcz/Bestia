#include "Bestia.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::cout << "Here you can log things that will not appear in release mode:" << '\n';
#endif // _DEBUG

    sf::RenderWindow window(sf::VideoMode(defaultWindowWidth, defaultWindowHeight), "Bestia");

    sf::Texture beastTexture;
    beastTexture.loadFromFile("../../../../Bestia/resources/spritesheets/white_monster.png"); // TODO: do sth with it

    const std::vector <sf::IntRect> frameRect = { {0, 0, 50, 50}, {50, 0, 50, 50} };

    AnimatedSprite beast(beastTexture, frameRect);
    beast.setScale(sf::Vector2f(5.0f, 5.0f)); // TODO: it's a mess when resizing the window

    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        beast.update(frameClock.restart());

        window.clear();
        window.draw(beast);
        window.display();
    }

    return 0;
}