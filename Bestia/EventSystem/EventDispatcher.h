#pragma once

#include <vector>
#include <algorithm>
#include "EventCaller.h"
#include "Event.h"

namespace bestia {
namespace event {

	template<typename TEvent>
	class EventDispatcherBase
	{
	protected:
		using delegate_t = std::function<void(const TEvent&)>;
		using delegate_caller_pair_t = std::pair<delegate_t, const EventCaller*>;

		void dispatch(const TEvent& event)
		{
			try
			{
				for (const auto& listener : m_eventListeners)
				{
					listener.first(event);
				}
			}
			catch (const std::bad_function_call&)
			{
				LOG("WRN: Dispatcher not set for event: " /*<< event.type*/ << "  Events in queue: " << m_eventListeners.size() << '\n');
			}
		}

		void add(const delegate_t& delegate, const EventCaller* caller)
		{
			m_eventListeners.push_back(delegate_caller_pair_t{ delegate, caller });
		}

		void remove(const EventCaller* caller)
		{
			m_eventListeners.erase(
				std::remove_if(
					m_eventListeners.begin(), m_eventListeners.end(),
					[&caller](const delegate_caller_pair_t& pair) { return pair.second == caller; }),
				m_eventListeners.end()
			);
		}

		void reserve(const size_t& capacity)
		{
			m_eventListeners.reserve(capacity);
		}

	private:
		std::vector<delegate_caller_pair_t> m_eventListeners;
	};

	template <typename TEvent>
	class EventBestiaDispatcher : public EventDispatcherBase<TEvent>
	{
	public:
		static void add(const delegate_t& delegate, const EventCaller* caller)
		{
			get().EventDispatcherBase<TEvent>::add(delegate, caller);
		}

		static void remove(const EventCaller* caller)
		{
			get().EventDispatcherBase<TEvent>::remove(caller);
		}

		static void print()
		{
			get().EventDispatcherBase<TEvent>::print();
		}
		
		static void dispatch(const TEvent& event)
		{
			get().EventDispatcherBase<TEvent>::dispatch(event);
		}

	private:
		EventBestiaDispatcher() = default;
		EventBestiaDispatcher(const EventBestiaDispatcher&) = delete;
		~EventBestiaDispatcher() = default;
		EventBestiaDispatcher& operator= (const EventBestiaDispatcher&) = delete;

		static EventBestiaDispatcher& get()
		{
			static EventBestiaDispatcher eventDispatcher;
			return eventDispatcher;
		}
	};

	template<const sf::Event::EventType TEventType>
	class EventSFMLDispatcher : public EventDispatcherBase<sf::Event>
	{
		using delegate_t = std::function<void(const sf::Event&)>;

	public:
		static void add(const delegate_t& delegate, const EventCaller* caller)
		{
			get().EventDispatcherBase<sf::Event>::add(delegate, caller);
		}

		static void remove(const EventCaller* caller)
		{
			get().EventDispatcherBase<sf::Event>::remove(caller);
		}

		static void print()
		{
			get().EventDispatcherBase<sf::Event>::print();
		}

		static void dispatch(const sf::Event& event)
		{
			get().EventDispatcherBase<sf::Event>::dispatch(event);
		}

	private:
		EventSFMLDispatcher()
		{
			constexpr size_t largeCapacity = 64;
			constexpr size_t smallCapacity = 4;

			switch (TEventType)
			{
			case sf::Event::MouseMoved:
				reserve(largeCapacity);
				break;
			default:
				reserve(smallCapacity);
				break;
			}
		}
		EventSFMLDispatcher(const EventSFMLDispatcher&) = delete;
		~EventSFMLDispatcher() = default;
		EventSFMLDispatcher& operator= (const EventSFMLDispatcher&) = delete;

		static EventSFMLDispatcher& get()
		{
			static EventSFMLDispatcher eventDispatcher;
			return eventDispatcher;
		}
	};

}}