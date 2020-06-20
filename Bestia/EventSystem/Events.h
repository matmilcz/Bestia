#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include "Utils/Log.h"

namespace bestia {
namespace event {

	using event_fcn_t = std::function<void(const sf::Event& event)>;

	class EventCaller
	{

	};

	class MouseButtonPressedEvent : public virtual EventCaller
	{
	public:
		void setOnMouseButtonPressedEvent(const event_fcn_t& eventFcn);
		virtual void onMouseButtonPressedEvent(const sf::Event& event);

	private:
		event_fcn_t m_onMouseButtonPressedEvent;
	};

	class MouseEnteredEvent : public virtual EventCaller
	{
	public:
		void setOnMouseEnteredEvent(const event_fcn_t& eventFcn);
		virtual void onMouseEnteredEvent(const sf::Event& event);

	private:
		event_fcn_t m_onMouseEnteredEvent;
	};

	class MouseLeftEvent : public virtual EventCaller
	{
	public:
		void setOnMouseLeftEvent(const event_fcn_t& eventFcn);
		virtual void onMouseLeftEvent(const sf::Event& event);

	private:
		event_fcn_t m_onMouseLeftEvent;
	};
}}