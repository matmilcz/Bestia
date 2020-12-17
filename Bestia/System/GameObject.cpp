#include "GameObject.h"
#include "Utils/Log.h"

namespace bestia {
namespace system {

	std::vector<IGameObject*> GameObject::m_gameObjects;
	uint32_t GameObject::m_numOfGameObjects = 0;

	GameObject::GameObject()
	{
		registerGameObject();
	}

	GameObject::~GameObject()
	{
		deregisterGameObject();
	}

	const std::vector<IGameObject*>& GameObject::getGameObjects()
	{
		return m_gameObjects;
	}

	void GameObject::registerGameObject()
	{
		LOG("Register object: " << this << '\n');

		if (m_numOfGameObjects < m_gameObjects.size())
		{
			auto& gameObjectIter = std::find(m_gameObjects.begin(), m_gameObjects.end(), nullptr);
			*gameObjectIter = this;
		}
		else
		{
			m_gameObjects.push_back(this);
		}

		++m_numOfGameObjects;
	}

	void GameObject::deregisterGameObject()
	{
		LOG("Deregister object: " << this << '\n');

		auto& gameObjectIter = std::find(m_gameObjects.begin(), m_gameObjects.end(), this);
		if (gameObjectIter != m_gameObjects.end())
		{
			*gameObjectIter = nullptr;
			--m_numOfGameObjects;
		}
	}

}
}