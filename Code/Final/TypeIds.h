#pragma once

enum class AgentType : uint32_t
{
	Invalid		 = 0,
	HumanBase	 = 1,
	HumanWorker  = 2,
	HumanFighter = 3,
	RobotBase	 = 4,
	RobotWorker  = 5,
	RobotFighter = 6,
	Mineral		 = 7
};
