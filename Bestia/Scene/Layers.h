#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>
#include "Gui/Window.h"

namespace bestia {
namespace scene {

	class BackgroundLayer : public sf::Drawable
	{
	public:
		using object_t = std::shared_ptr<sf::Drawable>;
		std::vector<object_t> objects;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			for (const auto& object : objects)
			{
				gui::Window::draw(*object);
			}
		}
	};

	class FrontLayer : public sf::Drawable
	{
	public:
		using object_t = std::shared_ptr<sf::Drawable>;
		std::vector<object_t> objects;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			for (const auto& object : objects)
			{
				gui::Window::draw(*object);
			}
		}
	};

	class GuiLayer : public sf::Drawable
	{
	public:
		using object_t = std::shared_ptr<sf::Drawable>;
		std::vector<object_t> objects;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			for (const auto& object : objects)
			{
				gui::Window::draw(*object);
			}
		}
	};

}
}