#pragma once
#include <string>
#include <map>

namespace HopEngine {

	enum class TimerState {
		Missing,
		In_Process,
		End
	};

	class TimerSystem {
	public:
		static TimerSystem* Instance();

		void Update(float deltaTime);

		void addTimer(std::string name, float time);
		const TimerState checkTimer(std::string name);

		friend class GameWorld;
	private:
		TimerSystem() {}
		~TimerSystem() {}

		void Reset();

		std::map<std::string, float> allTimers;
		
		void deleteTimer(std::string name);
	};

}