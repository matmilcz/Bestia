#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const sf::Texture& _spritesheet, 
							   const std::vector<sf::IntRect>& _animationFrames, 
							   const sf::Time& _frameUpdateTime)
	: m_animationFrames(&_animationFrames),
	  m_frameUpdateTime(_frameUpdateTime)
{
	setTexture(_spritesheet);
	setTextureRect(m_animationFrames->front());
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::setAnimationFrames(const std::vector<sf::IntRect>& _animationFrames)
{
	m_animationFrames = &_animationFrames;
}

void AnimatedSprite::update(const sf::Time& _frameTime)
{
	m_frameTime += _frameTime;

	if (m_frameTime >= m_frameUpdateTime)
	{
		moveToNextFrame();
		m_frameTime = sf::seconds(0);
	}
}

void AnimatedSprite::moveToNextFrame()
{
	if (m_currentFrame < m_animationFrames->end() - 1)
	{
		++m_currentFrame;
	}
	else
	{
		m_currentFrame = m_animationFrames->begin();
	}

	setTextureRect(*m_currentFrame);
}

void AnimatedSprite::setTextureRect(const sf::IntRect& rectangle)
{
	sf::Sprite::setTextureRect(rectangle);
}

