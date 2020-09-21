#include "Timer.h"

namespace bestia {
namespace event {
namespace timer {

	Timer::Timer(const size_t& interval) : m_interval(std::chrono::milliseconds(interval))
	{

	}

	Timer::~Timer()
	{
		stop();
		m_timerThread.join();
	}

	void Timer::start()
	{
		m_isEnabled = true;

		m_timerThread = std::thread([this]() {
			std::unique_lock<std::mutex> uniqueLock(m_mutex);

			while (!m_cv.wait_for(uniqueLock, m_interval, [this]() { return !m_isEnabled; }))
			{
				// TODO: send timeout event
				std::this_thread::sleep_for(m_interval);
			}
			});
	}

	void Timer::stop()
	{
		std::lock_guard<std::mutex> guardLock(m_mutex);
		m_isEnabled = false;
		m_cv.notify_one();
	}

}
}
}