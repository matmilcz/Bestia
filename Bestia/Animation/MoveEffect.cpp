#include "MoveEffect.h"
#include "EventSystem/System.h"
#include "EventSystem/Timer.h"

namespace bestia {
namespace animation {
namespace effect {

	/*void move(IMoveEffect* object, const sf::Vector2f& effectSpeed, const sf::Vector2f& targetPosition, std::function<void()> callback)
	{
		event::system::connect<event::TimerTimeoutEvent>([=](const event::TimerTimeoutEvent& e) {
			if (e.sender == &event::timer::Timer::getTimer10ms())
			{
				if (!object->move(effectSpeed, targetPosition))
				{
					event::system::disconnect<event::TimerTimeoutEvent>(object);
					callback();
				}
			}
			}, object);
	}*/

	void move(sf::Transformable* object, const sf::Vector2f& effectSpeed, const sf::Vector2f& targetPosition, std::function<void()> callback)
	{
		std::cout << "connecting TimerTimeoutEvent...\n";
		event::system::connect<event::TimerTimeoutEvent>([=](const event::TimerTimeoutEvent& e) {
			if (e.sender == &event::timer::Timer::getTimer10ms())
			{
				auto o = object;
				o->move(effectSpeed);
				//std::cout << "timeout posx: " << object->getPosition().x << "  timeout posy: " << object->getPosition().y << '\n';
				if (o->getPosition() == targetPosition)
				{
					/*std::cout << "event queue before disconnecting " << std::hex << object << "\n";
					event::system::EventQueue<event::MoveEffectFinishedEvent>::print();*/
					event::EventBestiaDispatcher<event::MoveEffectFinishedEvent>::print();
					event::system::EventQueue<event::TimerTimeoutEvent>::print();
					std::cout << "disconnecting " << std::hex << object <<  "\n";
					//auto o = object;
					event::system::disconnect<event::TimerTimeoutEvent>(object);
					event::system::EventQueue<event::TimerTimeoutEvent>::print();
					/*event::MoveEffectFinishedEvent e;
					e.sender = o;
					std::cout << e.sender << '\n';
					event::system::EventQueue<event::MoveEffectFinishedEvent>::push(e);
					std::cout << "event queue after disconnecting " << std::hex << object << "\n";
					event::system::EventQueue<event::MoveEffectFinishedEvent>::print();*/
				}
			}
			}, object);
		std::cout << "finished connecting\n";
	}

}
}
}
