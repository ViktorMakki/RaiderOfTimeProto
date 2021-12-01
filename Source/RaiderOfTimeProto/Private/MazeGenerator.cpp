// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

#include <vector>

class Door 
{
public:
	FIntPoint location;

	void Draw(TArray<FTileArray>& map) const
	{
		map[location.X].tiles[location.Y] = MazeTileType::PATH;
	}
};

class Wall
{
public:
	FIntPoint start, end;

	void Draw(TArray<FTileArray>& map) const
	{
		FillWalls(map, start, end);
	}

	int32 Size() const 
	{
		return start.X < end.X ? abs(end.X - start.X) : abs(end.Y - start.Y);
	}

	FIntPoint GetRandomLocation() const
	{		
		if (start.X == end.X) {
			if (start.Y < end.Y )
				return { start.X, FMath::RandRange(start.Y, end.Y) };
			if (end.Y < start.Y)
				return { start.X, FMath::RandRange(end.Y, start.Y ) };
		}

		if (start.Y == end.Y) {
			if (start.X < end.X )
				return {FMath::RandRange(start.X , end.X), start.Y};
			if (end.X < start.X )
				return {FMath::RandRange(end.X , start.X), start.Y};
		}
		return start;
	}

private:
	static void FillWalls(TArray<FTileArray>& map, const FIntPoint& start, const FIntPoint& end)
	{
		if (start.X == end.X)
			FillWallsVertical(map, start.X, start.Y, end.Y);
		if (start.Y == end.Y)
			FillWallsHorizontal(map, start.Y, start.X, end.X);
	}

	static void FillWallsVertical(TArray<FTileArray>& map, int32 x, int32 yStart, int32 yEnd)
	{
		map[x].tiles[yEnd] = MazeTileType::WALL;

		int32 distance = yEnd - yStart;

		if (distance == 0)
			return;

		int32 iterValue = distance / abs(distance);

		for (int32 y = yStart; y != yEnd; y += iterValue) {
			map[x].tiles[y] = MazeTileType::WALL;
		}
	}

	static void FillWallsHorizontal(TArray<FTileArray>& map, int32 y, int32 xStart, int32 xEnd)
	{
		map[xEnd].tiles[y] = MazeTileType::WALL;

		int32 distance = xEnd - xStart;

		if (distance == 0)
			return;

		int32 iterValue = distance / abs(distance);

		for (int32 x = xStart; x != xEnd; x += iterValue) {
			map[x].tiles[y] = MazeTileType::WALL;
		}


	}
};

class Chamber 
{
public:
	FIntPoint leftBottom, rightTop;
	Door door;
	int32 Width() const 
	{
		return rightTop.X - leftBottom.X;
	}

	int32 Height() const 
	{
		return rightTop.Y - leftBottom.Y;
	}
};

// leftBottom <= result >= rightTop
static FIntPoint RandomPointInBounds(const FIntPoint& leftBottom, const FIntPoint& rightTop, int32 margin = 0)
{
	return { FMath::RandRange(leftBottom.X + margin, rightTop.X - margin), FMath::RandRange(leftBottom.Y + margin, rightTop.Y - margin) };
}

static bool IsPointInSkipRange(const FIntPoint& point, const std::vector<FIntPoint>& skipPoints)
{
	for (const auto& sp : skipPoints) 
	{
		if (point.X == sp.X || point.Y == sp.Y)
			return true;
	}
	return false;
}

static FIntPoint RandomPointInBoundsSkipRange(const FIntPoint& leftBottom, const FIntPoint& rightTop, const std::vector<FIntPoint>& skipPoints, int32 margin = 0)
{
	FIntPoint result = RandomPointInBounds(leftBottom, rightTop, margin);
	int32 probes = 0;
	while (IsPointInSkipRange(result, skipPoints))
	{
		if (probes > 10)
			return result;
		result = RandomPointInBounds(leftBottom, rightTop, margin);
		probes++;
	}
	return result;
}


