#include "pch.h"
#include "TimerSystem.h"

namespace HopEngine {

	TimerSystem* TimerSystem::Instance()
	{
		static TimerSystem render;
		return &render;
	}

	void TimerSystem::Update(float deltaTime) {
		for (auto l : allTimers) {
			if (allTimers[l.first] <= 0) continue;
			else allTimers[l.first] -= deltaTime;
		}
	}

	void TimerSystem::addTimer(std::string name, float time)
	{
		allTimers.emplace(name, time);
	}

	const TimerState TimerSystem::checkTimer(std::string name)
	{
		if (allTimers.find(name) == allTimers.end()) return TimerState::Missing;
		if (allTimers[name] > 0.f) return TimerState::In_Process;
		if (allTimers[name] <= 0.f) {
			deleteTimer(name);
			return TimerState::End;
		}
	}

	void TimerSystem::deleteTimer(std::string name)
	{
		allTimers.erase(name);
	}

}


