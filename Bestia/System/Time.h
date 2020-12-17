#pragma once

#include <SFML/System/Clock.hpp>

namespace bestia {
namespace time {

namespace {

	sf::Clock& getClock()
	{
		static sf::Clock clock;
		return clock;
	}

}

	static const sf::Time getDeltaTime()
	{
		return getClock().getElapsedTime();
	}

	static const sf::Time restart()
	{
		return getClock().restart();
	}

}
}