static TArray<FTileArray> CreateBaseMap(int32 width, int32 height)
{
	TArray<FTileArray> result;
	for (int32 x = 0; x < width; x++) {		
		result.Add({});
		for (int32 y = 0; y < height; y++) {
			result[x].tiles.Add({});
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
				result[x].tiles[y] = MazeTileType::WALL;
			}
			else {
				result[x].tiles[y] = MazeTileType::PATH;
			}
		}	
	}
	return result;
}

static std::vector<Door> CreateDoors(const Chamber& chamber, const std::vector<Wall>& walls)
{
	//PARAMETER may be parameterized by chambersize
	std::vector<Door> result;

	int32 indexToSkip = FMath::RandRange(0, walls.size() - 1);
	for (int32 i = 0; i < walls.size(); i++) {
		if (i == indexToSkip)
			continue;

		result.push_back({ walls[i].GetRandomLocation() });		
	}

	return result;
}

static std::vector<Wall> CreateSplitWalls(const Chamber& chamber, const FIntPoint& splitPoint)
{
	std::vector<Wall> result{ 4 };
	result[0] = { {splitPoint.X - 1, splitPoint.Y}, { chamber.leftBottom.X + 1, splitPoint.Y }};
	result[1] = { {splitPoint.X, splitPoint.Y + 1}, {splitPoint.X, chamber.rightTop.Y - 1} };
	result[2] = { {splitPoint.X + 1, splitPoint.Y}, {chamber.rightTop.X - 1, splitPoint.Y} };
	result[3] = { {splitPoint.X, splitPoint.Y - 1}, {splitPoint.X, chamber.leftBottom.Y + 1} };
	return result;
}

static std::vector<Chamber> CreateNewChambersBySplitPoint(const Chamber& chamber, const FIntPoint& splitPoint)
{
	std::vector<Chamber> newChambers{ 4 };
	newChambers[0] = { chamber.leftBottom, splitPoint };
	newChambers[1] = { {chamber.leftBottom.X, splitPoint.Y}, {splitPoint.X, chamber.rightTop.Y} };
	newChambers[2] = { splitPoint, chamber.rightTop };
	newChambers[3] = { {splitPoint.X, chamber.leftBottom.Y}, {chamber.rightTop.X, splitPoint.Y} };
	return newChambers;
}

static std::vector<FIntPoint> Cast(const std::vector<Door>& doors) 
{
	std::vector<FIntPoint> result;
	for (const auto& door : doors) {
		result.push_back(door.location);
	}
	return result;
}

static void SplitChambers(TArray<FTileArray>& map, const Chamber& chamber, const std::vector<FIntPoint>& lastDoors) 
{
	//PARAMETER
	if (chamber.Width() <= 2 || chamber.Height() <= 2)
		return;

	const FIntPoint splitPoint = RandomPointInBoundsSkipRange(chamber.leftBottom, chamber.rightTop, lastDoors, 2);
	const std::vector<Chamber> newChambers = CreateNewChambersBySplitPoint(chamber, splitPoint);
	const std::vector<Wall> walls = CreateSplitWalls(chamber, splitPoint);
	const std::vector<Door> doors = CreateDoors(chamber, walls);

	map[splitPoint.X].tiles[splitPoint.Y] = MazeTileType::WALL;

	for (const Wall& wall : walls) {		
		wall.Draw(map);
	}

	for (const Chamber& c : newChambers) {
		SplitChambers(map, c, Cast(doors));
	}

	for (const Door& door : doors) {
		door.Draw(map);
	}
}

TArray<FTileArray> UMazeGenerator::GenerateMaze(const FMazeGeneratorData& data)
{
	TArray<FTileArray> result = CreateBaseMap(data.width, data.height);

	Chamber firstChamber;
	firstChamber.leftBottom = { 0, 0 };
	firstChamber.rightTop = { data.width - 1, data.height - 1 };
	SplitChambers(result, firstChamber, {});
	return result;
}