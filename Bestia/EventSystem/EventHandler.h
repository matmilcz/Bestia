#pragma once

#include "EventDispatcher.h"

namespace bestia {
namespace event {
	
	static const char* eventName[] =
	{
		"Closed",
		"Resized",
		"LostFocus",
		"GainedFocus",
		"TextEntered",
		"KeyPressed",
		"KeyReleased",
		"MouseWheelMoved",
		"MouseWheelScrolled",
		"MouseButtonPressed",
		"MouseButtonReleased",
		"MouseMoved",
		"MouseEntered",
		"MouseLeft",
		"JoystickButtonPressed",
		"JoystickButtonReleased",
		"JoystickMoved",
		"JoystickConnected",
		"JoystickDisconnected",
		"TouchBegan",
		"TouchMoved",
		"TouchEnded",
		"SensorChanged"
	};

	void handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			EventDispatcher<sf::Event::Closed>::dispatch(event);
			break;
		case sf::Event::Resized:
			EventDispatcher<sf::Event::Resized>::dispatch(event);
			break;
		case sf::Event::MouseButtonPressed:
			EventDispatcher<sf::Event::MouseButtonPressed>::dispatch(event);
			break;
		case sf::Event::MouseMoved:
			EventDispatcher<sf::Event::MouseMoved>::dispatch(event);
			break;
		case sf::Event::KeyPressed:
			EventDispatcher<sf::Event::KeyPressed>::dispatch(event);
		default:
			LOG("INF: Unhandled event: " << eventName[event.type] << '\n');
			break;
		}
	}

}}