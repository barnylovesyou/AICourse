#include "HumanWorker.h"

#include "ImGui/Inc/imgui.h"

#include "TypeIDs.h"

#include "HWVisualSensor.h"
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
	maxSpeed = 20.0f;

	mStateMachine = std::make_unique<AI::StateMachine<HumanWorker>>();
	mStateMachine->Initialize(this);
	mStateMachine->AddState<HWMine>();
	mStateMachine->AddState<HWGoHome>();
	mStateMachine->AddState<HWScout>();
	mStateMachine->ChangeState(static_cast<uint32_t>(HumanWorkerState::GoHome));

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mSeekBehavior->SetActive(true);
	mSeekBehavior->SetWeight(300.0f);
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();
	mArriveBehavior->SetActive(false);
	mArriveBehavior->SetWeight(300.0f);

	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mPerceptionModule->SetMemorySpan(12.0f);
	mVisualSensor = mPerceptionModule->AddSensor<HWVisualSensor>();
	mVisualSensor->targetTypes.push_back(AgentType::Mineral);
	mVisualSensor->targetTypes.push_back(AgentType::RobotBase);
	mVisualSensor->targetTypes.push_back(AgentType::RobotFighter);
	mVisualSensor->targetTypes.push_back(AgentType::RobotWorker);
	mVisualSensor->viewRange = mVisionRadius;

	mDecisionModule = std::make_unique<AI::DecisionModule<HumanWorker>>(*this);
	auto scout = mDecisionModule->AddStrategy<HWStratScout>();
	mDecisionModule->AddStrategy<HWStratGoHome>();
	mDecisionModule->AddStrategy<HWStratMine>();

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
	mPerceptionModule->Update(deltaTime);
	mDecisionModule->Update();
	const X::Math::Vector2 force = mSteeringModule->Calculate();
	const X::Math::Vector2 acceleration = force / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

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
	MyAIWorld::GetInstance()->GetHumanBase()->Scout(position, mVisionRadius);
	ImGui::Begin("worker");
	ImGui::Text("X: %f", position.x);
	ImGui::SameLine();
	ImGui::Text("  Y: %f", position.y);
	ImGui::End();
}

void HumanWorker::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTextureIds.size()) % mTextureIds.size();
	X::DrawSprite(mTextureIds[frame], position);
}

void HumanWorker::Debug()
{
	mDecisionModule->Debug();
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
