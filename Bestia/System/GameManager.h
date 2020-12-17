#pragma once

#include <memory>
#include "Menu/MainMenu.h"
#include "Utils/Defs.h"
#include <iostream>
#include "System/GameObject.h"
#include "Scene/Scene.h"
#include "Scenes/MainMenuScene.h"

namespace bestia {
namespace system {

	class GameManager
	{
	public:
		GameManager(const GameManager&) = delete;
		GameManager& operator= (const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		GameManager& operator= (GameManager&&) = delete;
		~GameManager() = default;

		static GameManager& getInstance()
		{
			static GameManager gameManager;
			return gameManager;
		}

		void update()
		{
			switch (m_currentGameState)
			{
			case EGameState::InMenu:
				handleInMenuState();
				break;
			case EGameState::InGame:
				break;
			default:
				break;
			}

			for (const auto& object : GameObject::getGameObjects())
			{
				if (object != nullptr)
					object->update();
			}

			gui::Window::draw(*m_scenePtr);
		}

		void changeState(const EGameState& newGameState)
		{
			if (newGameState != m_currentGameState)
			{
				m_updatePtr.reset(nullptr);
				m_currentGameState = newGameState;
			}
		}

	private:
		GameManager() = default;

		void handleInMenuState()
		{
			//if (m_updatePtr == nullptr)
			if(m_scenePtr == nullptr)
			{
				m_scenePtr = std::make_unique<scene::MainMenuScene>();
				//m_updatePtr = std::make_unique<::bestia::MainMenu>(m_currentGameState);
			}
		}

		EGameState m_currentGameState = EGameState::InMenu;
		std::unique_ptr<GameObject> m_updatePtr = nullptr;
		std::unique_ptr<scene::SceneNew> m_scenePtr = nullptr;
	};

}
}
