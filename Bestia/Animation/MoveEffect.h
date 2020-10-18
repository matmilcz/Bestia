#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>

namespace bestia {
namespace animation {
namespace effect {

	class IMoveEffect
	{
	public:
		virtual bool move(const sf::Vector2f& effectSpeed, const sf::Vector2f& targetPosition) = 0;
	};

	void move(IMoveEffect* object,
			  const sf::Vector2f& effectSpeed,
			  const sf::Vector2f& targetPosition,
			  std::function<void()> callback = []() {});

	void move(sf::Transformable* object,
			  const sf::Vector2f& effectSpeed,
			  const sf::Vector2f& targetPosition,
			  std::function<void()> callback = []() {});

}
}
}
