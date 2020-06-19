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

	void MouseEnterEvent::setOnMouseEnterEvent(const event_fcn_t& eventFcn)
	{
		m_onMouseEnterEvent = eventFcn;
	}

	void MouseEnterEvent::onMouseEnterEvent(const sf::Event& event)
	{
		if (m_onMouseEnterEvent)
		{
			m_onMouseEnterEvent(event);
		}
		else
		{
			LOG("WRN: no onMouseEnterEvent event set for object: " << this << '\n');
		}
	}

	void MouseExitEvent::setOnMouseExitEvent(const event_fcn_t& eventFcn)
	{
		m_onMouseExitEvent = eventFcn;
	}

	void MouseExitEvent::onMouseExitEvent(const sf::Event& event)
	{
		if (m_onMouseExitEvent)
		{
			m_onMouseExitEvent(event);
		}
		else
		{
			LOG("WRN: no onMouseExitEvent event set for object: " << this << '\n');
		}
	}

}}