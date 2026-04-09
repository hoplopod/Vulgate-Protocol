#pragma once
#include "Component.h"
#include "GameObject.h"

#include "TimerSystem.h"

namespace HopEngine {

	class PVEComponent : public Component {
	public:
		PVEComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void setHP(int newHp) { hp = newHp; }
		void HP_minus(int minus) { hp -= minus; }
		void HP_plus(int plus) { hp += plus; }

		void setStamina(int newStamina) { stamina = newStamina; }
		void Stamina_minus(int minus) { stamina -= minus; }
		void Stamina_plus(int plus) { stamina += plus; }

		void setBlocked(bool newBlocked, float time) { wasBlocked = newBlocked; TimerSystem::Instance()->addTimer("block_" + gameObject->GetName(), time); 
		};
		bool getBlocked() const { return wasBlocked; };

		void setTakedDamage(bool newTakedDamage, float time) { wasTakedDamage = newTakedDamage; TimerSystem::Instance()->addTimer("takedamage_" + gameObject->GetName(), time);
		};
		bool getTakedDamage() const { return wasTakedDamage; };

		void setStanned(bool newStanned, float time) { wasStanned = newStanned; TimerSystem::Instance()->addTimer("stan_" + gameObject->GetName(), time);
		};
		bool getStanned() const { return wasStanned; };

	private:
		int hp = 0;
		int stamina = 0;

		//flags
		bool wasBlocked = false;
		bool wasTakedDamage = false;
		bool wasStanned = false;
	};

}
