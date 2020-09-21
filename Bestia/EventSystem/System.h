#pragma once

#include "EventDispatcher.h"
#include "EventQueue.h"

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

	template <typename TEvent>
	using delegate_bestia_t = std::function<void(const TEvent&)>;

	template <const sf::Event::EventType TEvent>
	void connect(const delegate_sfml_t& delegate, const EventCaller* caller)
	{
		EventSFMLDispatcher<TEvent>::add(delegate, caller);
	}

	template <const sf::Event::EventType TEvent>
	void disconnect(const EventCaller* caller)
	{
		EventSFMLDispatcher<TEvent>::remove(caller);
	}

	template <typename TEvent>
	void connect(const delegate_bestia_t<TEvent>& delegate, const EventCaller* caller)
	{
		EventBestiaDispatcher<TEvent>::add(delegate, caller);
	}

	template <typename TEvent>
	void disconnect(const EventCaller* caller)
	{
		EventBestiaDispatcher<TEvent>::remove(caller);
	}

	void handleEvent(const sf::Event& event);

	template <typename TEvent>
	void handleEvent()
	{
		while (!EventQueue<TEvent>::empty())
		{
			EventBestiaDispatcher<TEvent>::dispatch(EventQueue<TEvent>::front());
			EventQueue<TEvent>::pop();
		}
	}

	void handleEvents();

}}}