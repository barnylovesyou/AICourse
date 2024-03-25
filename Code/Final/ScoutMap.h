#pragma once
#include <XEngine.h>
#include <AI.h>

struct Sector
{
	Sector(int column, int row)
	{
		trColumn = column;
		trRow = row;
	}
	~Sector() = default;
	void Search(int column, int row)
	{
		row -= trRow;
		column -= trColumn;
		if (!explored[row * 5 + column])
		{
			explored[row * 5 + column] = true;
			exploreCount++;
		}
	}
	float PercentSearched()
	{
		float searched = 0;
		for (bool b : explored)
		{
			if (b)
			{
				searched++;
			}
		}
		return searched / 25;
	}
	X::Math::Vector2 GetCenter()
	{
		return X::Math::Vector2(32 * (2 + 0.5f + trColumn), 32 * (2 + 0.5f + trRow));
	}
	std::vector<X::Math::Vector2> GetUnkown()
	{
		std::vector<X::Math::Vector2> unkown;
		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 5; ++c)
			{
				if (!explored[r * 5 + c])
				{
					unkown.push_back(X::Math::Vector2(32*(c+0.5f+trColumn), 32*(r+0.5f+trRow)));
				}
			}
		}
		return unkown;
	}
	bool FullyExplored() { return exploreCount >= 25;}
	bool GetCenterExplored() {return explored[12];}
	bool Inside(int c, int r) {

		return (r >= trRow && r < trRow+5 && c >= trColumn && c < trColumn + 5);
	}
	bool currentlyScouted = false;
	int trRow;
	int trColumn;
	int exploreCount = 0;
	bool explored[25] = { false,false,false,false,false, false,false,false,false,false, false,false,false,false,false, false,false,false,false,false, false,false,false,false,false};
};
class ScoutMap
{
public:
	ScoutMap(X::Math::Vector2 start);
	Sector* GetHighestWeightSector(X::Math::Vector2 loc);
	void Search(X::Math::Vector2 loc, float radius);
	float GetTotalDiscovery();
	Sector* GetSector(float x, float y);
private:
	X::Math::Vector2 mStart;
	std::vector<std::unique_ptr<Sector>> mSectors;
};