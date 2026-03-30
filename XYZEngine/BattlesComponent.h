#pragma once
#include "Component.h"
#include "GameObject.h"

namespace HopEngine {

	class BattlesComponent : public Component {
	public:
		BattlesComponent(GameObject* gameObject);

		void Update(float deltaTime);
		void Render();

		void setHealthPoints(int newHP);

		void takeDamage(int damage);

		virtual void TriggerEvent(BattlesComponent* component) = 0;

	protected:
		int hp = 0;
	};

}