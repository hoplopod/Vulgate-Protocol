#pragma once
#include "Component.h"
#include "GameObject.h"

namespace HopEngine {

	class PVEComponent : public Component {
	public:
		PVEComponent(GameObject* gameObject) : Component(gameObject){}

		void setHP(int newHp) { hp = newHp; }
		void HP_minus(int minus) { hp -= minus; }
		void HP_plus(int plus) { hp += plus; }

		void setStamina(int newStamina) { stamina = newStamina; }
		void Stamina_minus(int minus) { stamina -= minus; }
		void Stamina_plus(int plus) { stamina += plus; }

	private:
		int hp = 0;
		int stamina = 0;
	};

}
