#pragma once
#include "ResourceSystem.h"
#include "RenderSystem.h"

namespace Roguelike {

	class Logo {
	public:
		Logo() {
			logo_shape.setSize({ 700.f, 350.f });

			logo_shape.setOrigin(logo_shape.getSize() / 2.f);

			auto& window = HopEngine::RenderSystem::Instance()->GetMainWindow();
			sf::Vector2u winSize = window.getSize();

			logo_shape.setPosition(winSize.x / 2.f, winSize.y / 2.f - 200);

			logo_shape.setTexture(HopEngine::ResourceSystem::Instance()->GetTextureCopy("logo"));

		}

		sf::RectangleShape logo_shape;
	};

}
