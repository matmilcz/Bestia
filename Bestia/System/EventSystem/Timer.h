#pragma once

#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace bestia {
namespace event {
namespace timer {

	constexpr size_t DEFAULT_INTERVAL = 1000;

	class Timer
	{
	public:
		Timer(const size_t& interval);
		Timer(const Timer&) = delete;
		Timer& operator= (const Timer&) = delete;
		~Timer();

		void start();
		void stop();

		static Timer& getTimer10ms()
		{
			static Timer timer(10);
			return timer;
		}

	private:
		std::thread m_timerThread;
		std::condition_variable m_cv;
		std::mutex m_mutex;
		std::chrono::milliseconds m_interval{ DEFAULT_INTERVAL };
		bool m_isEnabled = false;
	};

}
}
}