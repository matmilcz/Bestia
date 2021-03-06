#include "AnimatedSprite.h"

namespace bestia {
namespace animation {

	AnimatedSprite::AnimatedSprite(const std::shared_ptr<Animation> animation, const event::timer::Timer& frameUpdateTimer) :
		m_animation(animation),
		m_frameUpdateTimer(frameUpdateTimer)
	{
		sf::Sprite::setTexture(m_animation->spritesheet);

		constexpr unsigned initialFrameIdx = 0;
		setFrame(initialFrameIdx);
	}

	AnimatedSprite::~AnimatedSprite()
	{
		event::system::disconnect<event::TimerTimeoutEvent>(this);
	}

	void AnimatedSprite::setFrame(unsigned const frameIdx)
	{
		m_currFrameIter = m_animation->animationFrames.begin() + frameIdx;
		sf::Sprite::setTextureRect(*m_currFrameIter);
	}

	void AnimatedSprite::start()
	{
		event::system::connect<event::TimerTimeoutEvent>([this](const event::TimerTimeoutEvent& e) {
			if (e.sender == &m_frameUpdateTimer)
			{
				updateFrame();
			}
			}, this);
	}

	void AnimatedSprite::stop()
	{
		event::system::disconnect<event::TimerTimeoutEvent>(this);
	}

	void AnimatedSprite::updateFrame()
	{
		++m_currFrameIter;

		if (m_currFrameIter == m_animation->animationFrames.end())
		{
			m_currFrameIter = m_animation->animationFrames.begin();
		}

		sf::Sprite::setTextureRect(*m_currFrameIter);
	}

}
}