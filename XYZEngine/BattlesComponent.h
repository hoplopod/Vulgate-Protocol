#pragma once
#include "Component.h"

namespace HopEngine {

	class BattlesComponent : public Component {
	public:
		BattlesComponent(GameObject* gameObject) : Component(gameObject) {};

		void Update(float deltaTime) {};
		void Render() {};

		void setHealthPoints(int newHP) {
			hp = newHP;
		}

		void takeDamage(int damage) {
			hp -= damage;
		}

	protected:
		int hp = 0;
	};

}