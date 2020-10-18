#include "FadeEffect.h"
#include "EventSystem/System.h"
#include "EventSystem/Timer.h"

namespace bestia {
namespace animation {
namespace effect {

	void fadeIn(IFadeInEffect* object,
				const sf::Uint8 effectSpeed,
				const sf::Uint8 targetValue)
	{
		event::system::connect<event::TimerTimeoutEvent>([=](const event::TimerTimeoutEvent& e) {
			if (e.sender == &event::timer::Timer::getTimer10ms())
			{
				if (!object->fadeIn(effectSpeed, targetValue))
				{
					event::system::disconnect<event::TimerTimeoutEvent>(object);
				}
			}
			}, object);
	}

	void fadeOut(IFadeOutEffect* object,
				const sf::Uint8 effectSpeed,
				const sf::Uint8 targetValue)
	{
		event::system::connect<event::TimerTimeoutEvent>([=](const event::TimerTimeoutEvent& e) {
			if (e.sender == &event::timer::Timer::getTimer10ms())
			{
				if (!object->fadeOut(effectSpeed, targetValue))
				{
					event::system::disconnect<event::TimerTimeoutEvent>(object);
				}
			}
			}, object);
	}

}
}
}