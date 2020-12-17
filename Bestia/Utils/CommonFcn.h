# pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "System/EventSystem/EventCaller.h"
#include <SFML/Graphics/Shape.hpp>
#include "Gui/Window.h"

namespace bestia {

    void resizeView(const sf::Window& window, sf::View& view);
    void moveView(const sf::Vector2f& newCenter, sf::View& view, const event::EventCaller* caller);

    bool isMouseOver(const sf::Shape& shape, const sf::RenderWindow& window = gui::Window::getRenderWindow());
    bool isMouseOver(const sf::Rect<float>& rect, const sf::RenderWindow& window = gui::Window::getRenderWindow());

    template <typename T>
    T addSafely(const T& a, const T& b)
    {
        if (std::numeric_limits<T>().max() - a > b)
            return a + b;
        else
            return std::numeric_limits<T>().max();
    }

    template <typename T>
    T subSafely(const T& a, const T& b)
    {
        if (std::numeric_limits<T>().min() + a > b)
            return a - b;
        else
            return std::numeric_limits<T>().min();
    }
}