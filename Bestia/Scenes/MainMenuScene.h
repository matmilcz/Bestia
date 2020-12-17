#pragma once

#include "../Scene/Scene.h"
#include "Gui/Button.h"
#include <cassert>

namespace bestia {
namespace scene {

	class MainMenuScene : public SceneNew
	{
	public:
		MainMenuScene()
		{
			assert(m_buttonFont.loadFromFile("Resources/fonts/calibri.ttf"));
			
			layers[ELayer::Gui] = std::make_shared<Layer>();

			createButtons();
		}

	private:
		sf::Font m_buttonFont;

		void createButtons()
		{
			constexpr unsigned numOfButtons = 4;
			std::array<std::string, numOfButtons> buttonStrings = {"NEW GAME", "OPTIONS", "CREDITS", "EXIT"};
			std::array<std::function<void(gui::ButtonNew*)>, numOfButtons> onClickCallbacks = {
				[](gui::ButtonNew* button) {
					LOG("clicked new game\n");
					},
				[](gui::ButtonNew* button) {
					LOG("clicked options\n");
					},
				[](gui::ButtonNew* button) {
					LOG("clicked credits\n");
					},
				[](gui::ButtonNew* button) {
					LOG("clicked exit\n");
					}
			};

			const auto mouseEnterColor = sf::Color{ 10, 20, 70, 180 };
			const auto mouseLeftColor = sf::Color{ 10, 20, 180, 180 };

			auto onMouseEnterCallback = [mouseEnterColor](gui::ButtonNew* button) {
				auto shape = button->getShape();
				shape.setFillColor(mouseEnterColor);
				button->setShape(shape);
			};

			auto onMouseLeftCallback = [mouseLeftColor](gui::ButtonNew* button) {
				auto shape = button->getShape();
				shape.setFillColor(mouseLeftColor);
				button->setShape(shape);
			};

			sf::RectangleShape shape{ sf::Vector2f{250, 70} };
			shape.setFillColor(mouseLeftColor);

			for (unsigned buttonIdx = 0; buttonIdx < numOfButtons; ++buttonIdx)
			{
				auto button = std::make_shared<gui::ButtonNew>();

				button->setShape(shape);
				constexpr float offsetX = 500;
				constexpr float offsetY = 200;
				button->move(sf::Vector2f{ offsetX, static_cast<float>(offsetY + buttonIdx * (50 + button->getShape().getSize().y)) });
				constexpr unsigned characterSize = 26;
				sf::Text text{buttonStrings[buttonIdx], m_buttonFont, characterSize };
				button->setText(text);

				button->onClick = onClickCallbacks[buttonIdx];
				button->onMouseEnter = onMouseEnterCallback;
				button->onMouseLeft = onMouseLeftCallback;

				layers[ELayer::Gui]->objects.push_back(button);
			}
		}
	};

}
}