#pragma once

#include "Goal.h"
#include "GoalComposite.h"
#include "Strategy.h"

namespace AI
{
	template<class AgentType>
	class DecisionModule
	{
	public:
		using GoalType = Goal<AgentType>;
		using StrategyType = Strategy<AgentType>;

		DecisionModule(AgentType& agent)
			:mAgent(agent)
		{

		}
		
		template<class NewStrategy>
		NewStrategy* AddStrategy()
		{
			static_assert(std::is_base_of_v<StrategyType, NewStrategy>, "DecisionModule: must be of type Strategy");
			auto& newStrategy = mStrategies.emplace_back(std::make_unique<NewStrategy>());
			return static_cast<NewStrategy*>(newStrategy.get());
		}

		void Update()
		{
			//decide what is the best goal at this time
			Arbitrate();
			//process the goal
			if (mCurrentGoal != nullptr)
			{
				mCurrentGoal->Process(mAgent);
				if (mCurrentGoal->GetStatus() == GoalType::Status::Completed
					||mCurrentGoal->GetStatus() == GoalType::Status::Failed)
				{
					mCurrentStrategy = nullptr;
				}
			}
		}
		void Debug()
		{
			if (mCurrentStrategy != nullptr)
			{
				mCurrentStrategy->Debug(mAgent);
				mCurrentGoal->Debug(mAgent);
			}
		}
		StrategyType* GetCurrentStrategy() { return mCurrentStrategy;}

	private:

		void Arbitrate()
		{
			StrategyType* bestStrategy = nullptr;
			float mostDesirable = 0.0f;

			for (auto& strategy : mStrategies)
			{
				float desirability = strategy->CalculateDesirability(mAgent);
				if (desirability > mostDesirable)
				{
					mostDesirable = desirability;
					bestStrategy = strategy.get();
				}
			}

			if (mCurrentStrategy != bestStrategy)
			{
				mCurrentStrategy = bestStrategy;
				if (mCurrentGoal != nullptr)
				{
					mCurrentGoal->Terminate(mAgent);
					mCurrentGoal.reset();
				}
				if (mCurrentStrategy!= nullptr)
				{
					mCurrentGoal = mCurrentStrategy->CreateGoal(mAgent);
				}
			}
		}

		using Strategies = std::vector<std::unique_ptr<StrategyType>>;
		Strategies mStrategies;
		StrategyType* mCurrentStrategy = nullptr;
		std::unique_ptr<GoalType> mCurrentGoal = nullptr;
		AgentType& mAgent;
	};
}