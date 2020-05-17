#pragma once

namespace bestia {

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
}