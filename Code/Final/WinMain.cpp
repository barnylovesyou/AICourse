#include <XEngine.h> 
#include <ImGui/Inc/imgui.h>
#include "AI.h"
#include "MyAIWorld.h"
#include "TypeIds.h"

using namespace AI;
//--------------------------------------------------

void GameInit()
{
	MyAIWorld::StaticInitialize();
}

bool GameLoop(float deltaTime)
{
	deltaTime = (deltaTime > 1) ? 0 : deltaTime;
	MyAIWorld::GetInstance()->Update(deltaTime);
	MyAIWorld::GetInstance()->Render();
	MyAIWorld::GetInstance()->DebugUI();


	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	MyAIWorld::StaticTerminate();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Final");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}