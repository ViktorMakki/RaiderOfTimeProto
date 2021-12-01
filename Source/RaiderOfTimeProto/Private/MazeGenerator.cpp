// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

#include <vector>

class Door
{
public:
	FIntPoint location;

	void Draw(TArray<FTileArray>& map, int32 recursionLevel) const
	{
		map[location.X].tiles[location.Y].tile = MazeTileType::PATH;
		map[location.X].tiles[location.Y].recursionLevel = recursionLevel;
	}
};

class Wall
{
public:
	FIntPoint start, end;

	void Draw(TArray<FTileArray>& map, int32 recursionLevel) const
	{
		DrawWalls(map, start, end, recursionLevel);
	}

	int32 Size() const 
	{
		return start.X < end.X ? end.X - start.X : end.Y - start.Y;
	}

	FIntPoint GetRandomLocation() const
	{		
		if (start.X == end.X) {
			return { start.X, FMath::RandRange(start.Y, end.Y) };
		}
		if (start.Y == end.Y) {
			return {FMath::RandRange(start.X , end.X), start.Y};
		}
		return start;
	}

private:
	static void DrawWalls(TArray<FTileArray>& map, const FIntPoint& start, const FIntPoint& end, int32 recursionLevel)
	{
		if (start.X == end.X)
			DrawWallsVertical(map, start.X, start.Y, end.Y, recursionLevel);
		if (start.Y == end.Y)
			DrawWallsHorizontal(map, start.Y, start.X, end.X, recursionLevel);
	}

	static void DrawWallsVertical(TArray<FTileArray>& map, int32 x, int32 yStart, int32 yEnd, int32 recursionLevel)
	{
		for (int32 y = yStart; y <= yEnd; y++) {
			map[x].tiles[y].tile = MazeTileType::WALL;
			map[x].tiles[y].recursionLevel = recursionLevel;
		}
	}

	static void DrawWallsHorizontal(TArray<FTileArray>& map, int32 y, int32 xStart, int32 xEnd, int32 recursionLevel)
	{		
		for (int32 x = xStart; x <= xEnd; x++) {
			map[x].tiles[y].tile = MazeTileType::WALL;
			map[x].tiles[y].recursionLevel = recursionLevel;
		}
	}
};

class Chamber 
{
public:
	FIntPoint leftBottom, rightTop;
	int32 Width() const 
	{
		return rightTop.X - leftBottom.X;
	}

	int32 Height() const 
	{
		return rightTop.Y - leftBottom.Y;
	}
};

static TArray<FTileArray> CreateBaseMap(int32 width, int32 height)
{
	TArray<FTileArray> result;
	for (int32 x = 0; x < width; x++) {		
		result.Add({});
		for (int32 y = 0; y < height; y++) {
			result[x].tiles.Add({});
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
				result[x].tiles[y].tile = MazeTileType::WALL;
				result[x].tiles[y].recursionLevel = 0;
			}
			else {
				result[x].tiles[y].tile = MazeTileType::PATH;
				result[x].tiles[y].recursionLevel = 0;
			}
		}	
	}
	return result;
}

static bool IsHorizontal(const Chamber& chamber) 
{
	int32 width = chamber.Width();
	int32 height = chamber.Height();

	if (width > height)
		return true;
	if (width < height)
		return false;
	return FMath::RandBool();
}

static bool IsHorizontal(const Wall& wall) 
{
	if (wall.start.X != wall.end.X)
		return true;
	return false;
}

//returns the wall that splitted the chamber
static Wall CreateVerticalSplitWall(const Chamber& chamber) 
{	
	int32 randomStart = chamber.Width() > 7 ? 3 : 1;
	//Walls can be on every second place to avoid blocking doors
	int32 splitX = FMath::RandRange(randomStart, (chamber.Width() - randomStart)/2);
	int32 x = chamber.leftBottom.X + (2 * splitX);
	return { { x, chamber.leftBottom.Y}, {x, chamber.rightTop.Y} };
}

//returns the wall that splitted the chamber
static Wall CreateHorizontalSplitWall(const Chamber& chamber)
{
	int32 randomStart = chamber.Width() > 7 ? 3 : 1;
	//Walls can be on every second place to avoid blocking doors
	int32 splitY = FMath::RandRange(randomStart, (chamber.Height() - randomStart) / 2);
	int32 y = chamber.leftBottom.Y + (2 * splitY);
	return { { chamber.leftBottom.X, y}, {chamber.rightTop.X, y} };
}

static Door CreateDoorOnWall(const Wall& wall) 
{
	int32 min = wall.Size() > 4 ? 1 : 0;
	int32 max = (wall.Size() - 1) / 2;
	int32 rand = FMath::RandRange(min, max) * 2;

	if (IsHorizontal(wall)) {
		int32 doorX = rand + 1 + wall.start.X;
		return { {doorX, wall.start.Y} };
	}
	int32 doorY = rand + 1 + wall.start.Y;
	return { {wall.start.X, doorY} };
}

static void SplitChamber(TArray<FTileArray>& map, const Chamber& chamber, int32 recursionLevel) 
{
	if (chamber.Width() < 3 && chamber.Height() < 3)
		return;

	recursionLevel++;

	Wall splitWall;
	bool isHorizontal = IsHorizontal(chamber);

	if (isHorizontal) {
		splitWall = CreateVerticalSplitWall(chamber);
	}
	else {
		splitWall = CreateHorizontalSplitWall(chamber);
	}
	splitWall.Draw(map, recursionLevel);


	const Door door = CreateDoorOnWall(splitWall);

	door.Draw(map, recursionLevel);

	Chamber splitChamber1, splitChamber2;

	splitChamber1 = { chamber.leftBottom, splitWall.end };
	splitChamber2 = { splitWall.start, chamber.rightTop };

	SplitChamber(map, splitChamber1, recursionLevel);
	SplitChamber(map, splitChamber2, recursionLevel);
}

TArray<FTileArray> UMazeGenerator::GenerateMaze(const FMazeGeneratorData& data)
{
	TArray<FTileArray> result = CreateBaseMap(data.width, data.height);

	Chamber firstChamber;
	firstChamber.leftBottom = { 0, 0 };
	firstChamber.rightTop = { data.width - 1, data.height - 1 };
	SplitChamber(result, firstChamber, 0);
	return result;
}
