#pragma once

namespace HopEngine
{
	class Scene
	{
	public:
		virtual void Start() = 0;
		virtual void Restart() = 0;
		virtual void Stop() = 0;
	};
}