#pragma once

#include <vector>
#include <algorithm>
#include "Events.h"

namespace bestia {
namespace event {

	using event_fcn = std::function<void(const sf::Event& event)>;

	template <sf::Event::EventType TEvent>
	class EventDispatcher
	{
	public:
		static void add(const event_fcn& fcn, const EventCaller* eventCaller);
		static void remove(const EventCaller* eventCaller);
		static void dispatch(const sf::Event& event);

	private:
		EventDispatcher();

		EventDispatcher(const EventDispatcher&) = delete;
		~EventDispatcher() = default;
		EventDispatcher& operator= (const EventDispatcher&) = delete;

		static EventDispatcher<TEvent>& get();

		std::vector<std::pair<event_fcn, const EventCaller*>> m_fcn;
	};

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::add(const event_fcn& fcn, const EventCaller* eventCaller)
	{
		EventDispatcher<TEvent>::get().m_fcn.push_back({ fcn, eventCaller });
	}

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::remove(const EventCaller* eventCaller)
	{
		auto& dispatcher = EventDispatcher<TEvent>::get();

		dispatcher.m_fcn.erase(
			std::remove_if(
				dispatcher.m_fcn.begin(), dispatcher.m_fcn.end(),
				[&eventCaller](const std::pair<event_fcn, const EventCaller*>& pair) { return pair.second == eventCaller; }),
			dispatcher.m_fcn.end()
		);
	}

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::dispatch(const sf::Event& event)
	{
		try
		{
			for (const auto& it_fcn : EventDispatcher<TEvent>::get().m_fcn)
			{
				(it_fcn.first)(event);
			}
		}
		catch (const std::bad_function_call&)
		{
			LOG("WRN: Dispatcher not set for event: " << TEvent << "  " << EventDispatcher<TEvent>::get().m_fcn.size() << '\n');
		}
	}

	template<sf::Event::EventType TEvent>
	EventDispatcher<TEvent>::EventDispatcher()
	{
		constexpr size_t defaultCapacity = 64;
		m_fcn.reserve(defaultCapacity);
	}

	template<sf::Event::EventType TEvent>
	EventDispatcher<TEvent>& EventDispatcher<TEvent>::get()
	{
		static EventDispatcher<TEvent> eventDispatcher;
		return eventDispatcher;
	}

}}