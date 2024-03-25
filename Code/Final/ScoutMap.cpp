#include "ScoutMap.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"

ScoutMap::ScoutMap(X::Math::Vector2 start)
{
	for (int r = 0; r < 9; ++r)
	{
		for (int c = 0; c < 16; ++c)
		{
			mSectors.push_back(std::make_unique<Sector>(c*5, r*5));
		}
	}
	std::sort(mSectors.begin(), mSectors.end(), [&](const std::unique_ptr<Sector>& a, const std::unique_ptr<Sector>& b) {
		return (X::Math::MagnitudeSqr(start - a->GetCenter()) < X::Math::MagnitudeSqr(start - b->GetCenter()));
		});
	for (bool& b : mSectors.back()->explored)
	{
		b = true;
	}
	mSectors.back()->exploreCount = 25;
}

Sector* ScoutMap::GetHighestWeightSector(X::Math::Vector2 loc)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	//Lambda ignored a if the location is inside of it OR if it is already being scouted OR if a and not b is already sufficiently scouted it is ignored. Then if b is significantly scouted and a isnt OR b is currently scouted we ignore b. Then we do a distance comparison.
	return std::min_element(mSectors.begin(), mSectors.end(), [&](const std::unique_ptr<Sector>& a, const std::unique_ptr<Sector>& b) {
		return (a->Inside(map->GetColumn(loc.x), map->GetRow(loc.y)) || a->currentlyScouted ||( a->PercentSearched() > 0.8f && !(b->PercentSearched() > 0.8f)))  ?
			false : 
			(b->PercentSearched() > 0.8f && !(a->PercentSearched() > 0.8f )||b->currentlyScouted ||b->Inside(map->GetColumn(loc.x), map->GetRow(loc.y)))?
			true:
			X::Math::MagnitudeSqr(loc - a->GetCenter()) < X::Math::MagnitudeSqr(loc - b->GetCenter());
		})->get();
}

Sector* ScoutMap::GetSector(float x, float y)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	for (auto& s : mSectors)
	{
		if (s->Inside(map->GetColumn(x), map->GetRow(y)))
		{
			return s.get();
		}
	}
}

void ScoutMap::Search(X::Math::Vector2 loc, float radius)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
    float tileSize = 32.0f;
    int tileCheckRange = (radius/32)+1;
    float radiusSqr = radius * radius;
	X::Math::LineSegment line;

	//Creates a min and max r/c for vision text square
	int startR = map->GetRow(loc.y)-tileCheckRange;
	startR = (startR >= 0) ? startR : 0;
	int endR = map->GetRow(loc.y) + tileCheckRange;
	endR = (endR < 45) ? endR : 0;
	int startC = map->GetColumn(loc.x) - tileCheckRange;
	startC = (startC >= 0) ? startC : 0;
	int endC = map->GetColumn(loc.x) + tileCheckRange;
	endC = (endC < 45) ? endC : 0;

    for (int r = startR; r <= endR; ++r) 
	{
        for (int c = startC; c <= endC; ++c) 
		{
			//Tile is within vision radius
			if (X::Math::DistanceSqr(loc, map->GetPixelPosition(c, r)) < radiusSqr)
			{
				//Can See Tile
				line = X::Math::LineSegment(loc, map->GetPixelPosition(c, r));
				if (world->HasLineOfSight(line));
				{
					//Find Sector and search the node
					auto it = std::find_if(mSectors.begin(), mSectors.end(), [&](const std::unique_ptr<Sector>& sector) {
						return sector->Inside(c, r);
						});
					it->get()->Search(c, r);
				}
			}
        }
    }
}
float ScoutMap::GetTotalDiscovery()
{
	float discovery = 0.0f;
	for (auto& s : mSectors)
	{
		discovery += s->PercentSearched();
	}
	return discovery/mSectors.size();
}