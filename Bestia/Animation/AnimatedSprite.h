#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "EventSystem/System.h"
#include "EventSystem/Timer.h"
#include "Animation.h"

namespace bestia {
namespace animation {

	class AnimatedSprite : public sf::Sprite
	{
	public:
		AnimatedSprite(const Animation& animation, const event::timer::Timer& frameUpdateTimer);
		AnimatedSprite(const AnimatedSprite&) = delete; // TODO
		~AnimatedSprite();
		AnimatedSprite& operator= (const AnimatedSprite&) = delete; // TODO

		void setFrame(unsigned const frameIdx);
		void start();
		void stop();

	private:
		const Animation& m_animation;
		const event::timer::Timer& m_frameUpdateTimer;
		std::vector<sf::IntRect>::const_iterator m_currFrameIter;

		void updateFrame();
	};

}
}