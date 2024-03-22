#include "HumanWorker.h"

#include "ImGui/Inc/imgui.h"

#include "TypeIDs.h"

#include "VisualSensor.h"
#include "MovementSensor.h"
#include "MyAIWorld.h"
#include "HumanWorkerStates.h"
#include "HWStratGoHome.h"
#include "HWStratScout.h"
#include "HWStratMine.h"
#include "HumanBase.h"


namespace
{
	float ComputeImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
	{
		float score = 0.0f;
		AgentType entityType = static_cast<AgentType>(record.GetProperty<int>("type"));
		switch (entityType)
		{
		case AgentType::Invalid:
			score = 0.0f;
			break;
		case AgentType::HumanWorker:
			{
				X::Math::Vector2 lastSeenPos = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
				float distance = X::Math::Distance(agent.position, lastSeenPos);
				float distanceScore = std::max(1000.0f - distance, 0.0f);
				score = distanceScore;
			}
			break;
		case AgentType::Mineral:
			{
				X::Math::Vector2 lastSeenPos = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
				float distance = X::Math::Distance(agent.position, lastSeenPos);
				float distanceScore = std::max(1000.0f - distance, 0.0f);
				score = distanceScore;
			}
			break;
		default:
			break;
		}
		return score;
		return 0;
	}
}

HumanWorker::HumanWorker(AI::AIWorld& world)
	:Agent(world, static_cast<uint32_t>(AgentType::HumanWorker))
{
}

void HumanWorker::Load(X::Math::Vector2 spawn)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	position = spawn;
	maxSpeed = 40.0f;

	mStateMachine = std::make_unique<AI::StateMachine<HumanWorker>>();
	mStateMachine->Initialize(this);
	mStateMachine->AddState<Mine>();
	mStateMachine->AddState<Move>();
	mStateMachine->ChangeState(static_cast<int>(HumanWorkerState::Move));

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mSeekBehavior->SetActive(true);
	mSeekBehavior->SetWeight(30.0f);
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();
	mArriveBehavior->SetActive(false);
	mArriveBehavior->SetWeight(30.0f);

	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mPerceptionModule->SetMemorySpan(12.0f);
	mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>();
	mVisualSensor->targetTypes.push_back(AgentType::Mineral);
	mVisualSensor->targetTypes.push_back(AgentType::RobotBase);
	mVisualSensor->targetTypes.push_back(AgentType::RobotFighter);
	mVisualSensor->targetTypes.push_back(AgentType::RobotWorker);
	mVisualSensor->viewRange = 300.0f;
	mMovementSensor = mPerceptionModule->AddSensor<MovementSensor>();
	mMovementSensor->targetType = AgentType::HumanWorker;

	mDecisionModule = std::make_unique<AI::DecisionModule<HumanWorker>>(*this);
	//auto mine = mDecisionModule->AddStrategy<HWStratMine>();
	//auto entities = world->GetEntitiesInRange(X::Math::Circle(position, 9000.0f), static_cast<uint32_t>(AgentType::Mineral));
	//float distance = 3000000.0f;
	//float newDist;
	//X::Math::Vector2 goal;
	//for (auto& mineral : entities)
	//{
	//	newDist = X::Math::DistanceSqr(position, mineral->position);
	//	if (newDist < distance)
	//	{
	//		distance = newDist;
	//		goal = mineral->position;
	//		mineralP = mineral->position;
	//	}
	//}
	//mine->SetTargetDestination(goal);
	auto scout = mDecisionModule->AddStrategy<HWStratScout>();
	X::Math::Vector2 max = map->GetMax();
	scout->SetTargetDestination(X::Math::Vector2(600, 600));
	mDecisionModule->AddStrategy<HWStratGoHome>();

	for (int i = 0; i < mTextureIds.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "scv_%02i.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}
}

void HumanWorker::Unload()
{

}

void HumanWorker::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);

	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
	{
		heading = X::Math::Normalize(velocity);
	}

	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());
	if (position.x < 0.0f)
	{
		position.x = 0.0f;
		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	if (position.x >= screenWidth)
	{
		position.x = screenWidth;
		if (velocity.x > 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		if (velocity.y < 0.0f)
		{
			velocity.y = 0.0f;
		}
	}
	if (position.y >= screenHeight)
	{
		position.y = screenHeight;
		if (velocity.y > 0.0f)
		{
			velocity.y = 0.0f;
		}
	}
	ImGui::Begin("worker");
	ImGui::Text("X: %f", position.x);
	ImGui::SameLine();
	ImGui::Text("  Y: %f", position.y);

	ImGui::Text("X: %f", destination.x);
	ImGui::SameLine();
	ImGui::Text("  Y: %f", destination.y);
	ImGui::Text("Arrive: %s", mArriveBehavior->IsActive() ? "true" : "false");
	ImGui::SameLine();
	ImGui::Text("  Seek: %s", mSeekBehavior->IsActive()? "true" :  "false");
	ImGui::Text("HoldingMinerals: %i", mValue);
	ImGui::Text("BaseMinerals: %i", MyAIWorld::GetInstance()->GetHumanBase()->GetMinerals());
	X::DrawScreenCircle(mineralP, 15.0f, X::Colors::Red);
	ImGui::End();
}

void HumanWorker::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTextureIds.size()) % mTextureIds.size();
	X::DrawSprite(mTextureIds[frame], position);
}

void HumanWorker::ShowDebug(bool debug)
{
	mSeekBehavior->SetDebug(debug);
	mArriveBehavior->SetDebug(debug);
}

void HumanWorker::ChangeState(HumanWorkerState state)
{
	mStateMachine->ChangeState(static_cast<int>(state));
}

void HumanWorker::Dump()
{
	MyAIWorld::GetInstance()->GetHumanBase()->Dump(mValue);
	mValue = 0;
}
