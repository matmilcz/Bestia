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