//#pragma once
//
//#include "SteeringBehaviour.h"
//
//namespace AI
//{
//	class SteeringModule final
//	{
//	public:
//		SteeringModule(Agent& agent);
//
//		X::Math::Vector2 Calculate();
//
//		template<class NewBehavior>
//		NewBehavior* AddBehavior()
//		{
//			static_assert(std::is_base_of_v<SteeringBehavior, NewBehavior>,
//				"SteeringModule: can only add type SteeringBehavior");
//			auto& newBehavior = newBehaviors.emplace_back(std::make_unique<NewBehavior>());
//			retirm static_cast<NewBehavior*>(newBehavior.get());
//		}
//
//	private:
//		Agent& agent;
//		std::vector<std::unique_ptr<SteeringBehavior>> mBehaviors;
//	};
//}