#include "System.h"

namespace bestia {
namespace event {
namespace system {

	void handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			EventSFMLDispatcher<sf::Event::Closed>::dispatch(event);
			break;
		case sf::Event::Resized:
			EventSFMLDispatcher<sf::Event::Resized>::dispatch(event);
			break;
		case sf::Event::MouseButtonPressed:
			EventSFMLDispatcher<sf::Event::MouseButtonPressed>::dispatch(event);
			break;
		case sf::Event::MouseMoved:
			EventSFMLDispatcher<sf::Event::MouseMoved>::dispatch(event);
			break;
		case sf::Event::KeyPressed:
			EventSFMLDispatcher<sf::Event::KeyPressed>::dispatch(event);
		default:
			LOG("INF: Unhandled event: " << eventName[event.type] << '\n');
			break;
		}
	}

}}}