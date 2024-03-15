#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <ImGui/Inc/imgui.h>

TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;
Path path;
int startX = 5;
int startY = 9;
int endX = 24;
int endY = 12;
auto Manhattan = [](const AI::Node* neighbor, const AI::Node* endNode)->float
{
	float D = 1.0f;
	float dx = abs(neighbor->column - endNode->column);
	float dy = abs(neighbor->row - endNode->row);
	return D * (dx + dy);
};
auto Euclidean = [](const AI::Node* neighbor, const AI::Node* endNode)->float
{
	float D = 1.0f;
	float dx = abs(neighbor->column - endNode->column);
	float dy = abs(neighbor->row - endNode->row);
	return D * sqrt(dx * dx + dy * dy);
};
auto Diagonal = [](const AI::Node* neighbor, const AI::Node* endNode)->float
{
	float D1 = 1.0f;
	float D2 = 1.0f;
	float dx = abs(neighbor->column - endNode->column);
	float dy = abs(neighbor->row - endNode->row);
	return D1 * sqrt(dx + dy) + (D2 - 2 * D1) * std::min(dx, dy);
};
//--------------------------------------------------

void GameInit()
{
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");

	textureId = X::LoadTexture("bird1.png");
	position = { 100.0f, 100.0f };
}

bool GameLoop(float deltaTime)
{
	const float moveSpeed = 200.0f; // pixel per second
	if (X::IsKeyDown(X::Keys::RIGHT))
		position.x += moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::LEFT))
		position.x -= moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::UP))
		position.y -= moveSpeed * deltaTime;
	if (X::IsKeyDown(X::Keys::DOWN))
		position.y += moveSpeed * deltaTime;

	ImGui::Begin("Pathfinding", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		const int columns = tileMap.GetColumns();
		const int rows = tileMap.GetRows();
		ImGui::DragInt("StartX", &startX, 1, 0, columns - 1);
		ImGui::DragInt("StartY", &startY, 1, 0, rows - 1);
		ImGui::DragInt("EndX", &endX, 1, 0, columns - 1);
		ImGui::DragInt("EndY", &endY, 1, 0, rows - 1);
		if (ImGui::Button("Run BFS"))
		{
			path = tileMap.FindPathBFS(startX, startY, endX, endY);
		}
		if (ImGui::Button("Run DFS"))
		{
			path = tileMap.FindPathDFS(startX, startY, endX, endY);
		}
		if (ImGui::Button("Run Dijkstra"))
		{
			path = tileMap.FindPathDijkstra(startX, startY, endX, endY);
		}
		if (ImGui::Button("Run AStar"))
		{
			path = tileMap.FindPathAStar(startX, startY, endX, endY, Manhattan);
		}
		ImGui::Text("Path Size%i", path.size());
	}
	ImGui::End();
	tileMap.Render();

	X::DrawSprite(textureId, position, X::Pivot::TopLeft, X::Flip::Horizontal);
	X::DrawScreenCircle((endX+0.5f) * tileMap.GetTileWidth(), (endY+0.5f) * tileMap.GetTileHeight(), 10.0f, X::Colors::Red);
	
	for (auto pos : path)
	{
		X::DrawScreenCircle(pos, 10.0f, X::Colors::Pink);
	}

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}