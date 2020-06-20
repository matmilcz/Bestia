#include "Events.h"

namespace bestia {
namespace event {

	void MouseButtonPressedEvent::setOnMouseButtonPressedEvent(const event_fcn_t& eventFcn)
	{
		m_onMouseButtonPressedEvent = eventFcn;
	}

	void MouseButtonPressedEvent::onMouseButtonPressedEvent(const sf::Event& event)
	{
		if (m_onMouseButtonPressedEvent)
		{
			m_onMouseButtonPressedEvent(event);
		}
		else
		{
			LOG("WRN: no onMouseButtonPressedEvent event set for object: " << this << '\n');
		}
	}

	void MouseEnteredEvent::setOnMouseEnteredEvent(const event_fcn_t& eventFcn)
	{
		m_onMouseEnteredEvent = eventFcn;
	}

	void MouseEnteredEvent::onMouseEnteredEvent(const sf::Event& event)
	{
		if (m_onMouseEnteredEvent)
		{
			m_onMouseEnteredEvent(event);
		}
		else
		{
			LOG("WRN: no onMouseEnteredEvent event set for object: " << this << '\n');
		}
	}

	void MouseLeftEvent::setOnMouseLeftEvent(const event_fcn_t& eventFcn)
	{
		m_onMouseLeftEvent = eventFcn;
	}

	void MouseLeftEvent::onMouseLeftEvent(const sf::Event& event)
	{
		if (m_onMouseLeftEvent)
		{
			m_onMouseLeftEvent(event);
		}
		else
		{
			LOG("WRN: no onMouseLeftEvent event set for object: " << this << '\n');
		}
	}

}}