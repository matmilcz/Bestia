# pragma once

#include <SFML/Graphics.hpp>
#include "Defs.h"

namespace Bestia {

    inline void resizeView(const sf::Window& window, sf::View& view)
    {
        const float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
        view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
    }

    inline void handleCommonEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& view)
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

}
