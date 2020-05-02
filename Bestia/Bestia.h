#pragma once

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimatedSprite.hpp"

using uint = unsigned int;

constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;

constexpr float VIEW_WIDTH = WINDOW_WIDTH;
constexpr float VIEW_HEIGHT = WINDOW_HEIGHT;

void resizeView(const sf::Window& window, sf::View& view)
{
	const float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}