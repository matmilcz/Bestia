#pragma once

#include "System.h"
#include "Timer.h"
#include <functional>
#include <SFML/Graphics/Transformable.hpp>

namespace bestia {
namespace event {

	struct TimerTimeoutEvent
	{
		timer::Timer* sender;
	};

	struct MoveEffectFinishedEvent
	{
		sf::Transformable* sender;
	};

}
}