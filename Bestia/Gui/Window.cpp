#include "Window.h"

namespace bestia {
namespace gui {

    Window::Window()
    {
        m_renderWindow.setVerticalSyncEnabled(true);

        constexpr uint hotspotX = 0;
        constexpr uint hotspotY = 0;
        m_cursorImage.loadFromFile("Resources/sprites/cursor/small_rounded_up_left_rescaled.png"); // TODO: save the pixel array of original image and rescale
        m_cursor.loadFromPixels(m_cursorImage.getPixelsPtr(), m_cursorImage.getSize(), sf::Vector2u{ hotspotX, hotspotY });

        m_renderWindow.setMouseCursor(m_cursor);
        m_renderWindow.setMouseCursorGrabbed(true);
    }

    Window& Window::get()
    {
        static Window window;
        return window;
    }

}}