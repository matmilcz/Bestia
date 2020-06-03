#include "Window.h"

namespace bestia {
namespace gui {

    Window::Window()
    {
        m_renderWindow.setVerticalSyncEnabled(true);

        constexpr uint offsetX = 14;
        constexpr uint offsetY = 5;
        m_cursorImage.loadFromFile("Resources/sprites/cursor.png");
        m_cursor.loadFromPixels(m_cursorImage.getPixelsPtr(), m_cursorImage.getSize(), sf::Vector2u{ offsetX, offsetY });

        m_renderWindow.setMouseCursor(m_cursor);
        m_renderWindow.setMouseCursorGrabbed(true);
    }

    Window& Window::get()
    {
        static Window window;
        return window;
    }

}}