#pragma once

#include <SFML/Graphics.hpp>

namespace bestia {
namespace gui {

    using uint = unsigned int;

    class Window
    {
    public:
        Window(const Window&) = delete;
        ~Window() = default;
        Window& operator= (const Window&) = delete;

        static inline void setView(const sf::View& view);

        static inline void clear();
        static inline void close();
        static inline void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
        static inline void display();
        static inline bool pollEvent(sf::Event& event);
        static inline bool isOpen();

        static inline sf::RenderWindow& getRenderWindow() // TODO: temporary
        {
            return get().m_renderWindow;
        }

        static inline const sf::View& getView();
        static inline sf::Vector2u getSize();

    private:
#ifdef _DEBUG
        sf::RenderWindow m_renderWindow{ sf::VideoMode::getDesktopMode(), "Bestia" };
#else
        sf::RenderWindow m_renderWindow{ sf::VideoMode::getDesktopMode(), "Bestia", sf::Style::Fullscreen };
#endif

        sf::Image m_cursorImage;
        sf::Cursor m_cursor;

        Window();
        static Window& get();
    };

    inline void Window::setView(const sf::View& view)
    {
        get().m_renderWindow.setView(view);
    }

    inline void Window::clear()
    {
        get().m_renderWindow.clear();
    }

    inline void Window::close()
    {
        get().m_renderWindow.close();
    }

    inline void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        get().m_renderWindow.draw(drawable, states);
    }

    inline void Window::display()
    {
        get().m_renderWindow.display();
    }

    inline bool Window::pollEvent(sf::Event& event)
    {
        return get().m_renderWindow.pollEvent(event);
    }

    inline bool Window::isOpen()
    {
        return get().m_renderWindow.isOpen();
    }

    inline const sf::View& Window::getView()
    {
        return get().m_renderWindow.getView();
    }

    inline sf::Vector2u Window::getSize()
    {
        return get().m_renderWindow.getSize();
    }

}}