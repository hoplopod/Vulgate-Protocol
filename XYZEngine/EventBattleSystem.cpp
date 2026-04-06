#include "pch.h"
#include "EventBattleSystem.h"

HopEngine::EventBattleSystem* HopEngine::EventBattleSystem::EventBattleSystem::Instance()
{
    static EventBattleSystem EventBattleSystem;
    return &EventBattleSystem;
}

void HopEngine::EventBattleSystem::TriggerEvent(GameObject* gameObject_1, spine::String hitbox_name_1, GameObject* gameObject_2, spine::String hitbox_name_2)
{
    GameObject* pl_object, * en_object;
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

    if ((pl_hitbox == "blade_hitbox_2" || pl_hitbox == "blade_hitbox_1") && en_hitbox == "body hitbox") {
        if (!en_object->GetComponent<PVEComponent>()->getStanned()) en_object->GetComponent<PVEComponent>()->setBlocked(true);
        else en_object->GetComponent<PVEComponent>()->setTakedDamage(true);
    }

    if (pl_hitbox == "body hitbox" && (en_hitbox == "Sword right hitbox" || pl_hitbox == "Sword left hitbox")
        && !pl_object->GetComponent<PVEComponent>()->getBlocked()) pl_object->GetComponent<PVEComponent>()->setTakedDamage(true);

    if ((pl_hitbox == "blade_hitbox_2" || pl_hitbox == "blade_hitbox_1") && (en_hitbox == "Sword right hitbox" || pl_hitbox == "Sword left hitbox"))
        if (en_object->GetComponent<BaptistSpineComponent>()->checkBaptistState() == BaptistState::attack)
            if (!pl_object->GetComponent<PVEComponent>()->getTakedDamage())
                if (pl_object->GetComponent<PlayerSpineComponent>()->checkPlayerState() == PlayerState::attack) {
                    if ((pl_object->GetComponent<PlayerSpineComponent>()->checkBladeState() == BladeState::Open
                        && (en_object->GetComponent<EnemyAiComponent>()->getAttackType() == AttackType::Swing_Up
                            || en_object->GetComponent<EnemyAiComponent>()->getAttackType() == AttackType::Thrust_Up))
                        || (pl_object->GetComponent<PlayerSpineComponent>()->checkBladeState() == BladeState::Close
                            && (en_object->GetComponent<EnemyAiComponent>()->getAttackType() == AttackType::Swing_Down
                                || en_object->GetComponent<EnemyAiComponent>()->getAttackType() == AttackType::Thrust_Down))) en_object->GetComponent<PVEComponent>()->setStanned(true);
                }
                else if (pl_object->GetComponent<PlayerSpineComponent>()->checkPlayerState() == PlayerState::block) pl_object->GetComponent<PVEComponent>()->setBlocked(true);

}
