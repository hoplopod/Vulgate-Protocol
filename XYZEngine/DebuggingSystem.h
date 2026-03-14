#pragma once
#include "Component.h"
#include "RenderSystem.h"

namespace HopEngine
{
	class DebuggingSystem 
	{
	public:
		static DebuggingSystem* Instance();

		void Update();

	private:
		std::vector<sf::RectangleShape> renderShapes;
	};
}