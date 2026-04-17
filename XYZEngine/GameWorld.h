#pragma once

#include "GameObject.h"
#include "TriggersSystem.h"
#include "SpineTriggersSystem.h"
#include "TimerSystem.h"
#include "SoundSystem.h"

namespace HopEngine
{
	enum class world_end {
		nothing,
		player_death,
		player_win
	};

	class GameWorld
	{
	public:
		static GameWorld* Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();

		GameObject* CreateGameObject();
		GameObject* CreateGameObject(std::string name);
		GameObject* FindGameObject(std::string name);
		void DestroyGameObject(GameObject* gameObject);
		void Clear();

		void Print() const;

		void RequestGameOver() {
			gameOverRequested = true;
		}
		bool checkGameOverRequested() const{
			return gameOverRequested;
		}
		void set_world_end(world_end new_end) {
			end = new_end;
		}
		world_end get_world_end() const {
			return end;
		}
	private:
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		float fixedCounter = 0.f;
		bool gameOverRequested = false;
		world_end end = world_end::nothing;

		std::vector<GameObject*> gameObjects = {};
		std::vector<GameObject*> markedToDestroyGameObjects = {};

		void DestroyGameObjectImmediate(GameObject* gameObject);
	};
}