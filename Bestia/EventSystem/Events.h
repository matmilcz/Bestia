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

	class MouseEnterEvent : public virtual EventCaller
	{
	public:
		void setOnMouseEnterEvent(const event_fcn_t& eventFcn);
		virtual void onMouseEnterEvent(const sf::Event& event);

	private:
		event_fcn_t m_onMouseEnterEvent;
	};

	class MouseExitEvent : public virtual EventCaller
	{
	public:
		void setOnMouseExitEvent(const event_fcn_t& eventFcn);
		virtual void onMouseExitEvent(const sf::Event& event);

	private:
		event_fcn_t m_onMouseExitEvent;
	};
}}