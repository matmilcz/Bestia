#include "AnimatedSprite.h"

namespace bestia {
namespace animation {

	AnimatedSprite::AnimatedSprite(const Animation& animation, const event::timer::Timer& frameUpdateTimer) :
		m_animation(animation),
		m_frameUpdateTimer(frameUpdateTimer)
	{
		sf::Sprite::setTexture(m_animation.spritesheet);

		constexpr unsigned initialFrameIdx = 0;
		setFrame(initialFrameIdx);
	}

	AnimatedSprite::~AnimatedSprite()
	{
		event::system::disconnect<event::TimerTimeoutEvent>(&m_frameUpdateTimer);
	}

	void AnimatedSprite::setFrame(unsigned const frameIdx)
	{
		m_currFrameIter = m_animation.animationFrames.begin() + frameIdx;
		sf::Sprite::setTextureRect(*m_currFrameIter);
	}

	void AnimatedSprite::start()
	{
		event::system::connect<event::TimerTimeoutEvent>([this](const event::TimerTimeoutEvent& e) {
			if (e.sender == &m_frameUpdateTimer)
			{
				updateFrame();
			}
			}, &m_frameUpdateTimer);
	}

	void AnimatedSprite::stop()
	{
		event::system::disconnect<event::TimerTimeoutEvent>(&m_frameUpdateTimer);
	}

	void AnimatedSprite::updateFrame()
	{
		++m_currFrameIter;

		if (m_currFrameIter == m_animation.animationFrames.end())
		{
			m_currFrameIter = m_animation.animationFrames.begin();
		}

		sf::Sprite::setTextureRect(*m_currFrameIter);
	}

}
}