#pragma once

#include <queue>
#include <mutex>

namespace bestia {
namespace event {
namespace system {

	template <typename TEvent>
	class EventQueue
	{
	public:
		static void push(const TEvent& event)
		{
			std::lock_guard<std::mutex> lock(get().m_mutex);
			if (typeid(TEvent) == typeid(event::MoveEffectFinishedEvent))
				std::cout << "pushing event for " << event.sender << '\n';
			get().m_queue.push(event);
		}

		static const TEvent front()
		{
			std::lock_guard<std::mutex> lock(get().m_mutex);
			return get().m_queue.front();
		}

		static void pop()
		{
			std::lock_guard<std::mutex> lock(get().m_mutex);
			get().m_queue.pop();
		}

		static bool empty()
		{
			std::lock_guard<std::mutex> lock(get().m_mutex);
			return get().m_queue.empty();
		}

		static void print()
		{
			std::lock_guard<std::mutex> lock(get().m_mutex);
			std::queue<TEvent> q = get().m_queue;
			std::cout << "event queue: ";
			while (!q.empty())
			{
				std::cout << q.front().sender << " ";
				q.pop();
			}
			std::cout << '\n';
		};

	private:
		EventQueue() = default;

		static EventQueue& get()
		{
			static EventQueue<TEvent> eventQueue;
			return eventQueue;
		}

		std::queue<TEvent> m_queue;
		std::mutex m_mutex; // TODO: mutex not always necessary, remove above warnings
	};

}
}
}