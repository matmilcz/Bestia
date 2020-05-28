#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include "Utils/Log.h"

namespace bestia {
namespace event {

	template <sf::Event::EventType TEvent>
	class EventDispatcher
	{
	public:
		static void setDispatcher(const std::function<void()>& fcn);
		static void dispatch();

	private:
		EventDispatcher() = default;
		EventDispatcher(const EventDispatcher&) = delete;
		~EventDispatcher() = default;
		EventDispatcher& operator= (const EventDispatcher&) = delete;

		static EventDispatcher<TEvent>& get();

		std::function<void()> m_fcn;
	};

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::setDispatcher(const std::function<void()>& fcn)
	{
		EventDispatcher<TEvent>::get().m_fcn = fcn;
	}

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::dispatch()
	{
		try
		{
			EventDispatcher<TEvent>::get().m_fcn();
		}
		catch (const std::bad_function_call& e)
		{
			LOG("WRN: Dispatcher not set for event: " << TEvent << '\n');
		}
	}

	template<sf::Event::EventType TEvent>
	EventDispatcher<TEvent>& EventDispatcher<TEvent>::get()
	{
		static EventDispatcher<TEvent> eventDispatcher;
		return eventDispatcher;
	}

}}