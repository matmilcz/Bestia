#pragma once

#include "System.h"
#include "Timer.h"
#include <functional>
#include <SFML/Graphics/Transformable.hpp>
#include "SFML/Window/Event.hpp"

namespace bestia {
namespace event {

	struct Event {};

	struct MouseMoveEvent : public Event
	{
		MouseMoveEvent(const sf::Event& event) : x(event.mouseMove.x), y(event.mouseMove.y)
		{
		}

		int x;      ///< X position of the mouse pointer, relative to the left of the owner window
		int y;      ///< Y position of the mouse pointer, relative to the top of the owner window
	};

	struct MouseButtonPressedEvent : public MouseMoveEvent
	{
		MouseButtonPressedEvent(const sf::Event& event) : MouseMoveEvent(event), button(event.mouseButton.button)
		{
		}

		sf::Mouse::Button button; ///< Code of the button that has been pressed
	};

	struct TimerTimeoutEvent
	{
		timer::Timer* sender;
	};

	struct MoveEffectFinishedEvent
	{
		sf::Transformable* sender;
	};

	struct DummyEvent
	{
		sf::Transformable* sender;
	};

}
}