#include "CommonFcn.h"
#include "System/EventSystem/Timer.h"
#include "System/EventSystem/System.h"
#include "Defs.h"
#include <cmath>

extern bestia::event::timer::Timer g_timer60tpc;

namespace bestia {

    void resizeView(const sf::Window& window, sf::View& view)
    {
        const float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
        view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
    }

    void moveView(const sf::Vector2f& newCenter, sf::View& view, const event::EventCaller* caller)
    {
		static const sf::Vector2f s_newCenter = newCenter;
		static const event::EventCaller* s_caller = caller;

		event::system::connect<event::TimerTimeoutEvent>([&](const event::TimerTimeoutEvent& e) {
			if (e.sender == &event::timer::Timer::getTimer10ms())
			{
				auto distance = view.getCenter() - s_newCenter;
				
				if (distance.x > 20.f || distance.y > 30.f)
				{
					if (view.getCenter().y > s_newCenter.y)
					{
						view.move(sf::Vector2f{ 0.f, -30.f });
					}
					else if (view.getCenter().y < s_newCenter.y)
					{
						view.move(sf::Vector2f{ 0.f, 30.f });
					}

					if (view.getCenter().x > s_newCenter.x)
					{
						view.move(sf::Vector2f{ -30.f, 0.f });
					}
					else if (view.getCenter().x < s_newCenter.x)
					{
						view.move(sf::Vector2f{ 30.f, 0.f });
					}
				}
				else
				{
					view.setCenter(s_newCenter);
					event::system::disconnect<event::TimerTimeoutEvent>(s_caller);
				}
			}
			}, s_caller);
    }

	bool isMouseOver(const sf::Shape& shape, const sf::RenderWindow& window)
	{
		const auto& mousePixelPos = sf::Mouse::getPosition(window);
		const auto& mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

		return shape.getGlobalBounds().contains(mouseCoordPos);
	}

	bool isMouseOver(const sf::Rect<float>& rect, const sf::RenderWindow& window)
	{
		const auto& mousePixelPos = sf::Mouse::getPosition(window);
		const auto& mouseCoordPos = window.mapPixelToCoords(mousePixelPos);

		return rect.contains(mouseCoordPos);
	}

}
