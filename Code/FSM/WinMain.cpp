#include <XEngine.h> // <> for external includes, "" for internal includes
#include "ImGuiAdditions.h"
#include "SimsGameManager.h"
//--------------------------------------------------
void GameInit()
{
	SimsGameManager::StaticInitialize();
}

bool GameLoop(float deltaTime)
{
	SimsGameManager::Get()->Update(deltaTime);
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
	}
	ImGui::Begin("FSM", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{		
		SimsGameManager::Get()->DebugUI();
		//MyGui::TestColors();
	}
	ImGui::End();


	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	SimsGameManager::StaticTerminate();
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