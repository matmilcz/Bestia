#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include "Utils/Log.h"

namespace bestia {
namespace event {

	class EventCaller
	{

	};

	template<const sf::Event::EventType TEventType>
	class EventCall : virtual public EventCaller
	{
	public:
		std::function<void(const sf::Event&)> eventHandler = [](const sf::Event&) { LOG("Event function not set\n"); };
	};

}}