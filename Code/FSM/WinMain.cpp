#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>

//SpaceShip Bossfight States: Shoot, Dodge, LockMissile, Call Allies and Heal
#include "Miner.h"
#include "GameManager.h"
//--------------------------------------------------
Miner miner;
void GameInit()
{
	miner.Initialize();
	GameManager::staticIntialize();
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		miner.Update(deltaTime);
	}
	ImGui::Begin("FSM", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		miner.DebugUI();
	}
	ImGui::End();

	GameManager::Get()->Update();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	miner.Terminate();
	GameManager::staticIntialize();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("FSM");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}