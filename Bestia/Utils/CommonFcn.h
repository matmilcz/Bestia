# pragma once

#include <SFML/Graphics.hpp>
#include "Defs.h"

namespace bestia {

    inline void resizeView(const sf::Window& window, sf::View& view)
    {
        const float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
        view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
    }

}
