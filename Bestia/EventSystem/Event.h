#pragma once

#include "System.h"
#include "Timer.h"

namespace bestia {
namespace event {

	struct TimerTimeoutEvent
	{
		timer::Timer* sender;
	};

}
}