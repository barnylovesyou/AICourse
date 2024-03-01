#include <XEngine.h> 
#include <ImGui/Inc/imgui.h>
#include "AI.h"
#include "Scv.h"
#include "Mineral.h"
#include "Raven.h"

using namespace AI;
//--------------------------------------------------
AIWorld aiWorld;
std::vector<std::unique_ptr<SCV>> scvAgents;
std::vector<std::unique_ptr<Raven>> ravenAgents;
std::vector<std::unique_ptr<Mineral>> minerals;
X::Math::Vector2 destination = X::Math::Vector2::Zero();

bool showDebug = false;
bool useSeek = false;
float seekWeight = 1.0f;
bool useFlee = false;
float fleeWeight = 1.0f;
bool useArrive = false;
float arriveWeight = 1.0f;
bool useWander = false;
float wanderWeight = 1.0f;
float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
bool usePursuit = false;
float pursuitWeight = 1.0f;
bool useSeperation = false;
float seperationWeight = 1.0f;
float forceMultiplier = 10.0f;
bool useAlignment = false;
float alignmentWeight = 1.0f;
bool useCohesion = false;
float cohesionWeight = 1.0f;

float radius = 50.0f;

float viewRange = 300.0f;
float viewAngle = 45.0f;
float detectionSpeed = 45.0f;

