#pragma once

#include <XEngine.h>
#include <AI.h>

#include "Mineral.h"

using Path = std::vector<X::Math::Vector2>;

struct Tile
{
	X::TextureId textureId = 0;
	bool isWalkable = false;
};
class MyTileMap
{
public:
	void LoadTiles(const char* fileName);
	void LoadMap(const char* fileName);

	void Update(float deltaTime);
	void Render() const;
	void DebugUI() const;

	bool IsBlocked(int x, int y) const;
	int GetColumns() const { return mColumns; }
	int GetRows() const { return mRows; }
	int GetTileHeight()const { return mTileHeight; }
	int GetTileWidth() const { return mTileWidth; }
	int GetColumn(float y) const{ return int(y/mTileHeight);}
	int GetRow(float x) const{ return int(x / mTileWidth); }
	X::Math::Vector2 GetMax() const { return X::Math::Vector2(mRows*mTileWidth, mColumns * mTileHeight);}

	X::Math::Vector2 GetPixelPosition(int x, int y) const;

	Path FindPathDijkstra(int startX, int startY, int endX, int endY) const;
	Path FindPathAStar(int startX, int startY, int endX, int endY, AI::GetHeuristic heuristic) const;
private:
	std::unique_ptr<AI::GridBasedGraph> mGraph;
	std::vector<int> mMap;
	std::vector<std::unique_ptr<Tile>> mTiles;
	std::vector<std::unique_ptr<Mineral>> mMinerals;
	bool mplace = false;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileHeight = 0;
};