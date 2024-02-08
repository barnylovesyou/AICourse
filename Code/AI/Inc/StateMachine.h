#pragma once

namespace AI
{
	template<class AgentType>
	class StateMachine final
	{
	public:
		StateMachine() = default;
		void Initialize(AgentType* agent)
		{
			mAgent = agent;
		}
		void Terminate()
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->Exit(*mAgent);
			}
			mStates.clear();
			mCurrentState = nullptr;
			mAgent = nullptr;
		}
		template<class NewState>
		void AddState()
		{
			static_assert(std::is_base_of_v<State<AgentType>, NewState>, "StateMachine can only add states of type agenttype");
			mStates.push_back(std::make_unique<NewState>());
		}

		void Update(float deltaTime)
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->Update(*mAgent, deltaTime);
			}
		}

		void ChangeState(int index)
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->Exit(*mAgent);
			}
			mCurrentState = mStates[index].get();
			mCurrentState->Enter(*mAgent);
			mCurrentIndex = index;
		}

		void DebugUI()
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->DebugUI(*mAgent);
			}
		}
		int GetCurrentStateAsEnumValue() { return mCurrentIndex; }
	private:
		AgentType* mAgent = nullptr;
		State<AgentType>* mCurrentState = nullptr;
		int mCurrentIndex = 0;
		std::vector<std::unique_ptr<State<AgentType>>> mStates;
	};
}