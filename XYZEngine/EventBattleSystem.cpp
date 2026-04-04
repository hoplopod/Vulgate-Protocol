#include "pch.h"
#include "EventBattleSystem.h"

HopEngine::EventBattleSystem* HopEngine::EventBattleSystem::EventBattleSystem::Instance()
{
    static EventBattleSystem EventBattleSystem;
    return &EventBattleSystem;
}

void HopEngine::EventBattleSystem::TriggerEvent(GameObject* gameObject_1, std::string hitbox_name_1, GameObject* gameObject_2, std::string hitbox_name_2)
{

}
