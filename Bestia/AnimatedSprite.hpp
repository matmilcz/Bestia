#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite : public sf::Sprite
{
public:
	AnimatedSprite(const sf::Texture& _spritesheet, 
				   const std::vector<sf::IntRect>& _animationFrames,
				   const sf::Time& _frameUpdateTime = sf::seconds(0.5f));
	~AnimatedSprite();
	AnimatedSprite(const AnimatedSprite&) = delete;
	AnimatedSprite(AnimatedSprite&&) = delete;
	AnimatedSprite& operator=(const AnimatedSprite&) = delete;

	void setAnimationFrames(const std::vector<sf::IntRect>& _animationFrames);

	void update(const sf::Time& _frameTime);

private:
	sf::Time m_frameTime{ sf::seconds(0.0f) };
	sf::Time m_frameUpdateTime;
	const std::vector <sf::IntRect>* m_animationFrames;
	std::vector <sf::IntRect>::const_iterator m_currentFrame{ m_animationFrames->begin() };

	void moveToNextFrame();
	void setTextureRect(const sf::IntRect& rectangle);
};