#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include <vector>
#include "Utils/Log.h"

namespace bestia {
namespace event {

	class EventCaller
	{

	};

	template <const sf::Event::EventType TEventType>
	class EventCallSFML : virtual public EventCaller
	{
	public:
		std::function<void(const sf::Event&)> eventHandler = [](const sf::Event&) { LOG("Event function not set\n"); };
	};

	template <typename TEvent>
	class EventCallBestia : virtual public EventCaller
	{
	public:
		std::function<void(const TEvent&)> eventHandler = { [](const TEvent&) { LOG("Event function not set\n"); } };
	};

}}