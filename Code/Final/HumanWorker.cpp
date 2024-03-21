#include "HumanWorker.h"

#include "ImGui/Inc/imgui.h"

#include "TypeIDs.h"

#include "VisualSensor.h"
#include "MovementSensor.h"
#include "MyAIWorld.h"
#include "HumanWorkerStates.h"
#include "HWStratScout.h"


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
	auto scout = mDecisionModule->AddStrategy<HWStratScout>();
	scout->SetTargetDestination(X::Math::Vector2(180.0f,100.0f));
	

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
