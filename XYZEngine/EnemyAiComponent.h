#pragma once

#include "TransformComponent.h"
#include "PVEComponent.h"
#include "PlayerSpineComponent.h"

namespace HopEngine {

	enum class AttackType {
		None,           // нет атаки
		Thrust_Center,  // колюща€ по центру
		Thrust_Up,      // колюща€ сверху
		Thrust_Down,    // колюща€ снизу
		Swing_Up,       // руб€щий удар сверху
		Swing_Down      // руб€щий удар снизу
	};

	class EnemyAiComponent : public Component {
	public:
		EnemyAiComponent(GameObject* gameObject);
		
		void Update(float deltaTime) override;
		void Render() override;

		void SetPurpose(GameObject* gameObject);
		AttackType ChooseAttack();

		float GetHorizontalAxis() const;
		void SetSpeed(float newSpeed);
		float GetSpeed() const;
		AttackType getAttackType() const;
		void setBlock(bool newBlock);
		bool getBlock() const;
		
		float getDir();
	private:
		TransformComponent* enemy_transform;

		TransformComponent* purpose_transform;
		PlayerSpineComponent* pl_spine;

		float horizontalAxis = 0.f;
		float speed = 0;

		float optimalDistance = 580.0f;
		float minSafeDistance = 275.0f;
		float attackRange = 450.0f;
		float closeRange = 350.0f;
		
		bool block = false;

		AttackType at_type = AttackType::None;
	};

	float randomFloat(float min, float max);
}
