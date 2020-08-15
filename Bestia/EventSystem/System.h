#pragma once

#include "EventDispatcher.h"

namespace bestia {
namespace event {
namespace system {

	constexpr char* eventName[] =
	{
		"Closed",
		"Resized",
		"LostFocus",
		"GainedFocus",
		"TextEntered",
		"KeyPressed",
		"KeyReleased",
		"MouseWheelMoved",
		"MouseWheelScrolled",
		"MouseButtonPressed",
		"MouseButtonReleased",
		"MouseMoved",
		"MouseEntered",
		"MouseLeft",
		"JoystickButtonPressed",
		"JoystickButtonReleased",
		"JoystickMoved",
		"JoystickConnected",
		"JoystickDisconnected",
		"TouchBegan",
		"TouchMoved",
		"TouchEnded",
		"SensorChanged"
	};

	using delegate_sfml_t = std::function<void(const sf::Event&)>;

	template<const sf::Event::EventType TEvent>
	void connect(const delegate_sfml_t& delegate, const EventCaller* caller)
	{
		EventSFMLDispatcher<TEvent>::add(delegate, caller);
	}

	template<const sf::Event::EventType TEvent>
	void disconnect(const EventCaller* caller)
	{
		EventSFMLDispatcher<TEvent>::remove(caller);
	}

	void handleEvent(const sf::Event& event);

}}}