#include "pch.h"
#include "EventBattleSystem.h"

HopEngine::EventBattleSystem* HopEngine::EventBattleSystem::EventBattleSystem::Instance()
{
    static EventBattleSystem EventBattleSystem;
    return &EventBattleSystem;
}

void HopEngine::EventBattleSystem::TriggerEvent(GameObject* gameObject_1, spine::String hitbox_name_1, GameObject* gameObject_2, spine::String hitbox_name_2)
{
    GameObject* pl_object,* en_object;
    spine::String pl_hitbox, en_hitbox;

    if (gameObject_1->GetName() == "player") {
        pl_object = gameObject_1;
        pl_hitbox = hitbox_name_1;

        en_object = gameObject_2;
        en_hitbox = hitbox_name_2;
    }
    else {
        pl_object = gameObject_2;
        pl_hitbox = hitbox_name_2;

        en_object = gameObject_1;
        en_hitbox = hitbox_name_1;
    }

    if (pl_object->GetComponent<PlayerSpineComponent>()->checkPlayerDir() == PlayerDirection::left && pl_hitbox == "blade_hitbox_2") return;
    if (en_object->GetComponent<BaptistSpineComponent>()->checkBaptistDir() == BaptistDirection::left && en_hitbox == "Sword left hitbox") return;

    if (pl_hitbox == "blade_hitbox_2" && en_hitbox == "body hitbox") {
        en_object->GetComponent<EnemyAiComponent>()->setBlock(true);
    }
}