void SpawnAgent()
{
	auto& agent = scvAgents.emplace_back(std::make_unique<SCV>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();
	agent->position = X::RandomVector2({ 100.0f, 100.0f },
		{ screenWidth - 100.0f, screenHeight - 100.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
	agent->SetSeek(useSeek);
	agent->SetFlee(useFlee);
	agent->SetArrive(useArrive);
	agent->SetWander(useWander);
	agent->SetPursuit(usePursuit);
	agent->SetSeperation(useSeperation);
	agent->SetAlignment(useAlignment);
	agent->SetCohesion(useCohesion);

	agent->SetSeekWeight(seekWeight);
	agent->SetFleeWeight(fleeWeight);
	agent->SetArriveWeight(arriveWeight);
	agent->SetWanderWeight(wanderWeight);
	agent->SetPursuitWeight(pursuitWeight);
	agent->SetSeperationWeight(seperationWeight);
	agent->SetAlignmentWeight(alignmentWeight);
	agent->SetCohesionWeight(cohesionWeight);
}
void KillAgent()
{
	if (!scvAgents.empty())
	{
		auto& agent = scvAgents.back();
		agent->Unload();
		agent.reset();
		scvAgents.pop_back();
	}
}
void SpawnRaven()
{
	auto& agent = ravenAgents.emplace_back(std::make_unique<Raven>(aiWorld));
	agent->Load();

	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();
	agent->position = X::RandomVector2({ 100.0f, 100.0f },
		{ screenWidth - 100.0f, screenHeight - 100.0f });
	agent->destination = destination;
	agent->radius = radius;
	agent->ShowDebug(showDebug);
}
void KillRaven()
{
	if (!ravenAgents.empty())
	{
		auto& agent = ravenAgents.back();
		agent->Unload();
		agent.reset();
		ravenAgents.pop_back();
	}
}

void GameInit()
{
	aiWorld.Initialize();
	for (uint32_t i = 0; i < 10; ++i)
	{
		auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(aiWorld));
		mineral->Initialize();
	}

	aiWorld.AddObstacle({ 230.0f, 300.0f, 50.0f });

	X::Math::Vector2 topLeft(500.0f, 100.0f);
	X::Math::Vector2 topRight(600.0f, 100.0f);
	X::Math::Vector2 bottomLeft(500.0f, 600.0f);
	X::Math::Vector2 bottomRight(600.0f, 600.0f);
	aiWorld.AddWall({ topLeft, topRight });
	aiWorld.AddWall({ topRight, bottomRight });
	aiWorld.AddWall({ bottomLeft, bottomRight });
	aiWorld.AddWall({ bottomLeft, topLeft });
}

bool GameLoop(float deltaTime)
{
	deltaTime = (deltaTime > 1) ? 0 : deltaTime;

	ImGui::Begin("Steering", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::Button("SpawnAgent"))
		{
			SpawnAgent();
		}
		ImGui::SameLine();
		if (ImGui::Button("SpawnRaven"))
		{
			SpawnRaven();
		}
		if (ImGui::Button("KillAgent"))
		{
			KillAgent();
		}
		ImGui::SameLine();
		if (ImGui::Button("KillRaven"))
		{
			KillRaven();
		}
		if (ImGui::Checkbox("ShowDebug", &showDebug))
		{
			for (auto& agent : scvAgents)
			{
				agent->ShowDebug(showDebug);
			}
			for (auto& agent : ravenAgents)
			{
				agent->ShowDebug(showDebug);
			}
		}
		if (ImGui::Checkbox("Seek", &useSeek))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeek(useSeek);
			}
		}
		if (useSeek)
		{
			ImGui::SameLine();
			ImGui::DragFloat("SeekWeight", &seekWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::Checkbox("Flee", &useFlee))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetFlee(useFlee);
			}
		}
		if (useFlee)
		{
			ImGui::SameLine();
			ImGui::DragFloat("FleeWeight", &fleeWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::Checkbox("Arrive", &useArrive))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetArrive(useArrive);
			}
		}
		if (useArrive)
		{
			ImGui::SameLine();
			ImGui::DragFloat("ArriveWeight", &arriveWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::Checkbox("Wander", &useWander))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetWander(useWander);
			}
		}
		if (useWander)
		{
			ImGui::SameLine();
			ImGui::DragFloat("WanderWeight", &wanderWeight, 0.1f, 0.1f, 5.0f);
			if (ImGui::CollapsingHeader("WanderSettings", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::DragFloat("WJitter", &wanderJitter, 0.1f, 0.1f, 10.0f);
				ImGui::DragFloat("WRadius", &wanderRadius, 0.1f, 0.1f, 100.0f);
				ImGui::DragFloat("WDistance", &wanderDistance, 0.1f, 0.1f, 500.0f);
			}
		}
		if (ImGui::Checkbox("Pursuit", &usePursuit))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetPursuit(usePursuit);
			}
		}
		if (usePursuit)
		{
			ImGui::SameLine();
			ImGui::DragFloat("PursuitWeight", &pursuitWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::Checkbox("Seperation", &useSeperation))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetSeperation(useSeperation);
			}
		}
		if (useSeperation)
		{
			ImGui::SameLine();
			ImGui::DragFloat("SeperationWeight", &seperationWeight, 0.1f, 0.1f, 5.0f);
			if (ImGui::DragFloat("Radius", &radius))
			{
				for (auto& agent : scvAgents)
				{
					agent->radius = radius;
				}
			}
			ImGui::DragFloat("ForceMultiplier", &forceMultiplier, 0.1f, 5.0f, 2000.0f);
		}
		if (ImGui::Checkbox("Alignment", &useAlignment))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetAlignment(useAlignment);
			}
		}
		if (useAlignment)
		{
			ImGui::SameLine();
			ImGui::DragFloat("AlignmentWeight", &alignmentWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::Checkbox("Cohesion", &useCohesion))
		{
			for (auto& agent : scvAgents)
			{
				agent->SetCohesion(useCohesion);
			}
		}
		if (useCohesion)
		{
			ImGui::SameLine();
			ImGui::DragFloat("CohesionWeight", &cohesionWeight, 0.1f, 0.1f, 5.0f);
		}
		if (ImGui::CollapsingHeader("VisualSensor", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat("ViewRange", &viewRange, 1.0f, 100.0f, 1000.0f);
			ImGui::DragFloat("ViewAngle", &viewAngle, 1.0f, 1.0f, 360.0f);
		}
		if (ImGui::CollapsingHeader("MovementSensor", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat("DetectionSpeed", &detectionSpeed, 1.0f, 1.0f, 100.0f);
		}
	}
	ImGui::End();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());
		destination = { mouseX, mouseY };

		for (auto& agent : scvAgents)
		{
			agent->destination = destination;
		}
		for (auto& agent : ravenAgents)
		{
			agent->SetTargetDestination(destination);
		}
	}

	aiWorld.Update();

	for (auto& agent : scvAgents)
	{
		EntityPtrs neighbors = aiWorld.GetEntitiesInRange({ agent->position, 500.0f }, 0);
		agent->neighbors.clear();
		for (auto& n : neighbors)
		{
			if (n != agent.get())
			{
				agent->neighbors.push_back(static_cast<Agent*>(n));
			}
		}
	}

	for (auto& agent : scvAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : ravenAgents)
	{
		agent->Update(deltaTime);
	}
	for (auto& agent : scvAgents)
	{
		agent->Render();
	}
	for (auto& agent : ravenAgents)
	{
		agent->Render();
	}
	for (auto& mineral : minerals)
	{
		mineral->Render();
	}

	const AIWorld::Obstacles& obstacles = aiWorld.GetObstacles();
	for (const X::Math::Circle& obstacle : obstacles)
	{
		X::DrawScreenCircle(obstacle.center, obstacle.radius, X::Colors::Gray);
	}

	const AIWorld::Walls& walls = aiWorld.GetWalls();
	for (const X::Math::LineSegment& wall : walls)
	{
		X::DrawScreenLine(wall.from, wall.to, X::Colors::Gray);
	}

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	for (auto& agent : scvAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& agent : ravenAgents)
	{
		agent->Unload();
		agent.reset();
	}
	for (auto& mineral : minerals)
	{
		mineral.reset();
	}
	scvAgents.clear();
	ravenAgents.clear();
	minerals.clear();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Perception");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}