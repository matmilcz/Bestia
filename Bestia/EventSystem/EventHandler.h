#pragma once

#include "EventDispatcher.h"

namespace bestia {
namespace event {
	
	void handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			EventDispatcher<sf::Event::Closed>::dispatch();
			break;
		case sf::Event::Resized:
			EventDispatcher<sf::Event::Resized>::dispatch();
			break;
		case sf::Event::MouseButtonPressed:
			EventDispatcher<sf::Event::MouseButtonPressed>::dispatch();
			break;
		case sf::Event::MouseMoved:
			EventDispatcher<sf::Event::MouseMoved>::dispatch();
			break;
		case sf::Event::KeyPressed:
			EventDispatcher<sf::Event::KeyPressed>::dispatch();
		default:
			LOG("INF: Unhandled event: " << event.type << '\n');
			break;
		}
	}

}}