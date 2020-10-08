#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <utility>

namespace bestia {
namespace animation {

	struct Animation
	{
		Animation(const sf::Texture& _spritesheet, const std::vector<sf::IntRect>& _animationFrames) :
			spritesheet(_spritesheet),
			animationFrames(_animationFrames)
		{

		}

		Animation(sf::Texture&& _spritesheet, std::vector<sf::IntRect>&& _animationFrames) :
			spritesheet(std::move(_spritesheet)),
			animationFrames(std::move(_animationFrames))
		{

		}

		Animation(const Animation&) = default;
		Animation(Animation&&) = default;
		~Animation() = default;
		Animation& operator= (const Animation&) = default;
		Animation& operator= (Animation&&) = default;

		const sf::Texture spritesheet;
		const std::vector<sf::IntRect> animationFrames;
	};

}
}