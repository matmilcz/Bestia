#pragma once

#include "Layers.h"

namespace bestia {
namespace scene {

	class Scene : public sf::Drawable
	{
	public:
		Scene() = default;
		Scene(std::shared_ptr<BackgroundLayer> _background,
			  std::shared_ptr<FrontLayer> _front,
			  std::shared_ptr<GuiLayer> _gui) :
			background(_background), 
			front(_front), 
			gui(_gui)
		{}
		~Scene() = default;

		std::shared_ptr<BackgroundLayer> background = nullptr;
		std::shared_ptr<FrontLayer> front = nullptr;
		std::shared_ptr<GuiLayer> gui = nullptr;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			if (background)
			{
				gui::Window::draw(*background);
			}

			if (front)
			{
				gui::Window::draw(*front);
			}

			if (gui)
			{
				gui::Window::draw(*gui);
			}
		}
	};

}
}