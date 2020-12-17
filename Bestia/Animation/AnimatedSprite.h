#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "System/EventSystem/System.h"
#include "System/EventSystem/Timer.h"
#include "Animation.h"

namespace bestia {
namespace animation {

	class AnimatedSprite : public sf::Sprite, public event::EventCaller
	{
	public:
		AnimatedSprite(const std::shared_ptr<Animation> animation, const event::timer::Timer& frameUpdateTimer);
		AnimatedSprite(const AnimatedSprite&) = delete; // TODO
		~AnimatedSprite();
		AnimatedSprite& operator= (const AnimatedSprite&) = delete; // TODO

		void setFrame(unsigned const frameIdx);
		void start();
		void stop();

	private:
		const std::shared_ptr<Animation> m_animation;
		const event::timer::Timer& m_frameUpdateTimer;
		std::vector<sf::IntRect>::const_iterator m_currFrameIter;

		void updateFrame();
	};

}
}