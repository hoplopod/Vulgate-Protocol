#include "pch.h"
#include "PVEComponent.h"

HopEngine::PVEComponent::PVEComponent(GameObject* gameObject) : Component(gameObject)
{
}

void HopEngine::PVEComponent::Update(float deltaTime)
{
	if (hp == 0) {
		isDead = true;
		onDeath(this);
	}

	if (TimerSystem::Instance()->checkTimer("block_" + gameObject->GetName()) != TimerState::In_Process) wasBlocked = false;
	if (TimerSystem::Instance()->checkTimer("takedamage_" + gameObject->GetName()) != TimerState::In_Process) wasTakedDamage = false;
	if (TimerSystem::Instance()->checkTimer("stan_" + gameObject->GetName()) != TimerState::In_Process) wasStanned = false;
}

void HopEngine::PVEComponent::Render()
{
}
