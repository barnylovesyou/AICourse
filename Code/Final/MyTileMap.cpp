#include "MyTileMap.h"
using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void MyTileMap::LoadTiles(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}
	std::fstream file(fileName);
	int count = 0;
	int isWalkable = 0;
	std::string buffer;

	file >> buffer;
	file >> count;

	mTiles.clear();
	mTiles.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		file >> buffer;
		file >> isWalkable;

		std::unique_ptr<Tile> tile = std::make_unique<Tile>();
		tile->textureId = X::LoadTexture(buffer.c_str());
		tile->isWalkable = isWalkable == 0;
		mTiles.push_back(std::move(tile));
	}
	file.close();

	mTileWidth = X::GetSpriteWidth(mTiles[0]->textureId);
	mTileHeight = X::GetSpriteHeight(mTiles[0]->textureId);
}

void MyTileMap::LoadMap(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}
	std::fstream file(fileName);
	int columns = 0;
	int rows = 0;
	char tileType;
	std::string buffer;

	file >> buffer;
	file >> columns;
	file >> buffer;
	file >> rows;

	mColumns = columns;
	mRows = rows;

	mMap.resize(columns * rows);
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			file >> tileType;
			int mapIndex = ToIndex(x, y, columns);
			mMap[mapIndex] = tileType - '0';
		}

	}
	file.close();
	mGraph = std::make_unique<GridBasedGraph>();
	mGraph->Initialize(columns, rows);
	auto GetNeighbor = [&](int x, int y) -> Node*
		{
			if (IsBlocked(x, y))
			{
				return nullptr;
			}
			return mGraph->GetNode(x, y);
		};
	//TODO double check this is initialized correctly
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			if (IsBlocked(x, y))
			{
				continue;
			}
			Node* node = mGraph->GetNode(x, y);
			node->neighbors[North] = GetNeighbor(x, y - 1);
			node->neighbors[South] = GetNeighbor(x, y + 1);
			node->neighbors[East] = GetNeighbor(x + 1, y);
			node->neighbors[West] = GetNeighbor(x - 1, y);
		}

	}
}

void MyTileMap::Update(float deltaTime)
{
}

void MyTileMap::Render() const
{
	X::Math::Vector2 position;
	int mapIndex;
	int tileType;
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			mapIndex = ToIndex(x, y, mColumns);
			tileType = mMap[mapIndex];
			X::DrawSprite(mTiles[tileType]->textureId, position, X::Pivot::TopLeft);
			position.x += mTileWidth;
		}
		position.x = 0.0f;
		position.y += mTileHeight;
	}
}
void MyTileMap::DebugUI() const
{
	const Node* node;
	X::Math::Vector2 offset = { 0.5f * mTileWidth ,0.5f * mTileHeight };
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			node = mGraph->GetNode(x, y);
			//Grid display
			const X::Math::Vector2 a = GetPixelPosition(node->column, node->row);
			const X::Math::Vector2 b = GetPixelPosition(node->column + 1, node->row);
			const X::Math::Vector2 c = GetPixelPosition(node->column, node->row + 1);
			X::DrawScreenLine(a - offset, b - offset, X::Colors::Blue);
			X::DrawScreenLine(a - offset, c - offset, X::Colors::Blue);
			//Last search visited nodes display
			if (node->parent != nullptr)
			{
				X::DrawScreenCircle(GetPixelPosition(node->parent->column, node->parent->row), 10.0f, X::Colors::Black);
				X::DrawScreenLine(GetPixelPosition(node->parent->column, node->parent->row), GetPixelPosition(node->column, node->row), X::Colors::Red);
			}
		}
	}
}
bool MyTileMap::IsBlocked(int x, int y) const
{
	if (x >= 0 && x < mColumns &&
		y >= 0 && y < mRows)
	{
		const int index = ToIndex(x, y, mColumns);
		const int tileId = mMap[index];
		if (mTiles[tileId]->isWalkable)
		{
			return false;
		}
	}
	return true;
}

X::Math::Vector2 MyTileMap::GetPixelPosition(int x, int y) const
{
	return {
		(x + 0.5f) * mTileWidth,
		(y + 0.5f) * mTileHeight
	};
}
Path MyTileMap::FindPathDijkstra(int startX, int startY, int endX, int endY)
{
	auto getCost = [](const Node* node, const Node* neighbor)->float
		{
			return 1.0f;
		};
	Path path;
	Dijkstra dijkstra;
	if (dijkstra.Run(*mGraph, startX, startY, endX, endY, getCost))
	{
		const NodeList& closedList = dijkstra.GetClosedList();
		Node* node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
Path MyTileMap::FindPathAStar(int startX, int startY, int endX, int endY, AI::GetHeuristic heuristic)
{
	auto getCost = [](const Node* node, const Node* neighbor)->float
		{
			return 1.0f;
		};
	Path path;
	AStar aStar;
	if (aStar.Run(*mGraph, startX, startY, endX, endY, getCost, heuristic))
	{
		const NodeList& closedList = aStar.GetClosedList();
		Node* node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
// 2D map - 5 columns x 4 rows
// [0][0][0][0][0]
// [0][0][0][0][0]
// [0][0][0][X][0]   X is at (3, 2)
// [0][0][0][0][0]

// Stored as 1D - 5x4 = 20 slots
// [0][0][0][0][0] [0][0][0][0][0] [0][0][0][X][0] [0][0][0][0][0]
//
// index = column + (row * columnCount)
//       = 3 + (2 * 5)
//       = 13