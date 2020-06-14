#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include <vector>
#include <algorithm>
#include "Utils/Log.h"

namespace bestia {
namespace event {

	using event_fcn = std::function<void(const sf::Event& event)>;
	using caller_id = uint64_t;

	class EventCaller
	{
	protected:
		EventCaller()
		{
			m_id = ++m_counter;
		}

		~EventCaller() = default; // TODO: maybe store free ids

		caller_id m_id;

	private:
		static uint64_t m_counter;
	};

	template <sf::Event::EventType TEvent>
	class EventDispatcher
	{
	public:
		static void setDispatcher(const event_fcn& fcn, const caller_id& id);
		static void removeDispatcher(const caller_id& id);
		static void dispatch(const sf::Event& event);
		static void clear()
		{
			EventDispatcher<TEvent>::get().m_fcn.clear();
		}

	private:
		EventDispatcher();

		EventDispatcher(const EventDispatcher&) = delete;
		~EventDispatcher() = default;
		EventDispatcher& operator= (const EventDispatcher&) = delete;

		static EventDispatcher<TEvent>& get();

		std::vector<std::pair<event_fcn, caller_id>> m_fcn;
	};

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::setDispatcher(const event_fcn& fcn, const caller_id& id)
	{
		EventDispatcher<TEvent>::get().m_fcn.push_back({ fcn, id });
	}

	template<sf::Event::EventType TEvent>
	void EventDispatcher<TEvent>::removeDispatcher(const caller_id& id)
	{
		auto& dispatcher = EventDispatcher<TEvent>::get();

		dispatcher.m_fcn.erase(
			std::remove_if(
				dispatcher.m_fcn.begin(), dispatcher.m_fcn.end(),
				[&id](const std::pair<event_fcn, caller_id>& pair) { return pair.second == id; }),
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