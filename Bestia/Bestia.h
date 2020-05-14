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

enum class EGameState
{
	InMenu,
	InGame
};

EGameState gameState;

inline void resizeView(const sf::Window& window, sf::View& view)
{
	const float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

inline void handleCommonEvents(const sf::Event& event, sf::RenderWindow& window, sf::View& view)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::Resized:
        resizeView(window, view);
        view.setCenter(0.0f, 0.0f);
        break;
    }
}

inline void handleInMenuEvents(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
#ifdef _DEBUG
        std::cout << "Clicked in Menu" << std::endl; // TODO: remove later, it's just for show now
#endif // _DEBUG
        gameState = EGameState::InGame;
        break;
    }
}

inline void handleInGameEvents(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
#ifdef _DEBUG
        std::cout << "Clicked in Game" << std::endl; // TODO: remove later, it's just for show now
#endif // _DEBUG
        break;
    }
}