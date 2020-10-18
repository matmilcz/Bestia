#pragma once

#include <SFML/Config.hpp>
#include "EventSystem/EventCaller.h"

namespace bestia {
namespace animation {
namespace effect {

	constexpr sf::Uint8 DEFAULT_FADE_IN_TARGET_VAL = 255;
	constexpr sf::Uint8 DEFAULT_FADE_OUT_TARGET_VAL = 0;

	class IFadeInEffect : public virtual event::EventCaller
	{
	public:
		virtual bool fadeIn(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue) = 0;
	};

	class IFadeOutEffect : public virtual event::EventCaller
	{
	public:
		virtual bool fadeOut(const sf::Uint8 effectSpeed, const sf::Uint8 targetValue) = 0;
	};

	class IFadeEffect : public IFadeInEffect, public IFadeOutEffect
	{
	};

	void fadeIn(IFadeInEffect* object,
				const sf::Uint8 effectSpeed,
				const sf::Uint8 targetValue = DEFAULT_FADE_IN_TARGET_VAL);

	void fadeOut(IFadeOutEffect* object,
				const sf::Uint8 effectSpeed,
				const sf::Uint8 targetValue = DEFAULT_FADE_OUT_TARGET_VAL);

}
}
}
