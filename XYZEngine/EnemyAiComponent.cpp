#include "pch.h"
#include "EnemyAiComponent.h"
#include "ColliderComponent.h"
#include "TimerSystem.h"
#include <random>

HopEngine::EnemyAiComponent::EnemyAiComponent(GameObject* gameObject) : Component(gameObject)
{
	enemy_transform = gameObject->GetComponent<TransformComponent>();
}

void HopEngine::EnemyAiComponent::Update(float deltaTime)
{
    float dist = abs(purpose_transform->GetWorldPosition().x - enemy_transform->GetWorldPosition().x);

    horizontalAxis = 0.f;
    at_type = AttackType::None;

    if (dist < attackRange + 0.5f && dist > minSafeDistance) at_type = ChooseAttack();
    else {

        if (dist > optimalDistance + 0.5f) {
            horizontalAxis = (purpose_transform->GetWorldPosition().x > enemy_transform->GetWorldPosition().x) ? 1 : -1;
        }
        else if (dist < minSafeDistance) {
            horizontalAxis = (purpose_transform->GetWorldPosition().x > enemy_transform->GetWorldPosition().x) ? -1 : 1;
        }

        if (gameObject->GetComponent<ColliderComponent>() != nullptr) {
            auto collision = gameObject->GetComponent<ColliderComponent>();
            if (collision->GetCollision()[0] == -1 * horizontalAxis)  horizontalAxis = 0;
        }
        if (TimerSystem::Instance()->checkTimer("enemy_action") == TimerState::In_Process) horizontalAxis = 0;

        enemy_transform->MoveBy(speed * deltaTime * Vector2Df{ horizontalAxis, 0.f });
    }
	
}

void HopEngine::EnemyAiComponent::Render()
{
}

HopEngine::AttackType HopEngine::EnemyAiComponent::ChooseAttack() {
    
    float distance = abs(purpose_transform->GetWorldPosition().x - enemy_transform->GetWorldPosition().x);
    bool isPlayerWeaponHigh = pl_spine->checkBladeState() == BladeState::Open;

    bool isClose = distance <= closeRange;

    if (isClose) {
        bool preferUp = !isPlayerWeaponHigh;
        bool preferDown = isPlayerWeaponHigh;

        float r = randomFloat(0.0f, 1.0f);
        if (r < 0.65f) {
            return preferUp ? AttackType::Swing_Up : AttackType::Swing_Down;
        }
        else {
            return preferUp ? AttackType::Swing_Down : AttackType::Swing_Up;
        }
    }
    else {
        float r = randomFloat(0.0f, 1.0f);
        if (r < 0.35f) {
            return AttackType::Thrust_Center;
        }

        bool preferUp = !isPlayerWeaponHigh; 
        bool preferDown = isPlayerWeaponHigh;

        float subR = randomFloat(0.0f, 1.0f);
        if (subR < 0.7f) {
            return preferUp ? AttackType::Thrust_Up : AttackType::Thrust_Down;
        }
        else {
            return preferUp ? AttackType::Thrust_Down : AttackType::Thrust_Up;
        }
    }
}

float HopEngine::randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

void HopEngine::EnemyAiComponent::SetPurpose(GameObject* gameObject)
{
	purpose_transform = gameObject->GetComponent<TransformComponent>();
    pl_spine = gameObject->GetComponent<PlayerSpineComponent>();
}

float HopEngine::EnemyAiComponent::GetHorizontalAxis() const
{
	return horizontalAxis;
}

void HopEngine::EnemyAiComponent::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float HopEngine::EnemyAiComponent::GetSpeed() const
{
	return speed;
}

HopEngine::AttackType HopEngine::EnemyAiComponent::getAttackType() const
{
	return at_type;
}

float HopEngine::EnemyAiComponent::getDir()
{
    if (purpose_transform->GetWorldPosition().x < enemy_transform->GetWorldPosition().x) return -1.0f;
    else return 1.0f;
}
